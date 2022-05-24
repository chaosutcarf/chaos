#pragma once
#include <memory>

#include "common/macro.h"
#include "common/type.h"
#include "utils/logger/logger.h"
#include "utils/params/params.h"

namespace chaos::solver {

class linear_solver_base {
 public:
  enum linear_solver_impl_t {
    EIGEN_BUILTIN_LLT,
    EIGEN_BUILTIN_LDLT,
    EIGEN_BUILTIN_D_PCG,
    EIGEN_BUILTIN_IC_PCG,
    EIGEN_BUILTIN_D_BIPCG,
    EIGEN_BUILTIN_ILU_BIPCG,
#ifdef USE_SUITESPARSE
    CHOLMOD_SUPERNODAL_LLT,
    CHOLMOD_SIMPLICIAL_LLT,
    CHOLMOD_SIMPLICIAL_LDLT,
    UmfPackLU,
#endif
#ifdef USE_PARDISO
    PARDISO_LLT,
    PARDISO_LDLT,
#endif
  };
  inline static const std::map<std::string, linear_solver_impl_t>
      linear_solver_impl_map{
          STRING_ENUM_MAP(EIGEN_BUILTIN_LLT),
          STRING_ENUM_MAP(EIGEN_BUILTIN_LDLT),
          STRING_ENUM_MAP(EIGEN_BUILTIN_D_PCG),
          STRING_ENUM_MAP(EIGEN_BUILTIN_IC_PCG),
          STRING_ENUM_MAP(EIGEN_BUILTIN_D_BIPCG),
          STRING_ENUM_MAP(EIGEN_BUILTIN_ILU_BIPCG),
#ifdef USE_SUITESPARSE
          STRING_ENUM_MAP(CHOLMOD_SUPERNODAL_LLT),
          STRING_ENUM_MAP(CHOLMOD_SIMPLICIAL_LLT),
          STRING_ENUM_MAP(CHOLMOD_SIMPLICIAL_LDLT),
#endif
#ifdef USE_PARDISO
          STRING_ENUM_MAP(PARDISO_LLT),
          STRING_ENUM_MAP(PARDISO_LDLT),
#endif
      };

  struct params_t : public utils::params_group_t {
    params_t() : utils::params_group_t("ls", "linear solver params") {
      prms.emplace_back(&type);
      prms.emplace_back(&tol);
      prms.emplace_back(&maxits);
      type.add_valid(
          utils::enum_transform_valid_t<linear_solver_impl_t>::create(
              {linear_solver_impl_map}));
    }

    DEFINE_PARAM_DEFAULT(linear_solver_impl_t, type, "linear solver impl type",
                         CHOLMOD_SUPERNODAL_LLT);
    DEFINE_PARAM_DEFAULT(real_t, tol, "tolerance for iterative solver", 1e-2);
    DEFINE_PARAM_DEFAULT(size_t, maxits, "maxits for iterative solver",
                         (size_t)-1);
  };

  virtual ~linear_solver_base() = default;
  virtual void compute(const csr_matr_t &A) = 0;
  virtual void analyzePattern(const csr_matr_t &A) = 0;
  virtual void factorize(const csr_matr_t &A) = 0;
  virtual void solve(const Eigen::Ref<const matxr_t> &b,
                     const Eigen::Ref<matxr_t> &x) const = 0;

  matxr_t solve(const Eigen::Ref<const matxr_t> &b) const {
    matxr_t x(b.rows(), b.cols());
    solve(b, x);
    return x;
  }

  virtual Eigen::ComputationInfo info() const = 0;
};

template <MATRIX_FILL_MODE Mode_ = MATRIX_FILL_MODE::FULL>
class linear_solver_t : public linear_solver_base {
 public:
  static constexpr MATRIX_FILL_MODE Mode = Mode_;
  virtual ~linear_solver_t() = default;

  static std::unique_ptr<linear_solver_t<Mode_>> create(
      const params_t &prm = {});
  static std::unique_ptr<linear_solver_t<Mode_>> create(
      linear_solver_impl_t type, real_t tol = 1e-2, size_t maxits = -1);
};

template <MATRIX_FILL_MODE Mode = MATRIX_FILL_MODE::FULL>
class iterative_linear_solver_t : public linear_solver_t<Mode> {
 public:
  virtual void setMaxIterations(const size_t maxIters) = 0;
  virtual void setTolerance(const real_t tol) = 0;
  virtual real_t tolerance() const = 0;
  virtual real_t error() const = 0;
  virtual size_t maxIterations() const = 0;
  virtual size_t iterations() const = 0;
};

template <typename Solver, MATRIX_FILL_MODE Mode>
class eigen_ls_wrapper_t : public linear_solver_t<Mode> {
 public:
  eigen_ls_wrapper_t() = default;
  eigen_ls_wrapper_t(const csr_matr_t &A) : solver_(A) {}

  void compute(const csr_matr_t &A) override { solver_.compute(A); }
  void analyzePattern(const csr_matr_t &A) override {
    solver_.analyzePattern(A);
  }
  void factorize(const csr_matr_t &A) override { solver_.factorize(A); }
  void solve(const Eigen::Ref<const matxr_t> &b,
             const Eigen::Ref<matxr_t> &x) const override {
    CHAOS_DEBUG_ASSERT(x.rows() == b.rows());
    CHAOS_DEBUG_ASSERT(x.cols() == b.cols());
    x.const_cast_derived() = solver_.solve(b);
  }
  Eigen::ComputationInfo info() const override { return solver_.info(); }

 private:
  Solver solver_;
};

template <typename Solver, MATRIX_FILL_MODE Mode>
class eigen_iterative_ls_wrapper_t : public iterative_linear_solver_t<Mode> {
 public:
  eigen_iterative_ls_wrapper_t() = default;
  eigen_iterative_ls_wrapper_t(const csr_matr_t &A) : solver_(A) {}

  void compute(const csr_matr_t &A) override { solver_.compute(A); }
  void analyzePattern(const csr_matr_t &A) override {
    solver_.analyzePattern(A);
  }
  void factorize(const csr_matr_t &A) override { solver_.factorize(A); }
  void solve(const Eigen::Ref<const matxr_t> &b,
             const Eigen::Ref<matxr_t> &x) const override {
    CHAOS_DEBUG_ASSERT(x.rows() == b.rows());
    CHAOS_DEBUG_ASSERT(x.cols() == b.cols());
    x.const_cast_derived() = solver_.solve(b);
  }
  Eigen::ComputationInfo info() const override { return solver_.info(); }

  void setMaxIterations(const size_t maxIters) override {
    solver_.setMaxIterations(maxIters);
  }
  void setTolerance(const real_t tol) override { solver_.setTolerance(tol); }
  real_t tolerance() const override { return solver_.tolerance(); }
  real_t error() const override { return solver_.error(); }
  size_t maxIterations() const override { return solver_.maxIterations(); }
  size_t iterations() const override { return solver_.iterations(); }

 private:
  Solver solver_;
};

}  // namespace chaos::solver
