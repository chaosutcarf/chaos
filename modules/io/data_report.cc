#include "data_report.h"

#include <fstream>
#include <limits>

#include "utils/logger/logger.h"

namespace chaos::io {

csv_data_report::csv_data_report(const std::string &file,
                                 const std::vector<std::string> &fields)
    : fout(file), num_of_fields(fields.size()) {
  data.resize(num_of_fields);
  for (size_t i = 0; i < data.size(); ++i) {
    std::string current_field = fields[i];
    size_t cnt = 0;
    for (auto iter = maps.find(current_field); iter != maps.end();
         iter = maps.find(current_field)) {
      current_field = fields[i] + "_" + std::to_string(cnt++);
    }
    maps.insert({current_field, &data[i]});
    fout << current_field << ",";
  }
  fout << "\n";
}

csv_data_report::~csv_data_report() {
  flush(true);
  fout.close();
}

void csv_data_report::push(const std::string &tag, double val) {
  auto iter = maps.find(tag);
  if (iter != maps.end()) {
    iter->second->emplace_back(val);
    lazy_flush();
  } else {
    warn_msg("this tag({}) is not a member of the report", tag);
  }
}

void csv_data_report::push(const std::vector<double> &row_entry) {
  //-> assume the order is the same with the fields.
  size_t num_of_entry = row_entry.size();
  if (num_of_entry != num_of_fields) {
    warn_msg(
        "entry size({}) is not match!(should be equal to fields.size():{})",
        num_of_entry, num_of_fields);
  } else {
    //-> assume the same order.
    for (size_t i = 0; i < num_of_entry; ++i) {
      data[i].emplace_back(row_entry[i]);
    }
    lazy_flush();
  }
}

void csv_data_report::flush(bool flush_all) {
  //-> count max_common_row.
  size_t max_cnt = 0;
  if (flush_all) {
    for (size_t i = 0; i < num_of_fields; ++i) {
      max_cnt = std::max(max_cnt, data[i].size());
    }
  } else {
    max_cnt = -1;
    for (size_t i = 0; i < num_of_fields; ++i) {
      max_cnt = std::min(max_cnt, data[i].size());
    }
  }

  for (size_t i = 0; i < max_cnt; ++i) {
    for (size_t j = 0; j < num_of_fields; ++j) {
      if (!data[j].empty()) {
        fout << data[j].front();
        data[j].pop_front();
      }
      fout << ",";
    }
    fout << "\n";
  }
  cnt = 0;
}

void csv_data_report::lazy_flush() {
  cnt++;
  if (cnt > threshold) {
    flush();
  }
}

}  // namespace chaos::io
