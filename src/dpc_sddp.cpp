#include "dpc_sddp.h"

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "origKdTree/kdTree.h"
#include "pargeo/ball.h"
#include "pargeo/getTime.h"
#include "pargeo/point.h"
#include "pargeo/pointIO.h"
#include "pargeo/unionFind.h"
#include "parlay/parallel.h"
#include "parlay/primitives.h"
#include "parlay/sequence.h"
#include "priorityKdTree/psKdTree.h"

#include "IO.h"

namespace DPC {

namespace {

template <int dim>
parlay::sequence<pargeo::pointD<dim, double>>
compute_densities(parlay::sequence<pargeo::point<dim>> &ptrs, int K) {
  using point = pargeo::point<dim>;
  using ball = pargeo::_ball<dim, point>;
  using pointF = pargeo::pointD<dim, double>;
  pargeo::origKdTree::node<dim, point> *tree =
      pargeo::origKdTree::build<dim, point>(ptrs, true, 1);

  parlay::sequence<pointF> ptrDs(ptrs.size());

  auto knns = pargeo::origKdTree::batchKnn(ptrs, K, tree);

  parlay::parallel_for(0, ptrs.size(), [&](size_t i) {
    float dist = ptrs[knns[i * K + K - 1]].dist(ptrs[i]);
    ptrDs[i] = pointF(ptrs[i].coords(), 1.0 / dist);
  });

  return ptrDs;
}
} // namespace

template <int dim>
ClusteringResult dpc_sddp(double *data, std::string oFile, std::string dFile,
                          std::size_t n, double K, double noiseCut,
                          double depCut) {
  using point = pargeo::point<dim>;
  using ball = pargeo::_ball<dim, point>;
  using pointF = pargeo::pointD<dim, double>;

  pargeo::timer densityT, depT, linkageT, totalT;
  std::cout << "num_thread: " << parlay::num_workers() << std::endl;
  std::unordered_map<std::string, double> output_metadata;

  densityT.start();
  totalT.start();
  parlay::sequence<point> ptrs = parlay::tabulate(
      n, [&](size_t i) -> point { return point(data + dim * i); });
  parlay::sequence<pointF> ptrDs = compute_densities<dim>(ptrs, K);
  // std::cout << "density: " << densityT.get_next() << std::endl;
  output_metadata["Compute density time"] = densityT.get_next();

  depT.start();
  parlay::sequence<int> depPtr(n);
  parlay::sequence<pointF> sptrs(ptrDs);
  parlay::sequence<int> inverseMap(n);
  parlay::parallel_for(0, n, [&inverseMap](int i) { inverseMap[i] = i; });
  parlay::stable_sort_inplace(inverseMap, [&](int a, int b) {
    return pointF::attCompRev(sptrs[a], sptrs[b]);
  });
  parlay::stable_sort_inplace(ptrDs, pointF::attCompRev);

  pargeo::psKdTree::tree<dim, pointF> *root =
      pargeo::psKdTree::build<dim, pointF>(ptrDs, true, 16);
  root->pargeo::psKdTree::node<dim, pointF>::initParallel();
  parlay::parallel_for(
      0, n,
      [&](size_t i) {
        pointF *ptr = root->NearestNeighborBounded(i);
        if (ptr)
          depPtr[inverseMap[i]] = inverseMap[ptr->attribute];
        else
          depPtr[inverseMap[i]] = -1;
      },
      1);
  output_metadata["Compute dependent points time"] = depT.get_next();

  // std::cout << "dependent: " << depT.get_next() << std::endl;

  linkageT.start();
  pargeo::unionFind<int> UF(n);
  parlay::parallel_for(0, n, [&](int i) {
    if (sptrs[i].attribute >= noiseCut) {
      if (depPtr[i] != -1 &&
          (sptrs[i].distSqr(sptrs[depPtr[i]]) < depCut * depCut)) {
        UF.link(i, depPtr[i]);
      }
    }
  });

  std::vector<int> cluster(n);
  parlay::parallel_for(0, n, [&](int i) { cluster[i] = UF.find(i); });
  output_metadata["Find clusters time"] = linkageT.get_next();
  // std::cout << "link:" << linkageT.get_next() << std::endl;

  output_metadata["Total time"] = totalT.get_next();
  // std::cout << "total:" << totalT.get_next() << std::endl;

  if (dFile.size() > 0) {
    std::ofstream fout(dFile);
    for (int i = 0; i < n; i++)
      fout << sptrs[i].attribute << " " << sptrs[i].dist(sptrs[depPtr[i]])
           << '\n';
    fout.close();
  }

  if (oFile.size() > 0) {
    std::ofstream fout(oFile);
    for (int i = 0; i < n; i++)
      fout << cluster[i] << '\n';
    fout.close();
  }

  return {output_metadata, cluster};
}

} // namespace DPC

template DPC::ClusteringResult DPC::dpc_sddp<2>(double *, std::string,
                                                std::string, std::size_t,
                                                double, double, double);
template DPC::ClusteringResult DPC::dpc_sddp<128>(double *, std::string,
                                                  std::string, std::size_t,
                                                  double, double, double);
