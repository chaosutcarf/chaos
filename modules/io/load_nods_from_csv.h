#pragma once

#include <string>
#include <vector>

#include "common/type.h"
#include "io/io_basic.h"
namespace chaos::io {

template <typename Index>
bool load_nods_from_csv(const std::string &csv_file,
                        std::map<Index, vecxr_t> &id_nods, char delim = ',',
                        bool ignore_headerline = true);

template <typename Index>
bool load_nods_from_csv(const std::string &csv_file, std::vector<Index> &ids,
                        std::vector<vecxr_t> &nods, char delim = ',',
                        bool ignore_headerline = true);

////////////////////////////////////////////////////////////////////////
//                       template implementation                      //
////////////////////////////////////////////////////////////////////////
namespace details {
template <typename Index, typename Inserter>
bool load_nods_from_csv(const std::string &csv_file, char delim,
                        bool ignore_headerline, const Inserter &insert) {
  return with_read(csv_file, [&insert, &ignore_headerline,
                              &delim](std::istream &fin) {
    if (ignore_headerline) {
      std::string headerline;
      std::getline(fin, headerline);
      debug_msg("ignore header line: {}", headerline);
    }
    //-> TODO. check format.
    return io::with_readlines(fin, [&insert, &delim](const std::string &line) {
      Index id;
      //-> at most 3.
      real_t pos[3];
      //-> parse id first.
      auto end = line.find(delim, 0);
      if (end == std::string::npos) {
        return false;
      }
      id = std::stoul(line.substr(0, end));
      auto beg = end + 1;
      int i;
      for (i = 0; i < 3 && end != std::string::npos; ++i, beg = end + 1) {
        end = line.find(delim, beg);
        pos[i] = std::stod(line.substr(beg, end));
      }
      //-> less then 2 is not valid.
      if (i < 2) {
        return false;
      } else {
        insert(id, Eigen::Map<vecxr_t>(pos, i));
        return true;
      }
    });
  });
}
}  // namespace details

template <typename Index>
bool load_nods_from_csv(const std::string &csv_file,
                        std::map<Index, vecxr_t> &id_nods, char delim,
                        bool ignore_headerline) {
  return details::load_nods_from_csv<Index>(
      csv_file, delim, ignore_headerline,
      [&id_nods](Index id, const Eigen::Ref<const vecxr_t> &pos) {
        id_nods.insert({id, pos});
      });
}

template <typename Index>
bool load_nods_from_csv(const std::string &csv_file, std::vector<Index> &ids,
                        std::vector<vecxr_t> &nods, char delim,
                        bool ignore_headerline) {
  return details::load_nods_from_csv<Index>(
      csv_file, delim, ignore_headerline,
      [&ids, &nods](Index id, const Eigen::Ref<const vecxr_t> &pos) {
        ids.emplace_back(id);
        nods.emplace_back(pos);
      });
}
}  // namespace chaos::io
