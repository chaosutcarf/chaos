#pragma once

#include <Spectra/SymEigsBase.h>

#include "common/numerical.h"
#include "common/type.h"
#include "utils/params/params.h"

namespace chaos::math {
struct spectra_params_t : public utils::params_group_t {
  spectra_params_t() : utils::params_group_t("spectra", "spectra params") {
    prms.emplace_back(&maxits);
    prms.emplace_back(&tol);
    prms.emplace_back(&ncv);
  }
  DEFINE_PARAM_DEFAULT(size_t, maxits, "max iters", 1000);
  DEFINE_PARAM_DEFAULT(real_t, tol, "tolerance",
                       numerical::constant<real_t>::eps);
  //-> This parameter must satisfy nev<ncv≤n, and is advised to take
  // ncv≥2⋅nev.
  //-> if ncv is positive, then its actual value is nev + ncv.
  //-> if ncv is negative, then its actual value is (-ncv+1)*nev.
  DEFINE_PARAM_DEFAULT(
      int, ncv,
      "This parameter must satisfy nev < ncv <= n and is advised to take ncv "
      ">= 2nev.\n"
      "if ncv > 0, then its actual value is nev + ncv.\n"
      "if ncv < 0, then its actual value is (-ncv + 1)*nev.",
      -1);
  DEFINE_PARAM_DEFAULT(real_t, shift_eps, "shift eps",
                       -numerical::constant<float>::eps);
};

//-> A is a symmetric matrix.
//-> return value is the number of convergence basis
template <int Uplo = Eigen::Upper, typename MatType = csr_matr_t>
int symmetric_evd(
    const MatType &A, int num, matxr_t *basis = nullptr,
    vecxr_t *lambda = nullptr,
    const Spectra::SortRule &rule = Spectra::SortRule::SmallestMagn,
    const spectra_params_t &prm = {});

//-> A is a symmetric matrix.
//-> B is a positive definitive matrix.
//-> return value is the number of convergence basis
//
//-> This function solve: Ax = \lambda Bx, seem B as metric.
//-> Without use this general way, there are some conversions:
//->  1. <==> B^{-1}Ax = \loambda x, but this way will lead to a non-symmetric
//            decomposition.
//->  2. <==> B = CC^T, C^{-1}AC^{-T}C^{T}x = \lambda C^{T} x.
//->          denote: \bar{A} = C^{-1}AC^{-T}, \bar{x} = C^{T}x.
//->          2.1: first compute \bar{A} \bar{x} = \lambda \bar{x} as usual way;
//->          2.2: the eigenvalues are the same to the original one.
//->               the eigenvectors can be converted by: U = C^{-T} \bar{U}.
//-> the different strategy performance has not done.
template <int Uplo = Eigen::Upper, typename MatType = csr_matr_t>
int symmetric_gevd(
    const MatType &A, const MatType &B, int num, matxr_t *basis = nullptr,
    vecxr_t *lambda = nullptr,
    const Spectra::SortRule &rule = Spectra::SortRule::SmallestMagn,
    const spectra_params_t &prm = {});

//-> subspace general eigen value decomposition.
//-> subspace basis should column full rank.
//-> TODO.
//-> DO NOT CHECK.
template <int Uplo = Eigen::Upper, typename MatType = csr_matr_t,
          bool dense = true>
int symmetric_subspace_gevd(
    const MatType &A, const MatType &B, const matxr_t &subspace_basis, int num,
    matxr_t *basis = nullptr, vecxr_t *lambda = nullptr,
    const Spectra::SortRule &rule = Spectra::SortRule::SmallestMagn,
    const spectra_params_t &prm = {});
}  // namespace chaos::math
