/** -*- mode: c++ -*-
 * @file fshelper.cc
 * @author LamKamhang (Cool_Lam@outlook.com)
 * @brief A Documented file.
 * @version 1.0
 * @date Monday, June 28, 2021 PM06:43:12 HKT
 *
 * Detailed description
 *
 *
 * @copyright Copyright (c) 2021
 */
#include "fshelper.h"

#include <filesystem>
#include <optional>

#include "utils/logger/logger.h"

namespace fs = std::filesystem;

namespace chaos::utils {

std::string get_file_suffix(const std::string &file) {
  size_t pos = file.find_last_of('.');
  if (pos == std::string::npos || pos == 0) {
    return "";
  } else {
    return file.substr(pos + 1);
  }
}

std::string get_file_dir(const std::string &file) {
  size_t pos = file.find_last_of('/');
  if (pos == std::string::npos) {
    return "./";
  } else {
    return file.substr(0, pos + 1);
  }
}

std::string get_file_name(const std::string &file) {
  static_assert(std::string::npos == -1);
  std::string res = file.substr(file.find_last_of('/') + 1);
  size_t pos = res.find_last_of('.');
  if (pos == 0) {
    pos = std::string::npos;
  }
  return res.substr(0, pos);
}

std::string concat_dir(const std::initializer_list<std::string> &dirs) {
  std::string result_dir;
  for (const auto &dir : dirs) {
    result_dir += refine_dir(dir);
  }
  return result_dir;
}

std::string refine_dir(const std::string &dir) {
  std::string res(dir);
  for (size_t pos = res.find('\\'); pos != std::string::npos;
       pos = res.find('\\')) {
    res.replace(pos, 1, "/");
  }
  if (res[res.length() - 1] != '/') {
    res.push_back('/');
  }
  return res;
}

bool is_dir_exist(const std::string &dir) {
  return fs::exists(dir) && fs::is_directory(dir);
}

bool is_file_exist(const std::string &path) { return fs::exists(path); }

bool make_dir(const std::string &dir) {
  if (!is_dir_exist(dir)) {
    return fs::create_directories(dir);
  } else {
    return true;
  }
}

bool rm_file(const std::string &path) {
  if (fs::exists(path)) {
    return fs::remove(path);
  } else {
    return true;
  }
}

bool rm_dir(const std::string &dir) {
  if (is_dir_exist(dir)) {
    return fs::remove(dir);
  } else {
    return true;
  }
}

bool ls_dir(const std::string &dir, std::vector<std::string> &files,
            bool do_recursive, const std::set<std::string> &interest_suffixs) {
  if (!is_dir_exist(dir)) {
    warn_msg("dir<{}> does not exist.", dir);
    return false;
  } else {
    const auto &collect_files =
        [&files, &interest_suffixs](const fs::directory_entry &p) {
          const auto &name{p.path().string()};
          const auto &suffix{get_file_suffix(name)};
          if (interest_suffixs.empty() ||
              interest_suffixs.find(suffix) != interest_suffixs.end()) {
            files.emplace_back(name);
          }
        };
    if (do_recursive) {
      for (auto &p : fs::recursive_directory_iterator(dir)) {
        collect_files(p);
      }
    } else {
      for (auto &p : fs::directory_iterator(dir)) {
        collect_files(p);
      }
    }
    return true;
  }
}
}  // namespace chaos::utils
