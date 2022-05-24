#pragma once

//-> https://en.cppreference.com/w/cpp/numeric/random/
#include <random>
#include <type_traits>

#include "common/numerical.h"
#include "common/type.h"
namespace chaos::common {
class random {
 public:
  //-> global random generator.
  inline static std::mt19937& gen() {
    static std::random_device rd;
    static std::mt19937 gen_instance(rd());
    return gen_instance;
  }
  inline static int randint(int lower, int upper) {
    std::uniform_int_distribution<int> dis(lower, upper - 1);
    return dis(gen());
  }
  inline static double randreal(real_t lower = 0, real_t upper = 1) {
    std::uniform_real_distribution<double> dis(lower, upper);
    return dis(gen());
  }
  inline static vec3r_t randomv3(real_t lower = 0, real_t upper = 1) {
    return vec3r_t(randreal(lower, upper), randreal(lower, upper),
                   randreal(lower, upper));
  }

  inline static vec3r_t random_in_unit_disk() {
    // real_t r = randreal(0, 1);
    // real_t theta = randreal(0, 2*numerical::PI);
    // return vec3r_t(r*std::sin(theta), r*std::cos(theta), 0);
    real_t x, y;
    do {
      x = randreal(-1, 1);
      y = randreal(-1, 1);
    } while (x * x + y * y >= 1);
    return vec3r_t(x, y, 0);
  }

  inline static vec3r_t random_in_unit_sphere() {
    // real_t r = randreal(0, 1);
    // real_t theta = randreal(0, 2*numerical::PI);
    // real_t phi = randreal(0, numerical::PI);
    // return vec3r_t(r*std::sin(phi) * std::sin(theta), r
    // *std::sin(phi)*std::cos(theta), r*std::cos(phi));
    real_t x, y, z;
    do {
      x = randreal(-1, 1);
      y = randreal(-1, 1);
      z = randreal(-1, 1);
    } while (x * x + y * y + z * z >= 1);
    return vec3r_t(x, y, z);
  }

  inline static vec3r_t random_unit_vector() {
    real_t theta = randreal(0, numerical::PI);
    real_t phi = randreal(0, numerical::PI);
    return vec3r_t(std::sin(phi) * std::sin(theta),
                   std::sin(phi) * std::cos(theta), std::cos(phi));
  }
  inline vec3r_t random_in_hemisphere(const vec3r_t& normal) {
    vec3r_t in_unit_sphere = random_in_unit_sphere();
    if (in_unit_sphere.dot(normal) > 0) {
      return in_unit_sphere;
    } else {
      return -in_unit_sphere;
    }
  }
};
}  // namespace chaos::common
