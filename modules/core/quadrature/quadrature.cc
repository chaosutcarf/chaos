#include "quadrature.h"

#include "utils/logger/logger.h"

namespace chaos {

namespace details {
std::unique_ptr<quadrature> line(int order);
std::unique_ptr<quadrature> quad(int order);
std::unique_ptr<quadrature> hex(int order);

std::unique_ptr<quadrature> tri(int order);
std::unique_ptr<quadrature> tet(int order);

std::unique_ptr<quadrature> wedge(int order);
std::unique_ptr<quadrature> pyramid(int order);
}  // namespace details

size_t quadrature::num() const {
  CHAOS_DEBUG_ASSERT(P.cols() == W.size(), P.cols(), W.size());
  return W.size();
}
Eigen::Ref<const vecxr_t> quadrature::at(int i) const {
  CHAOS_DEBUG_ASSERT(i < num());
  return P.col(i);
}
real_t quadrature::weight(int i) const {
  CHAOS_DEBUG_ASSERT(i < num());
  return W[i];
}

size_t quadrature::dim() const {
  CHAOS_DEBUG_ASSERT(P.cols() == W.size(), P.cols(), W.size());
  return P.rows();
}

int quadrature_factory::hash_prm(cell_type type, int order) {
  return (order << 4) | type;
}

const quadrature* quadrature_factory::create(cell_type type, int order) {
  auto code = hash_prm(type, order);
  auto iter = cache.find(code);
  if (iter == cache.end()) {
    //-> not found, create one and store it.
    std::unique_ptr<quadrature> qdrt;
    switch (type) {
      case LINE:
        qdrt = details::line(order);
        break;
      case QUAD:
        qdrt = details::quad(order);
        break;
      case TRI:
        qdrt = details::tri(order);
        break;
      case HEX:
        qdrt = details::hex(order);
        break;
      case TET:
        qdrt = details::tet(order);
        break;
      case WEDGE:
        qdrt = details::wedge(order);
        break;
      case PYRAMID:
        qdrt = details::pyramid(order);
        break;
      default:
        critical_msg("gauss legendre quadrature filed with unknown type: ",
                     type);
    }
    const quadrature* lease_ptr = qdrt.get();
    cache.insert({code, std::move(qdrt)});
    return lease_ptr;
  } else {
    return iter->second.get();
  }
}
//-> define the static variable.
quadrature_factory::cache_t quadrature_factory::cache;
}  // namespace chaos
