#pragma once

#include <iterator>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "common/numerical.h"
#include "io/io_basic.h"
#include "io/polyFormat.h"
#include "utils/logger/logger.h"

#define CONSTEXPR_IF(cond, action) \
  if constexpr (!!(cond)) {        \
    action;                        \
  }

#define EXPECT_SIZE_EQUAL(v1, v2) \
  CHAOS_ASSERT((v1).size() == (v2).size(), (v1).size(), (v2).size());

namespace chaos::io {
struct objFormat : public polyFormat {
  enum MODE {
    V_MODE = 1U << 0,
    TC_MODE = 1U << 1,
    VN_MODE = 1U << 2,
    F_MODE = 1U << 3,
    FTC_MODE = 1U << 4,
    FN_MODE = 1U << 5,
    SIMPLE_MODE = V_MODE | F_MODE,
    ALL_MODE = V_MODE | TC_MODE | VN_MODE | F_MODE | FTC_MODE | FN_MODE
  };
  template <int mode = ALL_MODE, typename Scalar = double,
            typename Index = size_t>
  static bool load(const std::string &file, CoordList<Scalar> &V,
                   CoordList<Scalar> &TC, CoordList<Scalar> &VN,
                   FaceList<Index> &F, FaceList<Index> &FTC,
                   FaceList<Index> &FN);

  template <int mode = ALL_MODE, typename Scalar = double,
            typename Index = size_t>
  static bool save(const std::string &file, const CoordList<Scalar> &V,
                   const CoordList<Scalar> &TC, const CoordList<Scalar> &VN,
                   const FaceList<Index> &F, const FaceList<Index> &FTC,
                   const FaceList<Index> &FN);

  template <typename Scalar = double, typename Index = size_t>
  static bool load(const std::string &file, CoordList<Scalar> &V,
                   FaceList<Index> &F);

  template <typename Scalar = double, typename Index = size_t>
  static bool save(const std::string &file, const CoordList<Scalar> &V,
                   const FaceList<Index> &F);

