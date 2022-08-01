#pragma once

#include <concepts>

#include "common/type.h"

namespace chaos::mapping {

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
HAS_MEMBER(bool, AllowGetData);
HAS_MEMBER(MATRIX_FILL_MODE, MatFillMode);
#undef HAS_MEMBER

template <typename T>
struct FillerTraits {
#define DEF_TRAITS(Type, Name, Default, ...) \
  static constexpr Type Name() {             \
    if constexpr (HasMember##Name<T>) {      \
      return T::Name __VA_ARGS__;            \
    } else {                                 \
      return Default;                        \
    }                                        \
  }

  DEF_TRAITS(bool, Override, false);
  DEF_TRAITS(bool, CanParallel, false);
  DEF_TRAITS(MATRIX_FILL_MODE, MatFillMode, MATRIX_FILL_MODE::FULL);
  DEF_TRAITS(bool, CanGetData, false,
             &&MatFillMode() == MATRIX_FILL_MODE::FULL && Override() == true);

#undef DEF_TRAITS
};

template <bool isOverride, typename LHS, typename RHS>
concept AssignableConcept = (isOverride && std::assignable_from<LHS, RHS>) ||
                            (!isOverride && requires(LHS a, RHS b) { a += b; });

template <bool fillmode, bool Override>
concept FillOverrideCheck = Override || !fillmode;

namespace details {
struct _ONE_DIM_READ_DATA_INTERFACE_ {
  index_t size() const { return 0; }
  real_t operator[](index_t) const { return 0; }
};
struct _TWO_DIM_READ_DATA_INTERFACE_ {
  index_t rows() const { return 0; }
  index_t cols() const { return 0; }
  real_t operator()(index_t, index_t) const { return 0; }
};
}  // namespace details

template <typename T>
concept OneDimFillerConcept = HasFunctionSize<T> && requires(T a) {
  a.setZero();
//-> individual fill.
#define ARGS std::declval<index_t>(), std::declval<real_t>()
  a.template fill<true && FillerTraits<T>::Override()>(ARGS);
  a.template fill<false>(ARGS);
#undef ARGS
  //-> batch fill.
#define ARGS std::declval<details::_ONE_DIM_READ_DATA_INTERFACE_>()
  a.template fill<true && FillerTraits<T>::Override()>(ARGS);
  a.template fill<false>(ARGS);
#undef ARGS
};

template <typename T>
concept TwoDimFillerConcept = HasFunctionRows<T> && HasFunctionCols<T> &&
    requires(T a) {
  a.setZero();
//-> individual fill.
#define ARGS \
  std::declval<index_t>(), std::declval<index_t>(), std::declval<real_t>()
  a.template fill<true && FillerTraits<T>::Override()>(ARGS);
  a.template fill<false>(ARGS);
#undef ARGS
  //-> batch fill.
#define ARGS std::declval<details::_TWO_DIM_READ_DATA_INTERFACE_>()
  a.template fill<true && FillerTraits<T>::Override()>(ARGS);
  a.template fill<false>(ARGS);
#undef ARGS
};

//-> common type concepts.
template <typename T>
concept ArithmeticType = std::is_arithmetic_v<T>;

template <typename T>
concept EigenDenseMatrixConcept = std::derived_from<T, Eigen::MatrixBase<T>>;

template <typename T>
concept EigenSparseMatrixConcept =
    std::derived_from<T, Eigen::SparseMatrixBase<T>>;

template <typename T, typename U = real_t>
concept UnaryAccessible = HasFunctionSize<T> && requires(const T a, index_t p) {
  { a[p] } -> std::convertible_to<U>;
};

template <typename T, typename U = real_t>
concept UnaryAssignable = HasFunctionSize<T> && requires(T a, index_t p) {
  { a[p] } -> std::assignable_from<U>;
};
template <typename T, typename U = real_t>
concept BinaryAccessible = HasFunctionRows<T> && HasFunctionCols<T> &&
    requires(const T a, index_t r, index_t c) {
  { a(r, c) } -> std::convertible_to<U>;
};

template <typename T, typename U = real_t>
concept BinaryAssignable = HasFunctionRows<T> && HasFunctionCols<T> &&
    requires(T a, index_t r, index_t c) {
  { a(r, c) } -> std::assignable_from<U>;
};

template <typename T, typename U>
concept ProvideBatchFill = requires(T a, U &&data) {
  a.template fill<true && FillerTraits<T>::Override(), U>(data);
  a.template fill<false, U>(data);
};
}  // namespace chaos::mapping
