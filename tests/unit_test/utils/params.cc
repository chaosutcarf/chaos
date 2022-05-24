#include "utils/params/params.h"

#include <catch2/catch.hpp>
#include <fstream>

#include "common/numerical.h"
#include "common/type.h"
#include "utils/params/valid.h"

using namespace chaos;
using namespace chaos::utils;

TEST_CASE("test params common usage", "[utils::params]") {
  struct test_params_t : public params_group_t {
    test_params_t() : utils::params_group_t("", "test description") {
      //-> register member params.
      prms.emplace_back(&i);
      prms.emplace_back(&d);
    }

    DEFINE_PARAM_DEFAULT(int, i, "integer", 1);
    DEFINE_PARAM_REQUIRED(double, d, "double required");
  };
  CLI::App app("test app");
  test_params_t prm;
  SECTION("test common usage") {
    prm.attach(&app);
    SECTION("wo required params") {
      const char* argv[] = {"exec"};
      const int argc = sizeof(argv) / sizeof(argv[0]);
      CHECK_THROWS(app.parse(argc, argv));
    }

    SECTION("wo default params, with required params") {
      const char* argv[] = {"exec", "--d=2.0"};
      const int argc = sizeof(argv) / sizeof(argv[0]);
      CHECK_NOTHROW(app.parse(argc, argv));
      CHECK(chaos::numerical::near<double>(prm.d, 2.0));
      CHECK(prm.i == 1);
    }

    SECTION("with default params and with required params") {
      const char* argv[] = {"exec", "--d=2.0", "--i=20"};
      const int argc = sizeof(argv) / sizeof(argv[0]);
      CHECK_NOTHROW(app.parse(argc, argv));
      CHECK(chaos::numerical::near<double>(prm.d, 2.0));
      CHECK(prm.i == 20);
    }
  }

  SECTION("test common usage with name") {
    prm.name = "test";
    prm.attach(&app);
    SECTION("wo required params") {
      const char* argv[] = {"exec", "test"};
      const int argc = sizeof(argv) / sizeof(argv[0]);
      CHECK_THROWS(app.parse(argc, argv));
    }

    SECTION("wo default params, with required params") {
      const char* argv[] = {"exec", "test", "--d=2.0"};
      const int argc = sizeof(argv) / sizeof(argv[0]);
      CHECK_NOTHROW(app.parse(argc, argv));
      CHECK(chaos::numerical::near<double>(prm.d, 2.0));
      CHECK(prm.i == 1);
    }

    SECTION("with default params and with required params") {
      const char* argv[] = {"exec", "test", "--d=2.0", "--i=20"};
      const int argc = sizeof(argv) / sizeof(argv[0]);
      CHECK_NOTHROW(app.parse(argc, argv));
      CHECK(chaos::numerical::near<double>(prm.d, 2.0));
      CHECK(prm.i == 20);
    }
  }

  SECTION("test dump and load") {
    prm.attach(&app);
    const char* argv[] = {"exec", "--d=2.0", "--i=20"};
    const int argc = sizeof(argv) / sizeof(argv[0]);
    CHECK_NOTHROW(app.parse(argc, argv));
    CHECK(chaos::numerical::near<double>(prm.d, 2.0));
    CHECK(prm.i == 20);
    dump_config(&app, "test_config.toml");
    dump_config_chdir(&app, "test_config_with_dir.toml");
    CHAOS_ASSERT(chdir("..") == 0);

    prm.i.set_val(10);
    prm.d.set_val(1.0);
    {
      const char* argv[] = {"exec", "--config=test_config.toml"};
      const int argc = sizeof(argv) / sizeof(argv[0]);
      DEFINE_CONFIG_APP(config_app, "read params from config file", &prm);
      CHECK(prm.i == 20);
      CHECK(chaos::numerical::near<double>(prm.d, 2.0));
    }
  }
}

