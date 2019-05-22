#pragma once
#include <es_la/dense/forward.hpp>

#include <type_traits>
#include <utility>

namespace es_la
{
namespace internal
{
template<class Expr, class Category>
void dense_match(const Dense<Expr, Category>&);

int dense_match(...);

template<class Expr>
struct Is_dense_trait : std::is_void<decltype(internal::dense_match(std::declval<Expr>()))>
{};
} // namespace internal

template<class Expr>
inline constexpr bool is_dense = internal::Is_dense_trait<Expr>::value;
} // namespace es_la
