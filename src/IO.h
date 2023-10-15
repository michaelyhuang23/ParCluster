#pragma once

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <system_error>
#include <unordered_map>
#include <vector>

namespace DPC {

namespace {
inline bool is_newline(char c) {
  switch (c) {
  case '\r':
  case '\n':
    return true;
  default:
    return false;
  }
}

inline bool is_delim(char c) {
  switch (c) {
  case '\t':
  case ';':
  case ',':
  case ' ':
    return true;
  default:
    return false;
  }
}

inline bool is_space(char c) { return is_newline(c) || is_delim(c) || c == 0; }

inline std::vector<char> readStringFromFile(const std::string &fileName) {
  std::ifstream file(fileName, std::ios::in | std::ios::binary | std::ios::ate);
  if (!file.is_open()) {
    throw std::runtime_error("Unable to open file");
  }
  long end = file.tellg();
  file.seekg(0, std::ios::beg);
  long n = end - file.tellg();
  std::vector<char> bytes(n, (char)0);
  file.read(bytes.data(), n);
  file.close();
  return bytes;
}

inline std::pair<std::vector<char *>, size_t>
stringToWords(std::vector<char> &Str) {
  size_t n = Str.size();
  std::vector<char *> SA;
  bool isLastSpace = true;
  size_t dim = 0;
  for (size_t i = 0; i < n; i++) {
    bool isThisSpace = is_space(Str[i]);
    if (!isThisSpace && isLastSpace) {
      SA.push_back(Str.data() + i);
    }
    if (dim == 0 && is_newline(Str[i])) {
      dim = SA.size();
    }
    isLastSpace = isThisSpace;
  }
  return std::make_pair(SA, dim);
}
} // namespace

// load data from text_file.
inline void load_text_file(const std::string &text_file, double *&data,
                           size_t &npts, size_t &dim) {
  std::vector<char> chars = readStringFromFile(text_file);
  auto ret = stringToWords(chars);
  std::vector<char *> words(std::move(ret.first));
  dim = ret.second;
  assert(words.size() % dim == 0);
  npts = words.size() / dim;
  std::cout << "Metadata: #pts = " << npts << ", #dims = " << dim << "... "
            << std::flush;
  size_t allocSize = npts * dim * sizeof(double);
  std::cout << "allocating aligned memory of " << allocSize << " bytes... "
            << std::flush;

  data = (double *)malloc(allocSize * sizeof(double));
  std::cout << "done. Copying data to allocated buffer..." << std::flush;
  for (size_t i = 0; i < npts; i++) {
    for (size_t d = 0; d < dim; d++) {
      *(data + i * dim + d) = atof(words[i * dim + d]);
    }
  }
  std::cout << " done." << std::endl;
}

struct ClusteringResult {
  std::unordered_map<std::string, double> output_metadata;
  std::vector<int> clusters;
};
} // namespace DPC