TEST_CASE("test valids", "[utils::params]") {
  struct empty_valid_t : public params_valid_t<int> {
    bool valid(const int&) const override { return true; }
  };
  struct test_params_t : public params_group_t {
    enum test_enum_type { A, B };
    test_params_t() : utils::params_group_t("", "test desc") {
      emplace_back({&in_file, &number, &type, &range_number, &con_types});

      in_file.add_valid(file_exist_valid_t::create());
      in_file.add_valid({file_attr_valid_t::create({"txt"})});
      number.add_valid(customize_valid_t<int>::create(
          [](const int& val) { return val == 1; }));
      type.add_valid(
          enum_transform_valid_t<test_enum_type>::create({{"A", A}, {"B", B}}));
      range_number.add_valid(range_valid_t<int>::create(0));
      number.add_valid(std::make_shared<empty_valid_t>());
      con_types.add_valid(
          container_element_valid_t<std::vector<test_enum_type>,
                                    enum_transform_valid_t<test_enum_type>>::
              create(enum_transform_valid_t<test_enum_type>::create(
                  {{"A", A}, {"B", B}})));
    }

    DEFINE_PARAM_DEFAULT(std::string, in_file, "input file", "");
    DEFINE_PARAM_DEFAULT(int, number, "number", 1);
    DEFINE_PARAM_DEFAULT(test_enum_type, type, "enum type", A);
    DEFINE_PARAM_DEFAULT(int, range_number, "range number", 1);
    DEFINE_PARAM_DEFAULT(std::vector<test_enum_type>, con_types,
                         "container types",
                         std::vector<test_enum_type>({A, B}));
  };

  CLI::App app("test app");
  test_params_t prm;
  prm.attach(&app);

  CHECK(!prm.valid());
  CHECK(!prm.number.set_val(2));
  prm.number.val = 2;
  CHECK_THROWS(prm.number.get_val());
  CHECK(prm.number.set_val(1));

  //-> create file.
  std::string filename("test_file_exist.txt");
  std::ofstream fout(filename);
  fout.close();
  SECTION("valid params") {
    SECTION("case1") {
      const char* const argv[] = {"exec", "--in_file", filename.c_str()};
      const int argc = sizeof(argv) / sizeof(argv[0]);
      CHECK_NOTHROW(app.parse(argc, argv));
      CHECK(prm.in_file.val == filename);
      CHECK(prm.valid());
    }
    SECTION("case2") {
      const char* const argv[] = {"exec", "--in_file", filename.c_str(),
                                  "--type", "A"};
      const int argc = sizeof(argv) / sizeof(argv[0]);
      CHECK_NOTHROW(app.parse(argc, argv));
      CHECK(prm.type == test_params_t::A);
      CHECK(prm.valid());
    }
    SECTION("case3") {
      const char* const argv[] = {"exec", "--in_file", filename.c_str(),
                                  "--type", "B"};
      const int argc = sizeof(argv) / sizeof(argv[0]);
      CHECK_NOTHROW(app.parse(argc, argv));
      CHECK(prm.type == test_params_t::B);
      CHECK(prm.valid());
    }
    SECTION("case4") {
      const char* const argv[] = {"exec", "--in_file", filename.c_str(),
                                  "--type", "0"};
      const int argc = sizeof(argv) / sizeof(argv[0]);
      CHECK_NOTHROW(app.parse(argc, argv));
      CHECK(prm.type == test_params_t::A);
      CHECK(prm.valid());
    }
    SECTION("case5") {
      const char* const argv[] = {"exec", "--in_file", filename.c_str(),
                                  "--type", "1"};
      const int argc = sizeof(argv) / sizeof(argv[0]);
      CHECK_NOTHROW(app.parse(argc, argv));
      CHECK(prm.type == test_params_t::B);
      CHECK(prm.valid());
    }
    SECTION("case6") {
      const char* const argv[] = {"exec", "--in_file", filename.c_str(),
                                  "--type", "a"};
      const int argc = sizeof(argv) / sizeof(argv[0]);
      CHECK_NOTHROW(app.parse(argc, argv));
      CHECK(prm.type == test_params_t::A);
      CHECK(prm.valid());
    }
    SECTION("case7") {
      const char* const argv[] = {"exec",   "--in_file", filename.c_str(),
                                  "--type", "b",         "--number",
                                  "1"};
      const int argc = sizeof(argv) / sizeof(argv[0]);
      CHECK_NOTHROW(app.parse(argc, argv));
      CHECK(prm.type == test_params_t::B);
      CHECK(prm.number == 1);
      CHECK(prm.valid());
    }
    SECTION("case8") {
      const char* const argv[] = {"exec",   "--in_file",   filename.c_str(),
                                  "--type", "b",           "--number",
                                  "1",      "--con_types", "[a,b,a]"};
      const int argc = sizeof(argv) / sizeof(argv[0]);
      CHECK_NOTHROW(app.parse(argc, argv));
      prm.con_types.get_val();
    }
  }

  SECTION("invalid params") {
    SECTION("case1") {
      const char* const argv[] = {"exec", "--in_file", "not_exist_file.txt"};
      const int argc = sizeof(argv) / sizeof(argv[0]);
      CHECK_THROWS(app.parse(argc, argv));
    }
    SECTION("case2") {
      std::ofstream fout("no_attr_file");
      fout.close();
      const char* const argv[] = {"exec", "--in_file", "no_attr_file"};
      const int argc = sizeof(argv) / sizeof(argv[0]);
      CHECK_THROWS(app.parse(argc, argv));
    }
    SECTION("case3") {
      const char* const argv[] = {"exec", "--in_file", filename.c_str(),
                                  "--type", "C"};
      const int argc = sizeof(argv) / sizeof(argv[0]);
      CHECK_THROWS(app.parse(argc, argv));
    }
    SECTION("case3") {
      const char* const argv[] = {"exec", "--in_file", filename.c_str(),
                                  "--number", "2"};
      const int argc = sizeof(argv) / sizeof(argv[0]);
      CHECK_THROWS(app.parse(argc, argv));
    }
  }
}

TEST_CASE("test params_desc not attach cli", "[params]") {
  struct prm_t : public params_desc_t {
    prm_t() : params_desc_t("", "", false) {}
    bool valid() const override { return true; }
  } prm;
  CLI::App app;
  CHECK_NOTHROW(prm.attach(&app));
}
