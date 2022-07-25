#pragma once

#include <concepts>
#include <utility>

#include "common/type.h"

namespace chaos::mapping {

template <bool isOverride, typename LHS, typename RHS>
concept AssignableConcept = (isOverride && std::assignable_from<LHS, RHS>) ||
                            (!isOverride && requires(LHS a, RHS b) { a += b; });

#define HAS_CONST_FUNCTION(RetType, Op, op)       \
  template <typename T>                           \
  concept HasFunction##Op = requires(const T a) { \
    { a.op() } -> std::convertible_to<RetType>;   \
  };
HAS_CONST_FUNCTION(index_t, Rows, rows);
HAS_CONST_FUNCTION(index_t, Cols, cols);
HAS_CONST_FUNCTION(index_t, Size, size);
#undef HAS_CONST_FUNCTION

#define HAS_MEMBER(Type, Mem)                \
  template <typename T>                      \
  concept HasMember##Mem = requires {        \
    { T::Mem } -> std::convertible_to<Type>; \
  };
HAS_MEMBER(bool, Override);
HAS_MEMBER(bool, CanParallel);
HAS_MEMBER(bool, CanGetData);
HAS_MEMBER(MATRIX_FILL_MODE, MatFillMode);
#undef HAS_MEMBER

template <typename T>
concept OneDimFillerConcept = HasFillerTraits<T> && HasFunctionSize<T> &&
    requires(T a) {
  a.template _fill<true && T::Traits::Override()>(std::declval<index_t>(),
                                                  std::declval<real_t>());
  a.template _fill<false>(std::declval<index_t>, std::declval<real_t>());
  a.setZero();
};

template <typename T>
concept TwoDimFillerConcept = HasFillerTraits<T> && HasFunctionRows<T> &&
    HasFunctionCols<T> && requires(T a) {
  a.template _fill<true && T::Traits::Override()>(
      std::declval<index_t>(), std::declval<index_t>(), std::declval<real_t>());
  a.template _fill<false>(std::declval<index_t>(), std::declval<index_t>,
                          std::declval<real_t>());
  a.setZero();
};

template <typename T, typename U>
concept ProvideBatchFill = requires(T a, U&& data) {
  a.template _fill<true && T::Traits::Override(), U>(data);
  a.template _fill<false, U>(data);
};

template <typename T>
concept ArithmeticType = std::is_arithmetic_v<T>;

template <typename T>
concept EigenDenseMatrixConcept = std::derived_from<T, Eigen::MatrixBase<T>>;

template <typename T>
concept EigenSparseMatrixConcept = HasFunctionRows<T> && HasFunctionCols<T> &&
    requires(T a) {
  {
    a.coeffRef(std::declval<index_t>(), std::declval<index_t>())
    } -> std::assignable_from<real_t>;
};
template <typename T, typename U = real_t>
concept UnaryAccessible = HasFunctionSize<T> && requires(const T a) {
  { a[std::declval<index_t>()] } -> std::convertible_to<U>;
};
template <typename T, typename U = real_t>
concept UnaryAssignable = HasFunctionSize<T> && requires(T a) {
  { a[std::declval<index_t>()] } -> std::assignable_from<U>;
};
template <typename T, typename U = real_t>
concept BinaryAccessible = HasFunctionRows<T> && HasFunctionCols<T> &&
    requires(const T a) {
  {
    a(std::declval<index_t>(), std::declval<index_t>())
    } -> std::convertible_to<U>;
};
template <typename T, typename U = real_t>
concept BinaryAssignable = HasFunctionRows<T> && HasFunctionCols<T> &&
    requires(T a) {
  {
    a(std::declval<index_t>(), std::declval<index_t>())
    } -> std::assignable_from<U>;
};

}  // namespace chaos::mapping
