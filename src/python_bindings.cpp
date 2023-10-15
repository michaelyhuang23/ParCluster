#include "IO.h"
#include "dpc_sddp.h"
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/shared_ptr.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/unordered_map.h>
#include <nanobind/stl/vector.h>
#include <sstream>

bool report_stats = true;

namespace nb = nanobind;

using namespace nb::literals;

namespace {
DPC::ClusteringResult dpc_sddp_helper(double *data, std::string oFile,
                                 std::string dFile, std::size_t n, double K,
                                 double noiseCut, double depCut, int dim) {
  if (dim == 2) {
    return DPC::dpc_sddp<2>(data, oFile, dFile, n, K, noiseCut, depCut);
  } else if (dim == 128) {
    return DPC::dpc_sddp<128>(data, oFile, dFile, n, K, noiseCut, depCut);
  } else {
    std::cout << "Unsupported dimension, dim = "<< dim << "\n";
    exit(1);
  }
}
} // namespace

DPC::ClusteringResult
dpc_sddp_numpy(nb::ndarray<double, nb::shape<nb::any, nb::any>, nb::device::cpu,
                           nb::c_contig>
                   data,
               const unsigned K, const std::string &output_path,
               const std::string &decision_graph_path, double noiseCut,
               double depCut) {

  double *data_ptr = data.data();
  size_t num_data = data.shape(0);
  size_t data_dim = data.shape(1);

  return dpc_sddp_helper(data_ptr, output_path, decision_graph_path, num_data, K,
                         noiseCut, depCut, data_dim);
}

DPC::ClusteringResult dpc_sddp_filename(const std::string &data_path,
                                        const unsigned K,
                                        const std::string &output_path,
                                        const std::string &decision_graph_path,
                                        double noiseCut, double depCut) {
  double *data;
  std::size_t n;
  std::size_t dim;
  DPC::load_text_file(data_path, data, n, dim);

  DPC::ClusteringResult result = dpc_sddp_helper(
      data, output_path, decision_graph_path, n, K, noiseCut, depCut, dim);

  free(data);

  return result;
}

NB_MODULE(par_dpc_ext, m) {
  m.doc() = "Module for Parallel DPC clustering";

  // Don't want to allow conversion since then it will copy
  m.def("dpc_sddp_numpy", &dpc_sddp_numpy, "data"_a.noconvert(), "K"_a = 6,
        "output_path"_a = "", "decision_graph_path"_a = "", "noiseCut"_a = 0,
        "depCut"_a = 0,
        "This function clusters the passed in numpy data using SDDP and "
        "returns a "
        "ClusteringResult object with the clusters and metadata about the "
        "clustering process.");

  m.def("dpc_sddp_filename", &dpc_sddp_filename, "data_path"_a, "K"_a = 6,
        "output_path"_a = "", "decision_graph_path"_a = "", "noiseCut"_a = 0,
        "depCut"_a = 0,
        "This function clusters the passed in data file name using SDDP and "
        "returns a "
        "ClusteringResult object with the clusters and metadata about the "
        "clustering process.");

  nb::class_<DPC::ClusteringResult>(m, "ClusteringResult")
      .def_rw("clusters", &DPC::ClusteringResult::clusters)
      .def_rw("metadata", &DPC::ClusteringResult::output_metadata);
}
