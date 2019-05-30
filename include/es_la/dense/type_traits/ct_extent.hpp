#pragma once
#include <es_la/core/type_traits/ct_extent.hpp>
#include <es_la/dense/forward.hpp>
#include <es_la/dense/utility/ct_extent.hpp>

#include <es_util/type_traits.hpp>

#include <cstddef>

namespace es_la
{
template<typename T, std::size_t ct_rows, std::size_t ct_cols, class Layout>
struct Ct_rows_trait<Matrix<T, ct_rows, ct_cols, Layout>> : es_util::Std_integral_constant<ct_rows>
{};

template<typename T, std::size_t ct_rows, std::size_t ct_cols, class Layout>
struct Ct_cols_trait<Matrix<T, ct_rows, ct_cols, Layout>> : es_util::Std_integral_constant<ct_cols>
{};

///////////////////////////////////////////////////////////////////////

template<class Expr, class Rows, class Cols, class Category>
struct Ct_rows_trait<View<Expr, Rows, Cols, Category>> : Ct_size_trait<Rows>
{};

template<class Expr, class Rows, class Cols, class Category>
struct Ct_cols_trait<View<Expr, Rows, Cols, Category>> : Ct_size_trait<Cols>
{};

//////////////////////////////////////////////////////////////////////

template<class Expr, class Category>
struct Ct_rows_trait<Transposed_view<Expr, Category>> : Ct_cols_trait<Expr>
{};

template<class Expr, class Category>
struct Ct_cols_trait<Transposed_view<Expr, Category>> : Ct_rows_trait<Expr>
{};

///////////////////////////////////////////////////////////////////////

template<class Expr, typename Scalar, class Fn>
struct Ct_rows_trait<Scalar_expr<Expr, Scalar, Fn>> : Ct_rows_trait<Expr>
{};

template<class Expr, typename Scalar, class Fn>
struct Ct_cols_trait<Scalar_expr<Expr, Scalar, Fn>> : Ct_cols_trait<Expr>
{};

///////////////////////////////////////////////////////////////////////

template<class Expr_l, class Expr_r, template<class, class> class Fn>
struct Ct_rows_trait<Binary_expr<Expr_l, Expr_r, Fn>> : es_util::Std_integral_constant<Fn<Expr_l, Expr_r>::ct_rows>
{};

template<class Expr_l, class Expr_r, template<class, class> class Fn>
struct Ct_cols_trait<Binary_expr<Expr_l, Expr_r, Fn>> : es_util::Std_integral_constant<Fn<Expr_l, Expr_r>::ct_cols>
{};

///////////////////////////////////////////////////////////////////////

template<class Random_distribution, class Random_generator>
struct Ct_rows_trait<Random_matrix<Random_distribution, Random_generator>> : es_util::Std_integral_constant<dynamic>
{};

template<class Random_distribution, class Random_generator>
struct Ct_cols_trait<Random_matrix<Random_distribution, Random_generator>> : es_util::Std_integral_constant<dynamic>
{};

///////////////////////////////////////////////////////////////////////

template<std::size_t ct_begin, std::size_t ct_size>
struct Ct_size_trait<internal::Range<ct_begin, ct_size>> : es_util::Std_integral_constant<ct_size>
{};

template<std::size_t ct_size>
struct Ct_size_trait<internal::Slice<ct_size>> : es_util::Std_integral_constant<ct_size>
{};
} // namespace es_la