#include "mapping/basic_data_filler.h"
#include "utils/logger/logger.h"
#include "common/numerical.h"

using namespace chaos;
using namespace chaos::mapping;

int main(int argc, char *argv[])
{
  //-> one_dim_filler.
  double res = 0;
  scalar_filler_t f(res);
  CHAOS_DEBUG_ASSERT(f.size() == 1);
  f.fill(5);
  CHAOS_DEBUG_ASSERT(numerical::near<double>(res, 5));
  f.fill<false>(0, 1);
  CHAOS_DEBUG_ASSERT(numerical::near<double>(res, 6));
  f.fill<true>(0, 1);
  CHAOS_DEBUG_ASSERT(numerical::near<double>(res, 1));
  return 0;
}
