#pragma once
#include <es_la/dense/dense.hpp>
#include <es_la/dense/type_traits.hpp>
#include <es_la/dense/utility.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>

namespace es_la
{
template<class Expr, class Rows, class Cols, class Category>
class View : public Dense<View<Expr, Rows, Cols, Category>, Category>
{
public:
	template<class Expr_f>
	View(Expr_f&& expr, Rows rows, Cols cols) :
		expr_(std::forward<Expr_f>(expr)), rows_(std::move(rows)), cols_(std::move(cols))
	{
		// static_assert(is_ct_extent_dynamic_or_less_equal(ct_size_value<Rows>, ct_rows_value<Expr>), "Incompatible extents");
		// static_assert(is_ct_extent_dynamic_or_less_equal(ct_size_value<Cols>, ct_cols_value<Expr>), "Incompatible extents");

		// assert(rows.are_all_less(expr.rows()));
		// assert(cols.are_all_less(expr.cols()));
	}

	View(const View&) = default;
	View(View&&) = default;

	View& operator=(const View& other)
	{
		static_assert(std::is_same_v<Category, Lvalue>, "Expression should be an l-value");
		this->assign_expr(other);
		return *this;
	}

	template<class Other>
	View& operator=(const Expression<Other>& other)
	{
		static_assert(std::is_same_v<Category, Lvalue>, "Expression should be an l-value");
		this->assign_expr(other);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////
	//* Extents */

	std::size_t rows() const
	{
		return rows_.size();
	}

	std::size_t cols() const
	{
		return cols_.size();
	}

	std::size_t l_dim() const
	{
		static_assert(is_lvalue_block<View>, "View should be an l-value block");
		return expr_.l_dim();
	}

	std::size_t row_inc() const
	{
		static_assert(is_lvalue_block<View>, "View should be an l-value block");
		return expr_.row_inc();
	}

	std::size_t col_inc() const
	{
		static_assert(is_lvalue_block<View>, "View should be an l-value block");
		return expr_.col_inc();
	}

	//////////////////////////////////////////////////////////////////////
	//* Element access */

	decltype(auto) operator()(std::size_t row, std::size_t col)
	{
		return expr_(rows_[row], cols_[col]);
	}

	decltype(auto) operator()(std::size_t row, std::size_t col) const
	{
		if constexpr (std::is_same_v<Category, Lvalue>)
			return std::as_const(expr_(rows_[row], cols_[col]));
		else
			return expr_(rows_[row], cols_[col]);
	}

	auto data()
	{
		static_assert(is_lvalue_block<View>, "View should be an l-value block");
		if constexpr (is_col_major<View>)
			return expr_.data() + cols_.start() * l_dim() + rows_.start();
		else
			return expr_.data() + rows_.start() * l_dim() + cols_.start();
	}

	auto data() const
	{
		static_assert(is_lvalue_block<View>, "View should be an l-value block");
		if constexpr (is_col_major<View>)
			return &std::as_const(*(expr_.data() + cols_.start() * l_dim() + rows_.start()));
		else
			return &std::as_const(*(expr_.data() + rows_.start() * l_dim() + cols_.start()));
	}

private:
	internal::Expr_storage_type<Expr> expr_;

	const Rows rows_;
	const Cols cols_;
};
} // namespace es_la