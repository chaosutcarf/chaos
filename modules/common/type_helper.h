#pragma once

#include <functional>
#include <initializer_list>

#include "common/numerical.h"
#include "common/type.h"
#include "utils/logger/logger.h"
namespace chaos::common {

template <typename T, typename DerivedM>
bool toNXMatrix(const std::vector<std::vector<T>> &v,
                Eigen::PlainObjectBase<DerivedM> &mat) {
  warn_msg_handler_if(return false, v.empty() || v[0].empty(),
                             "ref vector is not valid");
  const size_t cols = v.size();
  const size_t rows = v[0].size();
  mat.resize(rows, cols);
  for (size_t i = 0; i < cols; ++i) {
    error_msg_handler_if(return false, v[i].size() != rows,
                                "ref vector[{}].size != {}", v[i].size(), rows);
    mat.col(i) = Eigen::Map<const vec_t<T>>(v[i].data(), rows, 1);
  }
  return true;
}

template <typename T>
inline bool fromNXMatrix(const Eigen::Ref<const mat_t<T>> &mat,
                         std::vector<std::vector<T>> &v) {
  const size_t cols = mat.cols();
  const size_t rows = mat.rows();
  v.reserve(cols);
  for (size_t i = 0; i < cols; ++i) {
    const T *begin = mat.col(i).data();
    v.emplace_back(begin, begin + rows);
  }
  return true;
}

template <typename T>
inline mat_t<T> toNXMatrix(const std::vector<std::vector<T>> &v) {
  mat_t<T> mat;
  bool ret = toNXMatrix(v, mat);
  CHAOS_ASSERT(ret);
  return mat;
}

template <typename T>
inline std::vector<std::vector<T>> fromNXMatrix(
    const Eigen::Ref<const mat_t<T>> &mat) {
  std::vector<std::vector<T>> v;
  bool ret = fromNXMatrix(mat, v);
  CHAOS_ASSERT(ret);
  return v;
}

template <typename Scalar, typename Range = std::initializer_list<Scalar>>
constexpr vec_t<Scalar> to_vec(const Range &v) {
  vec_t<Scalar> res(v.size());
  size_t cnt = 0;
  for (const auto &item : v) {
    res[cnt++] = item;
  }
  return res;
}

template <typename Scalar, typename SparseMatrix>
inline tpl_list_t<Scalar> spm_to_tpl(const SparseMatrix &sparse) {
  tpl_list_t<Scalar> tpl;
  for (auto i = 0; i < sparse.outerSize(); ++i) {
    for (typename SparseMatrix::InnerIterator it(sparse, i); it; ++it) {
      tpl.emplace_back(it.row(), it.col(), it.value());
    }
  }
  return tpl;
}

template <typename Scalar, typename SparseMatrix = csr_mat_t<Scalar>>
inline SparseMatrix tpl_to_spm(size_t rows, size_t cols,
                               const tpl_list_t<Scalar> &tpl) {
  SparseMatrix sparse(rows, cols);
  sparse.setFromTriplets(tpl.begin(), tpl.end());
  return sparse;
}

template <typename Scalar, typename SparseMatrix = csr_mat_t<Scalar>>
inline SparseMatrix tpl_to_spm(size_t rows, const tpl_list_t<Scalar> &tpl) {
  return tpl_to_spm<Scalar, SparseMatrix>(rows, rows, tpl);
}
}  // namespace chaos::common

template <typename Scalar, int Rows>
struct std::hash<chaos::vec_t<Scalar, Rows>> {
  size_t operator()(const Eigen::Ref<const chaos::vec_t<Scalar>> &v) const {
    static_assert(Rows != -1 && Rows != 0,
                  "fixed vector hasher!, Rows != -1 and Rows != 0");
    size_t res = 0;
    //-> TODO: optimize this hasher.
    for (int i = 0; i < Rows; ++i) {
      res ^= (size_t)(v[i]) * (i + 1) *
                 chaos::numerical::constant<double>::golden_ratio +
             (res << (i + 2)) + (res >> i);
    }
    return res;
  }
};

template <typename Scalar>
struct std::hash<chaos::vec_t<Scalar>> {
  size_t operator()(const Eigen::Ref<const chaos::vec_t<Scalar>> &v) const {
    constexpr size_t p1 = 100000007;
    constexpr size_t p2 = 10000019;
    constexpr size_t p3 = 100001651;
    constexpr size_t p4 = 83492791;
    constexpr size_t p5 = 73856093;
    const size_t t1 = v.sum() * p1;
    const size_t t2 = v[p2 % v.size()] * p2;
    const size_t t3 = v[p3 % v.size()] * p3;
    const size_t t4 = v[p4 % v.size()] * p4;
    const size_t t5 = v.size() * p5;
    const size_t t6 =
        v.hasNaN() * chaos::numerical::constant<double>::golden_ratio;
    return t1 ^ t2 ^ t3 ^ t4 ^ t5 ^ t6;
  }
};

template <typename Scalar>
struct std::equal_to<chaos::vec_t<Scalar>> {
  equal_to(Scalar eps = chaos::numerical::constant<Scalar>::eps) : eps(eps) {}

  bool operator()(const Eigen::Ref<const chaos::vec_t<Scalar>> &lhs,
                  const Eigen::Ref<const chaos::vec_t<Scalar>> &rhs) const {
    auto scale = std::min(lhs.cwiseAbs().maxCoeff(), rhs.cwiseAbs().maxCoeff());
    if (scale < chaos::numerical::constant<Scalar>::eps * 100) {
      scale = 1;
    }
    return lhs.size() == rhs.size() &&
           (lhs - rhs).cwiseAbs().maxCoeff() <= eps * scale;
  }

 private:
  Scalar eps;
};

template <typename Scalar>
struct std::equal_to<chaos::mat_t<Scalar>> {
  equal_to(Scalar eps = chaos::numerical::constant<Scalar>::eps) : eps(eps) {}

  bool operator()(const Eigen::Ref<const chaos::mat_t<Scalar>> &lhs,
                  const Eigen::Ref<const chaos::mat_t<Scalar>> &rhs) const {
    auto scale = std::min(lhs.cwiseAbs().maxCoeff(), rhs.cwiseAbs().maxCoeff());
    if (scale < chaos::numerical::constant<Scalar>::eps * 100) {
      scale = 1;
    }
    return lhs.rows() == rhs.rows() && lhs.cols() == rhs.cols() &&
           (lhs - rhs).cwiseAbs().maxCoeff() <= eps * scale;
  }

 private:
  Scalar eps;
};
