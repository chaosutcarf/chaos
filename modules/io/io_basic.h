#pragma once

#include <exception>
#include <fstream>
#include <istream>
#include <string>
#include <type_traits>

#include "utils/logger/logger.h"

namespace chaos::io {
template <typename LineCallback>
bool with_readlines(std::istream &is, const LineCallback &cb);

template <typename LineCallback>
bool with_readlines(const std::string &file, const LineCallback &cb);

template <typename StreamCallback>
bool with_open(const std::string &file, const StreamCallback &cb,
               const std::fstream::openmode &mode = std::fstream::in |
                                                    std::fstream::out |
                                                    std::fstream::app);

template <typename StreamCallback>
bool with_read(const std::string &file, const StreamCallback &cb);
template <typename StreamCallback>
bool with_write(const std::string &file, const StreamCallback &cb);
template <typename StreamCallback>
bool with_append(const std::string &file, const StreamCallback &cb);
template <typename StreamCallback>
bool with_read_binary(const std::string &file, const StreamCallback &cb);
template <typename StreamCallback>
bool with_write_binary(const std::string &file, const StreamCallback &cb);
template <typename StreamCallback>
bool with_append_binary(const std::string &file, const StreamCallback &cb);

bool nextline(std::istream &is, std::string &line, char delim = '\n');

////////////////////////////////////////////////////////////////////////
//                       template implementation                      //
////////////////////////////////////////////////////////////////////////
inline bool nextline(std::istream &is, std::string &line, char delim) {
  if (is.eof() || is.peek() == -1) {
    return false;
  } else if (is.peek() == delim) {
    is.ignore();
    line = "";
  } else {
    std::getline(is, line);
  }
  return true;
}

template <typename LineCallback>
inline bool with_readlines(std::istream &is, const LineCallback &cb) {
  std::string line;
  bool ret = true;
  while (nextline(is, line)) {
    if constexpr (std::is_same_v<typename std::invoke_result_t<LineCallback,
                                                               std::string &>,
                                 bool>) {
      ret |= cb(line);
    } else {
      cb(line);
    }
  }
  return ret;
}

template <typename LineCallback>
inline bool with_readlines(const std::string &file, const LineCallback &cb) {
  return with_read(file, [&cb](auto &is) { return with_readlines(is, cb); });
}

template <typename StreamCallback>
inline bool with_open(const std::string &file, const StreamCallback &cb,
                      const std::fstream::openmode &mode) {
  constexpr const char *state[]{"fileopen", "fileprocess", "fileclose"};
  int cnt = 0;
  try {
    std::fstream fs(file, mode);
    fs.exceptions(std::fstream::failbit | std::fstream::badbit);
    bool ret = true;
    cnt++;
    if constexpr (std::is_same_v<typename std::invoke_result_t<StreamCallback,
                                                               std::fstream &>,
                                 bool>) {
      ret = cb(fs);
    } else {
      cb(fs);
    }
    cnt++;
    fs.close();
    return ret;
  } catch (std::exception &e) {
    error_msg("with_open({})<m:{}>[{}]->{}", state[cnt], mode, file, e.what());
    return false;
  }
}

template <typename StreamCallback>
inline bool with_read(const std::string &file, const StreamCallback &cb) {
  return with_open(file, cb, std::ios_base::in);
}

template <typename StreamCallback>
inline bool with_write(const std::string &file, const StreamCallback &cb) {
  return with_open(file, cb, std::ios_base::out);
}

template <typename StreamCallback>
inline bool with_append(const std::string &file, const StreamCallback &cb) {
  return with_open(file, cb, std::ios_base::app);
}

template <typename StreamCallback>
inline bool with_read_binary(const std::string &file,
                             const StreamCallback &cb) {
  return with_open(file, cb, std::ios_base::in | std::ios_base::binary);
}

template <typename StreamCallback>
inline bool with_write_binary(const std::string &file,
                              const StreamCallback &cb) {
  return with_open(file, cb, std::ios_base::out | std::ios_base::binary);
}

template <typename StreamCallback>
inline bool with_append_binary(const std::string &file,
                               const StreamCallback &cb) {
  return with_open(file, cb, std::ios_base::app | std::ios_base::binary);
}

}  // namespace chaos::io