 private:
  template <typename Index>
  inline static void export_f(std::ostream &os, const Face<Index> &f);
  template <typename Index>
  inline static void export_f_ft(std::ostream &os, const Face<Index> &f,
                                 const Face<Index> &ft);
  template <typename Index>
  inline static void export_f_fn(std::ostream &os, const Face<Index> &f,
                                 const Face<Index> &fn);
  template <typename Index>
  inline static void export_f_all(std::ostream &os, const Face<Index> &f,
                                  const Face<Index> &ft, const Face<Index> &fn);
  template <typename Scalar>
  inline static void export_range_v(std::ostream &os,
                                    const CoordList<Scalar> &RangeV,
                                    const std::string &tag);
  template <typename Index, int mode>
  inline static void export_face(std::ostream &os, const FaceList<Index> &F,
                                 const FaceList<Index> &FTC,
                                 const FaceList<Index> &FN);
};

////////////////////////////////////////////////////////////////////////
//                       template implementation                      //
////////////////////////////////////////////////////////////////////////
template <typename Index>
void objFormat::export_f(std::ostream &os, const Face<Index> &f) {
  for (const auto &_ : f) {
    os << _ + 1 << " ";
  }
}

template <typename Index>
void objFormat::export_f_ft(std::ostream &os, const Face<Index> &f,
                            const Face<Index> &ft) {
  EXPECT_SIZE_EQUAL(f, ft);
  for (size_t i = 0; i < f.size(); ++i) {
    os << f[i] + 1 << "/" << ft[i] + 1 << " ";
  }
}

template <typename Index>
void objFormat::export_f_fn(std::ostream &os, const Face<Index> &f,
                            const Face<Index> &fn) {
  EXPECT_SIZE_EQUAL(f, fn);
  for (size_t i = 0; i < f.size(); ++i) {
    os << f[i] + 1 << "//" << fn[i] + 1 << " ";
  }
}

template <typename Index>
void objFormat::export_f_all(std::ostream &os, const Face<Index> &f,
                             const Face<Index> &ft, const Face<Index> &fn) {
  EXPECT_SIZE_EQUAL(f, ft);
  EXPECT_SIZE_EQUAL(f, fn);
  for (size_t i = 0; i < f.size(); ++i) {
    os << f[i] + 1 << "/" << ft[i] + 1 << "/" << fn[i] + 1 << " ";
  }
}

template <typename Index, int mode>
void objFormat::export_face(std::ostream &os, const FaceList<Index> &F,
                            const FaceList<Index> &FTC,
                            const FaceList<Index> &FN) {
  if constexpr (!!(mode & F_MODE)) {
    const auto &f_num = F.size();
    os << "# [meshinfo] faces: " << f_num << "\n";
    CONSTEXPR_IF(mode & FTC_MODE, EXPECT_SIZE_EQUAL(F, FTC));
    CONSTEXPR_IF(mode & FN_MODE, EXPECT_SIZE_EQUAL(F, FN));
    for (size_t i = 0; i < f_num; ++i) {
      os << "f ";
      if constexpr (!!(mode & FTC_MODE) && !!(mode & FN_MODE)) {
        export_f_all(os, F[i], FTC[i], FN[i]);
      } else if constexpr (!!(mode & FTC_MODE)) {
        export_f_ft(os, F[i], FTC[i]);
      } else if constexpr (!!(mode & FN_MODE)) {
        export_f_fn(os, F[i], FN[i]);
      } else {
        export_f(os, F[i]);
      }
      os << "\n";
    }
  }
}

template <typename Scalar>
void objFormat::export_range_v(std::ostream &os,
                               const CoordList<Scalar> &RangeV,
                               const std::string &tag) {
  os << "# [meshinfo] " << tag << ": " << RangeV.size() << "\n";
  for (const auto &Coord : RangeV) {
    os << tag << " ";
    for (const auto &c : Coord) {
      os << c << " ";
    }
    os << "\n";
  }
}

template <typename Scalar, typename Index>
inline bool objFormat::load(const std::string &file, CoordList<Scalar> &V,
                            FaceList<Index> &F) {
  CoordList<Scalar> _v;
  FaceList<Index> _f;
  return load<SIMPLE_MODE>(file, V, _v, _v, F, _f, _f);
}

template <typename Scalar, typename Index>
inline bool objFormat::save(const std::string &file, const CoordList<Scalar> &V,
                            const FaceList<Index> &F) {
  CoordList<Scalar> _v;
  FaceList<Index> _f;
  return save<SIMPLE_MODE>(file, V, _v, _v, F, _f, _f);
}

template <int mode, typename Scalar, typename Index>
bool objFormat::load(const std::string &file, CoordList<Scalar> &V,
                     CoordList<Scalar> &TC, CoordList<Scalar> &VN,
                     FaceList<Index> &F, FaceList<Index> &FTC,
                     FaceList<Index> &FN) {
  size_t line_number = 0;
  return with_readlines(file, [&](const std::string &line) {
    line_number++;
    std::string tag;
    //-> WTD if the line is an empty line?
    std::istringstream ss(line);
    ss >> tag;
    if (tag.empty() || tag[0] == '#') {
      return;
    }
    CONSTEXPR_IF(
        mode & V_MODE, if (tag == "v") {
          V.emplace_back(std::istream_iterator<Scalar>(ss),
                         std::istream_iterator<Scalar>());
          return;
        });
    CONSTEXPR_IF(
        mode & TC_MODE, if (tag == "vt") {
          TC.emplace_back(std::istream_iterator<Scalar>(ss),
                          std::istream_iterator<Scalar>());
          return;
        });
    CONSTEXPR_IF(
        mode & VN_MODE, if (tag == "vn") {
          VN.emplace_back(std::istream_iterator<Scalar>(ss),
                          std::istream_iterator<Scalar>());
          return;
        });
    if (tag == "f") {
      std::string face_id_term;
      Face<Index> f, ftc, fn;
      while (ss >> face_id_term) {
        long i{-1}, it{-1}, in{-1};
        if (sscanf(face_id_term.c_str(), "%ld/%ld/%ld", &i, &it, &in) == 3 ||
            sscanf(face_id_term.c_str(), "%ld/%ld", &i, &it) == 2 ||
            sscanf(face_id_term.c_str(), "%ld//%ld", &i, &in) == 2 ||
            sscanf(face_id_term.c_str(), "%ld", &i) == 1) {
          CONSTEXPR_IF(
              mode & F_MODE, if (i != -1) { f.emplace_back(i - 1); });
          CONSTEXPR_IF(
              mode & FTC_MODE, if (it != -1) { ftc.emplace_back(it - 1); });
          CONSTEXPR_IF(
              mode & FN_MODE, if (in != -1) { fn.emplace_back(in - 1); });
        } else {
          error_msg("obj load face on line#{} has invalid element format<{}>",
                    line_number, line);
        }
      }
      CONSTEXPR_IF(
          mode & F_MODE, if (!f.empty()) { F.emplace_back(f); });
      CONSTEXPR_IF(
          mode & FTC_MODE, if (!ftc.empty()) { FTC.emplace_back(ftc); });
      CONSTEXPR_IF(
          mode & FN_MODE, if (!fn.empty()) { FN.emplace_back(fn); });
    }
  });
}

template <int mode, typename Scalar, typename Index>
bool objFormat::save(const std::string &file, const CoordList<Scalar> &V,
                     const CoordList<Scalar> &TC, const CoordList<Scalar> &VN,
                     const FaceList<Index> &F, const FaceList<Index> &FTC,
                     const FaceList<Index> &FN) {
  return with_write(file, [&](std::ostream &os) {
    os.precision(numerical::constant<Scalar>::precision);
    CONSTEXPR_IF(mode & V_MODE, export_range_v(os, V, "v"));
    CONSTEXPR_IF(mode & TC_MODE, export_range_v(os, TC, "vt"));
    CONSTEXPR_IF(mode & VN_MODE, export_range_v(os, VN, "vn"));
    export_face<Index, mode>(os, F, FTC, FN);
  });
}
}  // namespace chaos::io
#undef CONSTEXPR_IF
#undef EXPECT_SIZE_EQUAL
