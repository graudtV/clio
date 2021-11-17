#pragma once

#include <cassert>
#include <functional>
#include <unordered_map>
#include <utility>

namespace utils {

namespace detail {

template <class Tuple, size_t I = std::tuple_size<Tuple>::value - 1>
struct TupleHashImpl {
  size_t operator()(const Tuple &T) const {
    using Elem = typename std::tuple_element<I, Tuple>::type;
    return std::hash<Elem>()(std::get<I>(T)) + TupleHashImpl<Tuple, I - 1>()(T);
  }
};

template <class Tuple> struct TupleHashImpl<Tuple, 0> {
  size_t operator()(const Tuple &T) const {
    using Elem = typename std::tuple_element<0, Tuple>::type;
    return std::hash<Elem>()(std::get<0>(T));
  }
};

template <class Tuple> using TupleHash = detail::TupleHashImpl<Tuple>;

} // namespace detail

template <class ValueT, class... KeyTs> class CachedAccess {
public:
  using ValueType = ValueT;
  using Reference = ValueT &;
  using ConstReference = const ValueT &;
  using KeyTuple = std::tuple<KeyTs...>;
  using DirectAccessFunctor = std::function<ValueT(KeyTs...)>;

  CachedAccess(DirectAccessFunctor DA) : DirectAccess(std::move(DA)) {}

  // TODO: check if it really works without copy-ctor invocation (f.e. if
  // copy-ctor deleted)
  /* template is used to enable perfect forwarding semantics */
  template <class... KTs> ConstReference operator()(KTs &&... Keys) {
    return accessValue(KeyTuple(std::forward<KTs>(Keys)...));
  }

  template <class... KTs> bool isCached(KTs &&... Keys) {
    return Cache.count(KeyTuple(std::forward<KTs>(Keys)...));
  }

private:
  DirectAccessFunctor DirectAccess;
  std::unordered_map<KeyTuple, ValueType, detail::TupleHash<KeyTuple>,
                     std::equal_to<>>
      Cache;

  Reference accessValue(KeyTuple Keys) {
    if (auto Search = Cache.find(Keys); Search != Cache.end())
      return Search->second;
    auto [It, Inserted] = Cache.emplace(Keys, std::apply(DirectAccess, Keys));
    assert(Inserted == true &&
           "Keys were not found in cache, but insertion failed");
    return It->second;
  }
};

template <class... KeyTs, class Functor> auto makeCache(Functor &&F) {
  using ValueT = std::invoke_result_t<Functor, KeyTs...>;
  return CachedAccess<ValueT, KeyTs...>(std::forward<Functor>(F));
}

} // namespace utils