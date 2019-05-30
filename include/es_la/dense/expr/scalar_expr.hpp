#pragma once
#include <es_la/dense/dense.hpp>
#include <es_la/dense/type_traits.hpp>

#include <cstddef>
#include <utility>

namespace es_la
{
template<class Expr_, typename Scalar_, class Fn>
class Scalar_expr : public Dense<Scalar_expr<Expr_, Scalar_, Fn>, Rvalue>
{
public:
	using Value = Value_type<Scalar_expr>;
	using Expr = Expr_;
	using Scalar = Scalar_;

public:
	template<class Expr_f, typename Scalar_f>
	Scalar_expr(Expr_f&& expr, Scalar_f&& scalar) :
		expr_(std::forward<Expr_f>(expr)), scalar_(std::forward<Scalar_f>(scalar))
	{}

	std::size_t rows() const
	{
		return expr_.rows();
	}

	std::size_t cols() const
	{
		return expr_.cols();
	}

	Value operator()(std::size_t row, std::size_t col) const
	{
		return Fn::element(expr_, scalar_, row, col);
	}

	const Expr& expr() const
	{
		return expr_;
	}

	const Scalar& scalar() const
	{
		return scalar_;
	}

private:
	internal::Expr_storage_type<const Expr> expr_;
	const Scalar scalar_;
};
} // namespace es_la