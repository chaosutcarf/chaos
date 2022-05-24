#pragma once
#include <unistd.h>

#include <CLI/CLI.hpp>
#include <cstddef>
#include <fstream>
#include <initializer_list>
#include <limits>
#include <memory>
#include <ostream>
#include <string>
#include <unordered_set>

#include "utils/logger/logger.h"
#include "utils/params/valid.h"

namespace chaos::utils {
inline void dump_config(const CLI::App *app, const std::string &dump_file) {
  if (app) {
    std::ofstream fout(dump_file);
    fout << app->config_to_str(true, true);
    fout.close();
  }
}

inline void dump_config_chdir(const CLI::App *app,
                              const std::string &dump_file) {
  if (app) {
    const std::string config_content = app->config_to_str(true, true);
    size_t str_hash = std::hash<std::string>{}(config_content);
    std::string folder(std::to_string(str_hash));
    make_dir(folder);
    warn_msg_if(chdir(folder.c_str()) != 0,
                "cannot change working directory: {}", folder);
    std::ofstream fout(dump_file);
    fout << config_content;
    fout.close();
  }
}

struct params_desc_t {
  params_desc_t(const std::string &name, const std::string &desc, bool required)
      : name(name), desc(desc), required(required) {}
  virtual ~params_desc_t() {}
  virtual CLI::App *attach(CLI::App *app) {
    warn_msg("not attach to CLI.");
    return app;
  }
  virtual bool valid() const = 0;
  virtual void setup_complete_callback() {}
  void attach_with_callback(CLI::App *app) {
    attach(app);
    app->final_callback([this]() { setup_complete_callback(); });
  }

  std::string name, desc;
  bool required{false};
};

struct params_group_t : public params_desc_t {
  params_group_t(const std::string &group = "", const std::string &desc = "")
      : params_desc_t(group, desc, false) {}

  CLI::App *attach(CLI::App *app) override {
    if (!name.empty() && !prms.empty()) {
      app = app->add_subcommand(name, desc);
    }

    for (auto &p : prms) {
      p->attach(app);
    }

    return app;
  }

  //-> denote as final to avoid overriding a misunderstanding function.
  void setup_complete_callback() final {
    for (auto &p : prms) {
      p->setup_complete_callback();
    }
    group_setup_complete_callback();
  }

  virtual void group_setup_complete_callback() {}

  bool valid() const override {
    bool ret{true};
    for (auto &p : prms) {
      ret &= p->valid();
    }
    return ret;
  }
  void emplace_back(params_desc_t *prm) {
    if (prm != nullptr) {
      prms.emplace_back(prm);
    }
  }

  void emplace_back(const std::vector<params_desc_t *> &ps) {
    for (const auto &p : ps) {
      emplace_back(p);
    }
  }

 protected:
  std::vector<params_desc_t *> prms;
};

template <typename T>
struct basetype_desc_t : public params_desc_t {
  basetype_desc_t(
      const std::string &name, const std::string &desc,
      const std::vector<std::shared_ptr<params_valid_t<T>>> &valids = {})
      : params_desc_t(name, desc, true), valids(valids) {}

  basetype_desc_t(
      const std::string &name, const std::string &desc, const T &default_val,
      const std::vector<std::shared_ptr<params_valid_t<T>>> &valids = {})
      : params_desc_t(name, desc, false), val(default_val), valids(valids) {}

  CLI::App *attach(CLI::App *app) override {
    auto &&option = app->add_option("--" + name, val, desc);
    if (required) {
      option->required();
    } else {
      option->default_val(val);
    }
    //-> setup valids.
    for (const auto &pv : valids) {
      pv->attach(option);
    }
    return app;
  }

  void add_valid(const std::shared_ptr<params_valid_t<T>> &valid) {
    valids.emplace_back(std::move(valid));
  }

  void add_valid(
      const std::initializer_list<std::shared_ptr<params_valid_t<T>>> &valids) {
    for (const auto &v : valids) {
      add_valid(v);
    }
  }

  bool set_val(const T &val) {
    if (valid(val)) {
      this->val = val;
      return true;
    } else {
      return false;
    }
  }

  bool valid(const T &val) const {
    for (const auto &pv : valids) {
      if (!pv->valid(val)) {
        return false;
      }
    }
    return true;
  }

  bool valid() const override { return valid(val); }

  const T &get_val() const {
    CHAOS_DEBUG_ASSERT(valid(val), name);
    return val;
  }

  operator const T &() const { return get_val(); }
  basetype_desc_t<T> &operator=(const T &val) {
    set_val(val);
    return *this;
  }

  T val;
  std::vector<std::shared_ptr<params_valid_t<T>>> valids;
};
}  // namespace chaos::utils

#define DEFINE_PARAM_DEFAULT(type, name, desc, value) \
  chaos::utils::basetype_desc_t<type> name{#name, desc, value};

#define DEFINE_PARAM_REQUIRED(type, name, desc) \
  chaos::utils::basetype_desc_t<type> name{#name, desc};

#define PARSE_APP_PRM(app_name, prm)      \
  (prm)->attach_with_callback(&app_name); \
  try {                                   \
    (app_name).parse((argc), (argv));     \
  } catch (const CLI::ParseError &e) {    \
    exit((app_name).exit(e));             \
  }

#define DEFINE_CONFIG_APP(app_name, desc, prm)                       \
  CLI::App app_name(desc);                                           \
  (app_name).set_config("--config", "config.toml");                  \
  (app_name).set_help_all_flag("--help-all", "show all help infos"); \
  PARSE_APP_PRM(app_name, prm)

#define DEFINE_APP(app_name, desc, prm)                              \
  CLI::App app_name(desc);                                           \
  (app_name).set_help_all_flag("--help-all", "show all help infos"); \
  PARSE_APP_PRM(app_name, prm)

#define DEFINE_APP_AND_PRM(app_name, desc, params_t) \
  params_t prm;                                      \
  DEFINE_APP(app_name, desc, &prm)

#define DEFINE_CONFIG_APP_AND_PRM(app_name, desc, params_t) \
  params_t prm;                                             \
  DEFINE_CONFIG_APP(app_name, desc, &prm)

#define DEFINE_PRM_PTR(params_t, prm) \
  std::unique_ptr<params_t> prm{std::make_unique<params_t>()};

#define DEFINE_CONFIG_APP_AND_PRM_OUTDIR(app_name, desc, params_t, outdir) \
  DEFINE_CONFIG_APP_AND_PRM(app_name, desc, params_t);                     \
  if (outdir.empty()) {                                                    \
    chaos::utils::dump_config(&app_name, "config.toml");                   \
  } else if (outdir == "auto") {                                           \
    chaos::utils::dump_config_chdir(&app_name, "config.toml");             \
  } else {                                                                 \
    CHAOS_ASSERT(chaos::utils::make_dir(outdir));                          \
    CHAOS_ASSERT(chdir(outdir.c_str()) == 0);                              \
    chaos::utils::dump_config(&app_name, "config.toml");                   \
  }
