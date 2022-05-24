#pragma once

#include <fstream>
#include <list>
#include <map>
#include <string>
#include <vector>

namespace chaos::io {

struct csv_data_report {
  csv_data_report(const std::string &file,
                  const std::vector<std::string> &fields);
  //-> save out data.
  ~csv_data_report();

  void push(const std::vector<double> &row_entry);
  void push(const std::string &tag, double val);

  void set_lazy_flush_threshold(size_t tau) { threshold = tau; }
  void flush(bool flush_all = false);

 protected:
  void lazy_flush();

  std::ofstream fout;
  size_t num_of_fields;
  std::map<std::string, std::list<double> *> maps;
  std::vector<std::list<double>> data;
  size_t cnt{0}, threshold{10};
};

}  // namespace chaos::io
