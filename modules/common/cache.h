#pragma once

#include <cstddef>
#include <iostream>
#include <list>
#include <mutex>
#include <optional>
#include <ostream>
#include <shared_mutex>
#include <unordered_map>

namespace chaos {
template <
    typename KeyT = size_t, typename ValueT = double, bool thread_safe = false,
    template <typename AllocT> typename Allocator = std::allocator,
    typename KeyEqual = std::equal_to<KeyT>, typename KeyHash = std::hash<KeyT>>
class LRUCache {
#define LOCK_ACTION(lock_type, action)         \
  if constexpr (thread_safe) {                 \
    lock_type<std::shared_mutex> lock(mutex_); \
    action;                                    \
  } else {                                     \
    action;                                    \
  }
#define READER(action) LOCK_ACTION(std::shared_lock, action);
#define WRITER(action) LOCK_ACTION(std::scoped_lock, action);

 public:
  explicit LRUCache(size_t capacity = 100, size_t relaxation = 10)
      : capacity_(capacity), relaxation_(relaxation) {}

  std::optional<ValueT> get(const KeyT &x) {
    WRITER({
      auto iter = entry_map_.find(x);
      if (iter == entry_map_.end()) {
        return {};
      } else {
        entry_list_.splice(entry_list_.begin(), entry_list_, iter->second);
        return iter->second->second;
      }
    });
  }

  bool has(const KeyT &x) const { READER(return entry_map_.count(x) != 0); }

  void store(const KeyT &x, const ValueT &v) { (*this)[x] = v; }

  ValueT &operator[](const KeyT &x) {
    WRITER({
      auto iter = entry_map_.find(x);
      if (iter == entry_map_.end()) {
        entry_list_.push_front({x, ValueT{}});
        entry_map_.insert({x, entry_list_.begin()});
        clean();
        return entry_list_.begin()->second;
      } else {
        entry_list_.splice(entry_list_.begin(), entry_list_, iter->second);
        return iter->second->second;
      }
    });
  }

  [[nodiscard]] size_t size() const { READER(return entry_map_.size()); }
  [[nodiscard]] size_t capacity() const { READER(return capacity_); }
  [[nodiscard]] size_t relaxation() const { READER(return relaxation_); }

  void resize(size_t capacity) { WRITER(this->capacity_ = capacity); }
  void capacity(size_t capacity) { WRITER(this->capacity_ = capacity); }
  void relaxation(size_t relaxation) { WRITER(this->relaxation_ = relaxation); }
  void clear() { WRITER(entry_list_.clear(); entry_map_.clear()); }

  friend std::ostream &operator<<(
      std::ostream &os,
      const LRUCache<KeyT, ValueT, thread_safe, Allocator, KeyEqual, KeyHash>
          &cache) {
    for (const auto &item : cache.entry_list_) {
      os << "(" << item.first << "," << item.second << ") ";
    }
    return os;
  }

 private:
  void clean() {
    auto remove_cnt = entry_map_.size() > capacity_ + relaxation_
                          ? entry_map_.size() - capacity_
                          : 0;
    for (size_t i = 0; i < remove_cnt; ++i) {
      auto last_it = entry_list_.end();
      last_it--;
      entry_map_.erase(last_it->first);
      entry_list_.pop_back();
    }
  }
  mutable std::shared_mutex mutex_;
  std::list<std::pair<KeyT, ValueT>, Allocator<std::pair<KeyT, ValueT>>>
      entry_list_;
  std::unordered_map<KeyT, decltype(entry_list_.begin()), KeyHash, KeyEqual,
                     Allocator<std::pair<
                         const KeyT, typename decltype(entry_list_)::iterator>>>
      entry_map_;
  size_t capacity_;
  size_t relaxation_;

#undef READER
#undef WRITER
#undef LOCK_ACTION
};
}  // namespace chaos
