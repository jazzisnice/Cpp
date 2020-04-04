#ifndef HASH_MAP
#define HASH_MAP

#include <functional>
#include <list>
#include <vector>

namespace mrai
{
template <typename Key, typename Value, typename HashFunction = std::hash<Key>,
          typename KeyEquality = std::equal_to<Key>>
class hash_map
{
public:
  using value_type = std::pair<Key, Value>;

  class iterator
  {
  };

  explicit hash_map(size_t bucket_count = 20,
                    const HashFunction& hash = HashFunction(),
                    const KeyEquality& key_equality = KeyEquality());
  // hash_map(const hash_map& rhs);
  // hash_map(hash_map&& rhs);
  // hash_map& operator=(const hash_map& rhs);
  // hash_map& operator=(hash_map&& rhs);
  //~hash_map();

  auto empty() -> bool;
  auto size() -> size_t;
  // auto insert(const value_type& value) -> std::pair<iterator, bool>;
  // auto insert(value_type&& value) -> std::pair<iterator, bool>;
  // emplace
  // auto erase() ->  size_t;
  // auto at(const Key& key) -> Value&l
  auto contains(const Key& key) -> bool;
  // auto find(const Key& key) -> iterator;

  auto bucket_count() const -> size_t;
  auto max_bucket_count() -> size_t;
  auto bucket_size(size_t bucket_index) const -> size_t;
  auto bucket(const Key& key) const -> size_t;

  auto load_factor() const -> float;
  auto max_load_factor() const -> float;
  auto max_load_factor(float max_load_factor) -> void;
  // auto rehash(size_t bucket_count) -> void;
  // auto reserve(size_t element_count) -> void;
private:
  auto generate_bucket_index(const Key& key) const -> std::size_t;

  using bucket_type = std::list<value_type>;

  std::vector<bucket_type> data_;
  std::size_t element_count_;
  float maximum_load_factor_;
  const HashFunction hash_;
  const KeyEquality key_equality_;
};

template <typename Key, typename Value, typename HashFunction,
          typename KeyEquality>
hash_map<Key, Value, HashFunction, KeyEquality>::hash_map(
    size_t bucket_count, const HashFunction& hash,
    const KeyEquality& key_equality)
    : data_(bucket_count),
      element_count_{ 0 },
      maximum_load_factor_{ 3.0f },
      hash_{ hash },
      key_equality_{ key_equality }
{
}

/*template <typename Key, typename Value, typename HashFunction,
          typename KeyEquality>
auto hash_map<Key, Value, HashFunction, KeyEquality>::insert(const value_type&
value) -> std::pair<iterator, bool>
{

}*/

template <typename Key, typename Value, typename HashFunction,
          typename KeyEquality>
auto hash_map<Key, Value, HashFunction, KeyEquality>::empty() -> bool
{
  return element_count_ == 0;
}

template <typename Key, typename Value, typename HashFunction,
          typename KeyEquality>
auto hash_map<Key, Value, HashFunction, KeyEquality>::size() -> size_t
{
  return element_count_;
}

template <typename Key, typename Value, typename HashFunction,
          typename KeyEquality>
auto hash_map<Key, Value, HashFunction, KeyEquality>::contains(const Key& key)
    -> bool
{
  auto index = generate_bucket_index(key);
  auto searched_element = std::find_if(data_[index].begin(), data_[index].end(),
                                       [&key](const value_type& element) {
                                         return key == element.first;
                                       });
  return searched_element != data_[index].end();
}

template <typename Key, typename Value, typename HashFunction,
          typename KeyEquality>
auto hash_map<Key, Value, HashFunction, KeyEquality>::bucket_count() const
    -> size_t
{
  return data_.capacity();
}

template <typename Key, typename Value, typename HashFunction,
          typename KeyEquality>
auto hash_map<Key, Value, HashFunction, KeyEquality>::max_bucket_count()
    -> size_t
{
  return std::numeric_limits<std::size_t>::max();
}

template <typename Key, typename Value, typename HashFunction,
          typename KeyEquality>
auto hash_map<Key, Value, HashFunction, KeyEquality>::bucket_size(
    size_t bucket_index) const -> size_t
{
  return data_[bucket_index].size();
}

template <typename Key, typename Value, typename HashFunction,
          typename KeyEquality>
auto hash_map<Key, Value, HashFunction, KeyEquality>::bucket(
    const Key& key) const -> size_t
{
  return generate_bucket_index(key);
}

template <typename Key, typename Value, typename HashFunction,
          typename KeyEquality>
auto hash_map<Key, Value, HashFunction, KeyEquality>::generate_bucket_index(
    const Key& key) const -> std::size_t
{
  auto hash_code = hash_(key);
  return hash_code % data_.capacity();
}

template <typename Key, typename Value, typename HashFunction,
          typename KeyEquality>
auto hash_map<Key, Value, HashFunction, KeyEquality>::load_factor() const
    -> float
{
  return element_count_ / bucket_count();
}

template <typename Key, typename Value, typename HashFunction,
          typename KeyEquality>
auto hash_map<Key, Value, HashFunction, KeyEquality>::max_load_factor() const
    -> float
{
  return maximum_load_factor_;
}

template <typename Key, typename Value, typename HashFunction,
          typename KeyEquality>
auto hash_map<Key, Value, HashFunction, KeyEquality>::max_load_factor(
    float max_load_factor) -> void
{
  maximum_load_factor_ = max_load_factor;
  /*if(load_factor() > max_load_factor)
  {
    rehash();
  }*/
}

}  // namespace mrai
#endif  // HASH_MAP