#pragma once

#include <concepts>
#include <type_traits>

#include "common/type.h"
#include "common/type_traits.h"

namespace chaos::mapping::data_filler_concepts {

#define const_interface_no_args(Op, op)         \
  template <typename T>                         \
  concept Has##Op = requires(const T a) {       \
    { a.op() } -> std::convertible_to<index_t>; \
  };

const_interface_no_args(Rows, rows);
const_interface_no_args(Cols, cols);
const_interface_no_args(Size, size);
#undef const_interface_no_args

#define has_member(Type, Mem)                \
  template <typename T>                      \
  concept HasMember##Mem = requires {        \
    { T::Mem } -> std::convertible_to<Type>; \
  };
has_member(bool, Override);
has_member(bool, CanParallel);
has_member(bool, CanGetData);
has_member(MATRIX_FILL_MODE, MatFillMode);
#undef has_member

template <typename T>
concept IsOverride = HasMemberOverride<T> && T::Override;

template <typename T>
concept CanParallel = HasMemberCanParallel<T> && T::CanParallel;

template <typename T>
requires HasMemberMatFillMode<T>
constexpr MATRIX_FILL_MODE MatFillMode() { return T::FillMode; }

template <typename T>
constexpr MATRIX_FILL_MODE MatFillMode() {
  return MATRIX_FILL_MODE::FULL;
}

template <typename T>
concept FullFillMode =
    !HasMemberMatFillMode<T> || T::FillMode == MATRIX_FILL_MODE::FULL;

template <typename T>
concept UpperFillMode =
    HasMemberMatFillMode<T> && T::FillMode == MATRIX_FILL_MODE::UPPER;

template <typename T>
concept LowerFillMode =
    HasMemberMatFillMode<T> && T::FillMode == MATRIX_FILL_MODE::LOWER;

template <typename T>
concept CanGetData = FullFillMode<T> && IsOverride<T> &&
    (!HasMemberCanGetData<T> || T::CanGetData);

template <typename T>
concept OverrideAPI = IsOverride<T> && requires(T a) {
  //-> set zero.
  a.setZero();
};

template <bool override_mode, typename T>
concept FillOverrideCheck = IsOverride<T> || !override_mode;

template <typename T>
concept OneDimFillerConcept = (!IsOverride<T> ||
                               OverrideAPI<T>)&&requires(T a) {
  //-> has _size.
  { a._size() } -> std::convertible_to<index_t>;
  //-> has fill.
  a.template _fill<true && IsOverride<T>>(std::declval<index_t>(),
                                          std::declval<real_t>());
  a.template _fill<false>(std::declval<index_t>(), std::declval<real_t>());
};

template <typename T>
concept TwoDimFillerConcept = (!IsOverride<T> ||
                               OverrideAPI<T>)&&requires(T a) {
  { a._rows() } -> std::convertible_to<index_t>;
  { a._cols() } -> std::convertible_to<index_t>;
  a.template _fill<true && IsOverride<T>>(
      std::declval<index_t>(), std::declval<index_t>(), std::declval<real_t>());
  a.template _fill<false>(std::declval<index_t>(), std::declval<index_t>(),
                          std::declval<real_t>());
};

template <typename T, typename U = real_t>
concept UnaryAccessible = HasSize<T> && requires(const T a) {
  //-> access operation.
  { a[std::declval<index_t>()] } -> std::convertible_to<U>;
};

template <typename T, typename U = real_t>
concept UnaryAssignable = HasSize<T> && requires(T a) {
  { a[std::declval<index_t>()] } -> std::assignable_from<U>;
};

template <typename T, typename U = real_t>
concept BinaryAccessible = HasRows<T> && HasCols<T> && requires(const T a) {
  //-> access operation.
  {
    a(std::declval<index_t>(), std::declval<index_t>())
    } -> std::convertible_to<U>;
};

template <typename T, typename U = real_t>
concept BinaryAssignable = HasRows<T> && HasCols<T> && requires(T a) {
  {
    a(std::declval<index_t>(), std::declval<index_t>())
    } -> std::assignable_from<U>;
};

template <typename T, typename U>
concept ProvideBatchFill = requires(T a, U &&data) {
  a.template _batch_fill<true && IsOverride<T>, U>(data);
  a.template _batch_fill<false, U>(data);
};

template <typename T>
concept EigenDenseMatrixBase = std::derived_from<T, Eigen::MatrixBase<T>>;

template <typename T>
concept EigenSparseMatrixBase = HasRows<T> && HasCols<T> && requires(T a) {
  {
    a.coeffRef(std::declval<index_t>(), std::declval<index_t>())
    } -> std::assignable_from<real_t>;
};

}  // namespace chaos::mapping::data_filler_concepts
