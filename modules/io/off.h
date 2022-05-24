#pragma once

#include <cstddef>
#include <istream>
#include <sstream>
#include <string>

#include "common/numerical.h"
#include "io/io_basic.h"
#include "io/polyFormat.h"
#include "utils/logger/logger.h"

namespace chaos::io {
struct offFormat : public polyFormat {
  template <typename Scalar = double, typename Index = size_t>
  static bool load(const std::string &file, CoordList<Scalar> &V,
                   FaceList<Index> &F);

  template <typename Scalar = double, typename Index = size_t>
  static bool save(const std::string &file, const CoordList<Scalar> &V,
                   const FaceList<Index> &F);

 private:
  static bool load_header(std::istream &is, size_t &numV, size_t &numF);
  template <typename Scalar>
  static bool load_vertices(std::istream &is, const size_t numV,
                            CoordList<Scalar> &V);
  template <typename Index>
  static bool load_faces(std::istream &is, const size_t numF,
                         FaceList<Index> &F);
  static bool skip_comments(std::istream &is);
};

////////////////////////////////////////////////////////////////////////
//                       template implementation                      //
////////////////////////////////////////////////////////////////////////
template <typename Scalar>
bool offFormat::load_vertices(std::istream &is, const size_t numV,
                              CoordList<Scalar> &V) {
  V.reserve(numV);
  for (size_t i = 0; i < numV; ++i) {
    if (skip_comments(is)) {
      std::string line;
      std::getline(is, line);
      std::istringstream ss(line);
      Scalar x, y, z;
      ss >> x >> y >> z;
      V.emplace_back(Coord<Scalar>{x, y, z});
    } else {
      return false;
    }
  }
  return V.size() == numV;
}

template <typename Index>
bool offFormat::load_faces(std::istream &is, const size_t numF,
                           FaceList<Index> &F) {
  F.reserve(numF);
  for (size_t i = 0; i < numF; ++i) {
    if (skip_comments(is)) {
      std::string line;
      std::getline(is, line);
      std::istringstream ss(line);
      size_t num;
      ss >> num;
      Face<Index> face(num);
      for (size_t j = 0; j < num; ++j) {
        ss >> face[j];
      }
      F.emplace_back(face);
    } else {
      return false;
    }
  }
  return F.size() == numF;
}

template <typename Scalar, typename Index>
bool offFormat::load(const std::string &file, CoordList<Scalar> &V,
                     FaceList<Index> &F) {
  return with_read(file, [&](std::istream &is) {
    size_t numV, numF;
    if (load_header(is, numV, numF)) {
      V.reserve(numV);
      F.reserve(numF);
      //-> load V and F.
      return load_vertices(is, numV, V) && load_faces(is, numF, F);
    } else {
      return false;
    }
  });
}

inline bool offFormat::skip_comments(std::istream &is) {
  bool ret = true;
  while (true) {
    if (is.eof() || is.peek() == -1) {
      ret = false;
      break;
    }
    char tag = is.peek();
    if (tag == '#') {
      std::string line;
      std::getline(is, line);
    } else if (tag == ' ' || tag == '\n' || tag == '\t') {
      is.ignore();
    } else {
      break;
    }
  }
  return ret;
}

inline bool offFormat::load_header(std::istream &is, size_t &numV,
                                   size_t &numF) {
  // load version tag.
  std::string off_type;
  is >> off_type;
  error_msg_handler_if(return false, off_type != "OFF",
                              "{} is not support. only support standard OFF.",
                              off_type);

  // load # of vertices and # of faces.
  //-> 1. skip comments and BINARY configuration.
  skip_comments(is);
  error_msg_handler_if(return false, is.peek() == 'B',
                              "BINARY is not support.");

  //-> 2. parse NumVertices and NumFaces.
  std::string line;
  std::getline(is, line);
  std::stringstream ss(line);
  ss >> numV >> numF;
  return true;
}

template <typename Scalar, typename Index>
bool offFormat::save(const std::string &file, const CoordList<Scalar> &V,
                     const FaceList<Index> &F) {
  return with_write(file, [&](std::ostream &os) {
    os << "OFF\n" << V.size() << " " << F.size() << " 0\n";
    os.precision(numerical::constant<Scalar>::precision);
    //-> export nodes.
    for (const auto &node : V) {
      for (const auto &p : node) {
        os << p << " ";
      }
      os << "\n";
    }
    //-> export faces.
    for (const auto &face : F) {
      os << face.size();
      for (const auto &f : face) {
        os << " " << f;
      }
      os << "\n";
    }
  });
}

}  // namespace chaos::io
