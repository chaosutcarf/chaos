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
concept OneDimTraitsConcept =
    HasMemberOverride<T> && HasMemberCanGetData<T> && HasMemberCanParallel<T>;

template <typename T>
concept TwoDimTraitsConcept = HasMemberMatFillMode<T> && HasMemberOverride<T> &&
    HasMemberCanParallel<T> && HasMemberCanGetData<T>;

template <typename T>
concept OneDimFillerConcept = requires {
  OneDimTraitsConcept<typename T::Traits>;
  //-> const api.
  requires requires(const T a) {
    { a._size() } -> std::convertible_to<index_t>;
  };
  //-> non-const api
  requires requires(T a) {
    a.template _fill<true && T::Traits::Override>(std::declval<index_t>(),
                                                  std::declval<real_t>());
    a.template _fill<false>(std::declval<index_t>(), std::declval<real_t>());
    a.setZero();
  };
};

template <typename T>
concept TwoDimFillerConcept = requires {
  TwoDimTraitsConcept<typename T::Traits>;
  //-> const api.
  requires requires(const T a) {
    { a._rows() } -> std::convertible_to<index_t>;
    { a._cols() } -> std::convertible_to<index_t>;
  };
  //-> non-const api
  requires requires(T a) {
    a.template _fill<true && T::Traits::Override>(std::declval<index_t>(),
                                                  std::declval<index_t>(),
                                                  std::declval<real_t>());
    a.template _fill<false>(std::declval<index_t>(), std::declval<index_t>(),
                            std::declval<real_t>());
    a.setZero();
  };
};

template <typename T, typename U>
concept ProvideBatchFill = (OneDimFillerConcept<T> ||
                            TwoDimFillerConcept<T>)&&requires(T a, U &&data) {
  a.template _batch_fill<true && T::Traits::Override, U>(data);
  a.template _batch_fill<false, U>(data);
};

template <bool fillmode, bool Override>
concept FillOverrideCheck = Override || !fillmode;

template <typename T, typename U = real_t>
concept UnaryAccessible = HasSize<T> && requires(const T a) {
  //-> access operation.
  { a[std::declval<index_t>()] } -> std::convertible_to<U>;
};

template <typename T, typename U = real_t>
concept UnaryAssignable = HasSize<T> && requires(T a) {
  { a[std::declval<index_t>()] } -> std::assignable_from<U>;
};

template <typename T>
concept ArithmeticType = std::is_arithmetic_v<T>;

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

template <typename T>
concept EigenDenseMatrixBase = std::derived_from<T, Eigen::MatrixBase<T>>;

template <typename T>
concept EigenSparseMatrixBase = HasRows<T> && HasCols<T> && requires(T a) {
  {
    a.coeffRef(std::declval<index_t>(), std::declval<index_t>())
    } -> std::assignable_from<real_t>;
};

}  // namespace chaos::mapping::data_filler_concepts
