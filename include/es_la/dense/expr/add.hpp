#pragma once
#include <es_la/dense/forward.hpp>
#include <es_la/dense/type_traits.hpp>

#include <mkl_cblas.h>

#include <cassert>
#include <cstddef>
#include <type_traits>

namespace es_la::internal
{
template<class Expr1, class Expr2, typename = void>
struct Add_equal
{
	static void run(Expr1& expr1, const Expr2& expr2)
	{
		assert(expr1.rows() == expr2.rows());
		assert(expr1.cols() == expr2.cols());

		for (std::size_t col = 0; col < expr1.cols(); ++col)
			for (std::size_t row = 0; row < expr1.rows(); ++row)
				expr1(row, col) += expr2(row, col);
	}
};

template<class Expr1, class Expr2,
	typename = std::enable_if_t<std::is_same_v<Value_type<Expr1>, Value_type<Expr2>> &&
								internal::is_fd_cfd<Value_type<Expr1>> && internal::is_dynamic_expr<Expr1> &&
								internal::is_dynamic_expr<Expr2> && internal::is_vector_expr<Expr1> &&
								internal::is_vector_expr<Expr2>>>
void add(Dense<Expr1, Lvalue>& expr1, const Dense<Expr2, Lvalue>& expr2)
{
	assert(expr1.size() == expr2.size());

	::cblas_daxpy(
		expr1.size(), 1., expr2.self().data(), expr2.self().col_inc(), expr1.self().data(), expr1.self().col_inc());
}

template<class Expr1, class Expr2, typename Scalar, class Fn,
	typename = std::enable_if_t<std::is_same_v<Value_type<Expr1>, Value_type<Expr2>> &&
								internal::is_fd_cfd<Value_type<Expr1>> && internal::is_dynamic_expr<Expr1> &&
								internal::is_dynamic_expr<Expr2> && internal::is_vector_expr<Expr1> &&
								internal::is_vector_expr<Expr2>>>
void add(Dense<Expr1, Lvalue>& expr1, const Dense<Scalar_expr<Expr2, Scalar, Fn>, Rvalue>& expr2)
{
	assert(expr1.size() == expr2.size());

	::cblas_daxpy(expr1.size(), expr2.self().scalar(), expr2.self().expr().data(), expr2.self().expr().col_inc(),
		expr1.self().data(), expr1.self().col_inc());
}
} // namespace es_la::internal
