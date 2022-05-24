#include "common/cache.h"

#include <catch2/catch.hpp>
#include <iostream>
using namespace chaos;
using namespace std;

template <bool flag>
void cache_routine_check() {
  constexpr const size_t num = 5;
  LRUCache<size_t, size_t, flag> cache(num, 0);
  CHECK(cache.capacity() == num);
  CHECK(cache.relaxation() == 0);
  CHECK(cache.size() == 0);
  for (size_t i = 0; i < num; ++i) {
    CHECK(!cache.has(i));
    cache[i] = i;
    CHECK(cache.has(i));
    cout << "LRUCache: [" << cache << "]\n";
  }
  CHECK(cache.size() == num);
  for (size_t i = 0; i < num; ++i) {
    CHECK(cache.has(i));
    CHECK(cache.get(i).value() == i);
  }
  cache.resize(2 * num);
  CHECK(cache.capacity() == 2 * num);
  cache.capacity(num);
  CHECK(cache.capacity() == num);
  cache.relaxation(num);
  CHECK(cache.relaxation() == num);
  cache.relaxation(0);
  CHECK(cache.relaxation() == 0);

  //-> check replace strategy.
  cache.store(num, num);
  cout << "LRUCache: [" << cache << "]\n";
  for (size_t i = 0; i < num + 1; ++i) {
    cout << "[LRUCache.has(" << i << "): " << cache.has(i) << endl;
  }
  CHECK(!cache.has(0));
  for (size_t i = 1; i < num + 1; ++i) {
    cout << i << endl;
    CHECK(cache.has(i));
    cout << cache.get(i).value() << endl;
    CHECK(cache.get(i).value() == i);
  }
  CHECK(!cache.get(2 * num));
  CHECK(cache.get(num));
  CHECK(cache.get(num).value() == num);
}

TEST_CASE("test cache usage", "[cache]") {
  cache_routine_check<true>();
  cache_routine_check<false>();
}
