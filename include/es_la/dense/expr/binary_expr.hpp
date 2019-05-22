#pragma once
#include <es_la/dense/dense.hpp>
#include <es_la/dense/type_traits.hpp>

#include <cstddef>
#include <utility>

namespace es_la
{
template<class Expr1_, class Expr2_, template<class, class> class Fn_>
class Binary_expr : public Dense<Binary_expr<Expr1_, Expr2_, Fn_>, Rvalue>
{
public:
	using Expr1 = Expr1_;
	using Expr2 = Expr2_;
	using Fn = Fn_<Expr1, Expr2>;

public:
	template<class Expr1_f, class Expr2_f>
	Binary_expr(Expr1_f&& expr1, Expr2_f&& expr2) :
		expr1_(std::forward<Expr1_f>(expr1)), expr2_(std::forward<Expr2_f>(expr2))
	{
		Fn::check_sizes(expr1_, expr2_);
	}

	std::size_t rows() const
	{
		return Fn::rows(expr1_, expr2_);
	}

	std::size_t cols() const
	{
		return Fn::cols(expr1_, expr2_);
	}

	decltype(auto) operator()(std::size_t row, std::size_t col) const
	{
		return Fn::element(expr1_, expr2_, row, col);
	}

	const Expr1& expr1() const
	{
		return expr1_;
	}

	const Expr2& expr2() const
	{
		return expr2_;
	}

private:
	internal::Expr_storage_type<const Expr1> expr1_;
	internal::Expr_storage_type<const Expr2> expr2_;
};
} // namespace es_la
