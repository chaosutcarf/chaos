#pragma once

#include "common/type.h"
namespace chaos {
struct spring_chain_t {
  spring_chain_t(size_t N) : rest_length(N), stiffness(N), N(N) {}
  std::vector<real_t> rest_length;
  std::vector<real_t> stiffness;
  size_t N;
};

struct spring_net {
  Eigen::Matrix<unsigned, 2, -1> conn;
  std::vector<real_t> rest_length;
  std::vector<real_t> stiffness;
  size_t N;
};
}  // namespace chaos
