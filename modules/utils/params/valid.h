#pragma once

#include <CLI/CLI.hpp>
#include <cctype>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_set>

#include "utils/fs/fshelper.h"
#include "utils/logger/logger.h"

namespace chaos::utils {
template <typename T>
struct params_valid_t {
  virtual ~params_valid_t() {}
  virtual void attach(CLI::Option * /*option*/) const {
    warn_msg("not attach to cli.");
  }
  virtual bool valid(const T &val) const = 0;
};

template <typename rangeT>
struct range_valid_t : public params_valid_t<rangeT> {
  range_valid_t(const rangeT &min = std::numeric_limits<rangeT>::min(),
                const rangeT &max = std::numeric_limits<rangeT>::max())
      : min(min), max(max) {}
  bool valid(const rangeT &val) const override {
    return val >= min && val <= max;
  }
  void attach(CLI::Option *option) const override {
    option->check(CLI::Range(min, max));
  }

  static std::shared_ptr<range_valid_t<rangeT>> create(
      const rangeT &min = std::numeric_limits<rangeT>::min(),
      const rangeT &max = std::numeric_limits<rangeT>::max()) {
    return std::make_shared<range_valid_t<rangeT>>(min, max);
  }

  rangeT min, max;
};

template <typename memberT>
struct member_valid_t : public params_valid_t<memberT> {
  member_valid_t(const std::unordered_set<memberT> &members)
      : members(members) {}
  bool valid(const memberT &val) const override {
    return members.find(val) != members.end();
  }
  void attach(CLI::Option *option) const override {
    option->check(CLI::IsMember(members));
  }

  static std::shared_ptr<member_valid_t<memberT>> create(
      const std::unordered_set<memberT> &members) {
    return std::make_shared<member_valid_t<memberT>>(members);
  }

  std::unordered_set<memberT> members;
};

template <>
struct member_valid_t<std::string> : public params_valid_t<std::string> {
  member_valid_t(const std::unordered_set<std::string> &members,
                 bool ignore_case = true)
      : members(members), ignore_case(ignore_case) {}
  bool valid(const std::string &val) const override {
    return members.find(ignore_case ? CLI::detail::to_lower(val) : val) !=
           members.end();
  }
  void attach(CLI::Option *option) const override {
    if (ignore_case) {
      option->check(CLI::IsMember(members, CLI::ignore_case));
    } else {
      option->check(CLI::IsMember(members));
    }
  }
  static std::shared_ptr<member_valid_t<std::string>> create(
      const std::unordered_set<std::string> &members) {
    return std::make_shared<member_valid_t<std::string>>(members);
  }

  std::unordered_set<std::string> members;
  bool ignore_case;
};

struct file_exist_valid_t : public params_valid_t<std::string> {
  static std::shared_ptr<file_exist_valid_t> create() {
    return std::make_shared<file_exist_valid_t>();
  }
  void attach(CLI::Option *option) const override {
    option->check(CLI::ExistingFile);
  }
  bool valid(const std::string &file) const override {
    return is_file_exist(file);
  }
};

template <typename EnumType>
struct enum_transform_valid_t : public params_valid_t<EnumType> {
  enum_transform_valid_t(const std::map<std::string, EnumType> &map)
      : map(map) {}
  static std::shared_ptr<enum_transform_valid_t<EnumType>> create(
      const std::map<std::string, EnumType> &map) {
    return std::make_shared<enum_transform_valid_t<EnumType>>(map);
  }

  void attach(CLI::Option *option) const override {
    option->transform(CLI::CheckedTransformer(map, CLI::ignore_case));
  }
  bool valid(const EnumType &) const override { return true; }
  std::map<std::string, EnumType> map;
};

template <typename ContainerType, typename ValidType>
struct container_element_valid_t : public params_valid_t<ContainerType> {
  container_element_valid_t(const std::shared_ptr<ValidType> &valid)
      : element_valid(valid) {}
  static std::shared_ptr<container_element_valid_t<ContainerType, ValidType>>
  create(const std::shared_ptr<ValidType> &valid) {
    return std::make_shared<
        container_element_valid_t<ContainerType, ValidType>>(valid);
  }
  void attach(CLI::Option *option) const override {
    if (element_valid) {
      element_valid->attach(option);
    }
  }
  bool valid(const ContainerType &) const override { return true; }
  std::shared_ptr<ValidType> element_valid;
};

template <typename T>
struct customize_valid_t : public params_valid_t<T> {
  static std::shared_ptr<customize_valid_t<T>> create(
      const std::function<bool(const T &val)> &func) {
    return std::make_shared<customize_valid_t<T>>(func);
  }
  customize_valid_t(const std::function<bool(const T &val)> &func)
      : func(func) {}

  void attach(CLI::Option *option) const override {
    option->check([&](const std::string &in) -> std::string {
      std::stringstream ss(in);
      T val;
      ss >> val;
      if (func(val)) {
        return "";
      } else {
        return "value is not valid.";
      }
    });
  }

  bool valid(const T &val) const override { return func(val); }

  std::function<bool(const T &val)> func{nullptr};
};

struct file_attr_valid_t : public customize_valid_t<std::string> {
  static std::shared_ptr<file_attr_valid_t> create(
      const std::unordered_set<std::string> &attrs) {
    return std::make_shared<file_attr_valid_t>(attrs);
  }

  file_attr_valid_t(const std::unordered_set<std::string> &attrs)
      : customize_valid_t<std::string>([&](const std::string &file) -> bool {
          auto attr = get_file_suffix(file);
          if (this->members.find(attr) != this->members.end()) {
            return true;
          } else {
            error_msg("file attr([{}]:{}) is not valid. support type: {}", file,
                      attr, this->members);
            return false;
          }
        }),
        members(attrs) {}

  std::unordered_set<std::string> members;
};

template <typename T>
struct counter_valid_t : public params_valid_t<T> {
  static std::shared_ptr<counter_valid_t<T>> create(size_t min_cnt,
                                                    size_t max_cnt) {
    return std::make_shared<counter_valid_t<T>>(min_cnt, max_cnt);
  }
  static std::shared_ptr<counter_valid_t<T>> create(size_t cnt) {
    return std::make_shared<counter_valid_t<T>>(cnt, cnt);
  }

  counter_valid_t(size_t cnt) : cnt_min(cnt), cnt_max(cnt) {}
  counter_valid_t(size_t min_cnt, size_t max_cnt)
      : cnt_min(min_cnt), cnt_max(max_cnt) {}

  void attach(CLI::Option *option) const override {
    option->expected(cnt_min, cnt_max);
  }

  bool valid(const T &val) const override {
    return val.size() >= cnt_min && val.size() <= cnt_max;
  }

  size_t cnt_min, cnt_max;
};

}  // namespace chaos::utils
