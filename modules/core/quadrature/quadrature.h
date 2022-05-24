#pragma once

#include <map>

#include "common/macro.h"
#include "common/type.h"
#include "utils/params/params.h"

namespace chaos {

struct quadrature {
  quadrature() = default;
  quadrature(const matxr_t &P, const vecxr_t &W) : P(P), W(W) {}
  size_t num() const;
  size_t dim() const;
  Eigen::Ref<const vecxr_t> at(int i) const;
  real_t weight(int i) const;
  //-> quadrature points. s x #.
  matxr_t P;
  //-> quadrature weights. 1 x #.
  vecxr_t W;
};

struct quadrature_factory {
  enum cell_type {
    // 1d.
    //-> [0, 1]
    LINE,
    // 2d.
    //-> [0, 1]^2
    QUAD,
    //-> {(0, 0), (0, 1), (1, 0)}
    TRI,
    // 3d.
    //-> [0, 1]^3
    HEX,
    //-> {(0, 0, 0), (1, 0, 0), (0, 1, 0), (0, 0, 1)}
    TET,
    //-> {(0, 0, 0), (1, 0, 0), (0, 1, 0), (0, 0, 1), (1, 0, 1), (0, 1, 1)}
    WEDGE,
    //-> {(0, 0, 0), (1, 0, 0), (1, 1, 0), (0, 1, 0), (0.5, 0.5, 1)}
    PYRAMID,
  };
  static inline const std::map<std::string, cell_type> cell_type_map{
      STRING_ENUM_MAP(LINE),   STRING_ENUM_MAP(QUAD), STRING_ENUM_MAP(TRI),
      STRING_ENUM_MAP(HEX),    STRING_ENUM_MAP(TET),  STRING_ENUM_MAP(WEDGE),
      STRING_ENUM_MAP(PYRAMID)};

  struct params_t : public utils::params_group_t {
    params_t() : utils::params_group_t("qdrt", "quadrature rule") {
      emplace_back({&type, &order});
      order.add_valid(utils::range_valid_t<int>::create(0));
      type.add_valid(
          utils::enum_transform_valid_t<cell_type>::create(cell_type_map));
    }
    // clang-format off
    DEFINE_PARAM_REQUIRED(
        cell_type, type,
        "gauss legendre quadrature rule on different cell types:\n"
        "\tline: [0, 1]\n"
        "\tquad: [0, 1]^2\n"
        "\thex: [0, 1]^3\n"
        "\ttri: {(0, 0), (0, 1), (1, 0)}\n"
        "\ttet: {(0, 0, 0), (1, 0, 0), (0, 1, 0), (0, 0, 1)}\n"
        "\twedge: {(0, 0, 0), (1, 0, 0), (0, 1, 0), (0, 0, 1), (1, 0, 1), (0, 1, 1)}\n"
        "\tpyramid: {(0, 0, 0), (1, 0, 0), (1, 1, 0), (0, 1, 0), (0.5, 0.5, 1)}\n");
    DEFINE_PARAM_DEFAULT(int, order, "the integral order should be reached", 1);
    // clang-format on
  };

  static const quadrature *create(const params_t &prm) {
    return create(prm.type, prm.order);
  }
  static const quadrature *create(cell_type type, int order);

 private:
  using cache_t = std::map<int, std::unique_ptr<quadrature>>;
  static int hash_prm(cell_type type, int order);
  static cache_t cache;
};
}  // namespace chaos
