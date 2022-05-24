#include "core/quadrature/quadrature.h"

namespace chaos::details {
int compute_gauss_legendre_order(int order) {
  CHAOS_ASSERT_EXT(
      order >= 0,
      "In gauss quadrature order, order should be a positive integer!", order);
  return order / 2 + 1;
}

std::unique_ptr<quadrature> line(int order) {
  order = compute_gauss_legendre_order(order);
  CHAOS_ASSERT_EXT(order <= 11, "Order only support up to 11.");
  matxr_t P(1, order);
  vecxr_t W(order);
  //-> https://pomax.github.io/bezierinfo/legendre-gauss.html
  if (order == 1) {
    P << 0;
    W << 2;
  } else if (order == 2) {
    P << -0.5773502691896257, 0.5773502691896257;
    W << 1, 1;
  } else if (order == 3) {
    P << 0, -0.7745966692414834, 0.7745966692414834;
    W << 0.8888888888888888, 0.5555555555555556, 0.5555555555555556;
  } else if (order == 4) {
    P << -0.3399810435848563, 0.3399810435848563, -0.8611363115940526,
        0.8611363115940526;
    W << 0.6521451548625461, 0.6521451548625461, 0.3478548451374538,
        0.3478548451374538;
  } else if (order == 5) {
    P << 0, -0.5384693101056831, 0.5384693101056831, 0.9061798459386640,
        -0.9061798459386640;
    W << 0.5688888888888889, 0.4786286704993665, 0.4786286704993665,
        0.2369268850561891, 0.2369268850561891;
  } else if (order == 6) {
    P << -0.6612093864662645, 0.6612093864662645, -0.2386191860831969,
        0.2386191860831969, -0.9324695142031521, 0.9324695142031521;
    W << 0.3607615730481386, 0.3607615730481386, 0.4679139345726910,
        0.4679139345726910, 0.1713244923791704, 0.1713244923791704;
  } else if (order == 7) {
    P << 0, -0.4058451513773972, 0.4058451513773972, -0.7415311855993945,
        0.7415311855993945, -0.9491079123427585, 0.9491079123427585;
    W << 0.4179591836734694, 0.3818300505051189, 0.3818300505051189,
        0.2797053914892766, 0.2797053914892766, 0.1294849661688697,
        0.1294849661688697;
  } else if (order == 8) {
    P << -0.1834346424956498, 0.1834346424956498, -0.5255324099163290,
        0.5255324099163290, -0.7966664774136267, 0.7966664774136267,
        -0.9602898564975363, 0.9602898564975363;
    W << 0.3626837833783620, 0.3626837833783620, 0.3137066458778873,
        0.3137066458778873, 0.2223810344533745, 0.2223810344533745,
        0.1012285362903763, 0.1012285362903763;
  } else if (order == 9) {
    P << 0.0000000000000000, -0.8360311073266358, 0.8360311073266358,
        -0.9681602395076261, 0.9681602395076261, -0.3242534234038089,
        0.3242534234038089, -0.6133714327005904, 0.6133714327005904;
    W << 0.3302393550012598, 0.1806481606948574, 0.1806481606948574,
        0.0812743883615744, 0.0812743883615744, 0.3123470770400029,
        0.3123470770400029, 0.2606106964029354, 0.2606106964029354;
  } else if (order == 10) {
    P << -0.1488743389816312, 0.1488743389816312, -0.4333953941292472,
        0.4333953941292472, -0.6794095682990244, 0.6794095682990244,
        -0.8650633666889845, 0.8650633666889845, -0.9739065285171717,
        0.9739065285171717;
    W << 0.2955242247147529, 0.2955242247147529, 0.2692667193099963,
        0.2692667193099963, 0.2190863625159820, 0.2190863625159820,
        0.1494513491505806, 0.1494513491505806, 0.0666713443086881,
        0.0666713443086881;
  } else if (order == 11) {
    P << 0.0000000000000000, -0.2695431559523450, 0.2695431559523450,
        -0.5190961292068118, 0.5190961292068118, -0.7301520055740494,
        0.7301520055740494, -0.8870625997680953, 0.8870625997680953,
        -0.9782286581460570, 0.9782286581460570;
    W << 0.2729250867779006, 0.2628045445102467, 0.2628045445102467,
        0.2331937645919905, 0.2331937645919905, 0.1862902109277343,
        0.1862902109277343, 0.1255803694649046, 0.1255803694649046,
        0.0556685671161737, 0.0556685671161737;
  } else {
    //-> asymptotic expansiton.
    critical_msg("WIP.asymptotic expansition");
  }
  P.array() += 1;
  P /= 2;
  W /= 2;
  return std::make_unique<quadrature>(P, W);
}

std::unique_ptr<quadrature> quad(int order) {
  auto qdrt = line(order);
  size_t num = qdrt->num() * qdrt->num();
  matxr_t P(2, num);
  vecxr_t W(num);

  size_t cur = 0;
  for (size_t x = 0; x < qdrt->num(); ++x) {
    for (size_t y = 0; y < qdrt->num(); ++y) {
      P(0, cur) = qdrt->P(0, x);
      P(1, cur) = qdrt->P(0, y);
      W(cur) = qdrt->W(x) * qdrt->W(y);
      cur++;
    }
  }

  return std::make_unique<quadrature>(P, W);
}

std::unique_ptr<quadrature> hex(int order) {
  auto qdrt = line(order);
  size_t num = qdrt->num() * qdrt->num() * qdrt->num();
  matxr_t P(3, num);
  vecxr_t W(num);

  size_t cur = 0;
  for (size_t x = 0; x < qdrt->num(); ++x) {
    for (size_t y = 0; y < qdrt->num(); ++y) {
      for (size_t z = 0; z < qdrt->num(); ++z) {
        P(0, cur) = qdrt->P(0, x);
        P(1, cur) = qdrt->P(0, y);
        P(2, cur) = qdrt->P(0, z);
        W(cur) = qdrt->W(x) * qdrt->W(y) * qdrt->W(z);
        cur++;
      }
    }
  }

  return std::make_unique<quadrature>(P, W);
}

// TODO.
std::unique_ptr<quadrature> wedge(int order) {
  auto qdrt = line(order);
  size_t num = qdrt->num() * qdrt->num() * qdrt->num();
  matxr_t P(3, num);
  vecxr_t W(num);

  /*
   * 0 <= x <= 1
   * 0 <= y <= 1 - x
   * 0 <= z <= 1
   */

  size_t cur = 0;
  for (size_t x = 0; x < qdrt->num(); ++x) {
    for (size_t y = 0; y < qdrt->num(); ++y) {
      for (size_t z = 0; z < qdrt->num(); ++z) {
        real_t s = (1 - qdrt->P(0, x));
        P(0, cur) = qdrt->P(0, x);
        P(1, cur) = qdrt->P(0, y) * s;
        P(2, cur) = qdrt->P(0, z);
        W(cur) = qdrt->W(x) * qdrt->W(y) * qdrt->W(z) * s;
        cur++;
      }
    }
  }

  return std::make_unique<quadrature>(P, W);
}
// TODO.
std::unique_ptr<quadrature> pyramid(int order) {
  auto qdrt_z = line(order + 2);
  auto qdrt_xy = line(order);
  size_t num = qdrt_z->num() * qdrt_xy->num() * qdrt_xy->num();
  matxr_t P(3, num);
  vecxr_t W(num);

  /*
   * 0.5z <= x <= 1-0.5z , x = (1-z)\xi_x + 0.5z
   * 0.5z <= y <= 1-0.5z , y = (1-z)\xi_y + 0.5z
   * 0    <= z <= 1      , z = \xi_z
   */

  size_t cur = 0;
  for (size_t x = 0; x < qdrt_xy->num(); ++x) {
    for (size_t y = 0; y < qdrt_xy->num(); ++y) {
      for (size_t z = 0; z < qdrt_z->num(); ++z) {
        real_t s = (1 - qdrt_z->at(z)[0]);
        real_t t = qdrt_z->at(z)[0] / 2;
        P(0, cur) = qdrt_xy->at(x)[0] * s + t;
        P(1, cur) = qdrt_xy->at(y)[0] * s + t;
        P(2, cur) = qdrt_z->at(z)[0];
        W(cur) = qdrt_xy->W(x) * qdrt_xy->W(y) * qdrt_z->W(z) * s * s;
        cur++;
      }
    }
  }

  return std::make_unique<quadrature>(P, W);
}
}  // namespace chaos::details
