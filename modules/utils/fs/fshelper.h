/** -*- mode: c++ -*-
 * @file fshelper.h
 * @author LamKamhang (Cool_Lam@outlook.com)
 * @brief A Documented file.
 * @version 1.0
 * @date Monday, January 04, 2021 PM01:47:23 CST
 *
 * Detailed description
 *
 *
 * @copyright Copyright (c) 2021
 */
#pragma once

#include <initializer_list>
#include <set>
#include <string>
#include <vector>

namespace chaos::utils {
/**
 * @brief      get_file_suffix
 * @details    get the suffix name of the file
 * @param      file_name
 * @return     return the suffix without "."
 * example 1 : input:  "a.txt"
 *             output: "txt"
 * example 2: input:  "a"
 *            output: ""
 */
std::string get_file_suffix(const std::string &file);
/**
 * @brief      get_file_dir
 * @details    get the dir name of the file
 * @param      file_name
 * @return     return the dir with "/"
 * example 1 : input:  "a.txt"
 *             output: "./"
 * example 2: input:  "/"
 *            output: "/"
 */
std::string get_file_dir(const std::string &file);
/**
 * @brief      get_file_name
 * @details    get the name of the file
 * @param      file_name
 * @return     return the name
 * example 1 : input:  "a.txt"
 *             output: "a"
 * example 2: input:  ".hidden_file"
 *            output: ".hidden_file"
 * example 3: input:  "/dir/file.txt"
 *            output: "file"
 */
std::string get_file_name(const std::string &file);
std::string concat_dir(const std::initializer_list<std::string> &dirs);
std::string refine_dir(const std::string &dir);
bool is_dir_exist(const std::string &dir);
bool is_file_exist(const std::string &path);
bool rm_file(const std::string &path);
bool make_dir(const std::string &dir);
bool rm_dir(const std::string &dir);
bool ls_dir(const std::string &dir, std::vector<std::string> &files,
            bool do_recursive = false,
            const std::set<std::string> &interest_suffixs = {});
}  // namespace chaos::utils
