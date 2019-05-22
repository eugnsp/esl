#pragma once
#include <es_la/dense/forward.hpp>

#include <es_util/type_traits.hpp>

#include <type_traits>

namespace es_la
{
namespace internal
{
template<class Expr>
struct Is_lvalue_block_trait_impl : std::false_type
{};

template<class Expr>
struct Is_lvalue_block_trait : Is_lvalue_block_trait_impl<es_util::Remove_cv_ref<Expr>>
{};

template<typename Value, auto ct_rows, auto ct_cols, class Layout>
struct Is_lvalue_block_trait_impl<Matrix<Value, ct_rows, ct_cols, Layout>> : std::true_type
{};

template<class Expr, auto ct_begin1, auto ct_size1, auto ct_begin2, auto ct_size2>
struct Is_lvalue_block_trait_impl<View<Expr, Range<ct_begin1, ct_size1>, Range<ct_begin2, ct_size2>, Lvalue>> :
	std::true_type
{};
} // namespace internal

template<class Expr>
inline constexpr bool is_lvalue_block = internal::Is_lvalue_block_trait<Expr>::value;
} // namespace es_la
