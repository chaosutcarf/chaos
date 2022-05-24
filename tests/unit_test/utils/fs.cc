#include <catch2/catch.hpp>
#include <fstream>

#include "utils/fs/fshelper.h"

using namespace chaos::utils;

TEST_CASE("test some fs utils", "[fs]") {
  /// check oshelper
  CHECK(get_file_suffix("a.").empty());
  CHECK(get_file_suffix("a.b") == "b");
  CHECK(get_file_suffix("a/b/c.d") == "d");
  CHECK(get_file_suffix(".hidden").empty());

  CHECK(get_file_dir("a.") == "./");
  CHECK(get_file_dir("a/b.c") == "a/");
  CHECK(get_file_dir("/") == "/");

  CHECK(get_file_name("a/b/c.d") == "c");
  CHECK(get_file_name(".a") == ".a");

  CHECK(refine_dir("a\\b\\c\\d") == "a/b/c/d/");

  CHECK(is_dir_exist("."));
  CHECK(is_dir_exist("/"));
  CHECK(is_dir_exist("../modules"));
  CHECK(!is_dir_exist("fuckdir"));

  CHECK(!is_file_exist("fuckfile"));
  std::ofstream fout("fuckfile");
  fout.close();
  CHECK(is_file_exist("fuckfile"));
  CHECK(rm_file("fuckfile") == true);
  CHECK(!is_file_exist("fuckfile"));
  CHECK(rm_file("fuckfile") == true);

  std::vector<std::string> files;
  CHECK(ls_dir(".", files, true, {"cc", "h"}));
  CHECK(ls_dir(".", files, false, {"cc", "h"}));
  CHECK(ls_dir(".", files, false));
  //-> ensure test_dir does not exist.
  CHECK(rm_dir("test_dir"));
  //-> since test_dir does not exists.
  CHECK(!is_dir_exist("test_dir"));
  CHECK(!ls_dir("test_dir", files, true, {"cc", "h"}));

  CHECK(make_dir("test_dir"));
  //-> still return true.
  CHECK(make_dir("test_dir"));
  CHECK(is_dir_exist("test_dir"));
  CHECK(rm_dir("test_dir"));
  CHECK(!is_dir_exist("test_dir"));

  CHECK(concat_dir({"a", "b", "c", "d"}) == "a/b/c/d/");
}
