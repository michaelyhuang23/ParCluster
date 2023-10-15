#pragma once

#include "IO.h"

namespace DPC {

template <int dim>
ClusteringResult dpc_sddp(double *data, std::string oFile, std::string dFile,
                          std::size_t n, double K, double noiseCut,
                          double depCut);
} // namespace DPC