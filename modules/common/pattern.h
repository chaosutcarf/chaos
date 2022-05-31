/** -*- mode: c++ -*-
 * @file pattern.h
 * @author LamKamhang (Cool_Lam@outlook.com)
 * @brief A Documented file.
 * @version 1.0
 * @date Monday, June 28, 2021 AM11:55:22 HKT
 *
 * Detailed description
 *
 *
 * @copyright Copyright (c) 2021
 */
#pragma once
#include <memory>

#define NIL_FUNC []() {}

#define DECLARE_NON_COPYABLE(c) \
  c(const c &) = delete;        \
  c &operator=(const c &) = delete;

#define DECLARE_NON_MOVEABLE(c) \
  c(const c &&) = delete;       \
  c &operator=(const c &&) = delete;

// only support no argument default constructors.
// singleton class example:
//
// class Test1{
//   DECLARE_SINGLETON_CLASS(
//       Test1,
//       [&](int data = 10){
//         this->data = data;
//       },
//       200);
//  private:
//   int data;
// };
//
// class Test2{
//   DECLARE_SINGLETON_CLASS(
//       Test2,
//       [](){});
//  private:
//   int data;
// };
//
#define DECLARE_SINGLETON(c, func, ...) \
 protected:                             \
  c() { func(__VA_ARGS__); }            \
  DECLARE_NON_COPYABLE(c);              \
                                        \
 public:                                \
  static c &instance() {                \
    static c m_instance;                \
    return m_instance;                  \
  }

#define DECLARE_LAZY_SINGLETON(c, func, ...)       \
 protected:                                        \
  c() { func(__VA_ARGS__); }                       \
  DECLARE_NON_COPYABLE(c);                         \
                                                   \
 public:                                           \
  static c &instance() {                           \
    static std::unique_ptr<c> m_instance{nullptr}; \
    if (m_instance == nullptr) {                   \
      m_instance = std::unique_ptr<c>(new c());    \
    }                                              \
    return *m_instance;                            \
  }

#define CRTPclass(Derived, Base) class Derived : public Base<Derived>

#define CRTP_derived_interface(Derived, Base)                         \
  inline Derived &derived() { return *static_cast<Derived *>(this); } \
  inline const Derived &derived() const {                             \
    return *static_cast<const Derived *>(this);                       \
  }                                                                   \
  inline Derived &const_cast_derived() const {                        \
    return *static_cast<Derived *>(const_cast<Base *>(this));         \
  }                                                                   \
  inline const Derived &const_derived() const { return derived(); }
