#pragma once
#include <es_la/dense/dense.hpp>
#include <es_la/dense/shape.hpp>
#include <es_la/dense/storage/storage.hpp>
#include <es_la/dense/type_traits.hpp>

#include <es_util/array.hpp>

#include <algorithm>
#include <array>
#include <cstddef>
#include <type_traits>

namespace es_la::internal
{
template<std::size_t ct_rows, std::size_t ct_cols, class Expr, class Layout>
class Matrix_base : public Dense<Expr, Lvalue>, public Shape<ct_rows, ct_cols, Layout>
{
private:
	using Dense_base = Dense<Expr, Lvalue>;
	using Shape_base = Shape<ct_rows, ct_cols, Layout>;

public:
	using Value = Value_type<Expr>;

public:
	//////////////////////////////////////////////////////////////////////
	//* Constructors */

	Matrix_base() = default;
	Matrix_base(const Matrix_base&) = default;
	Matrix_base(Matrix_base&&) = default;

	explicit Matrix_base(const Value& value)
	{
		Dense_base::assign_scalar(value);
	}

	template<typename... Values,
		typename =
			std::enable_if_t<sizeof...(Values) == ct_rows * ct_cols && (std::is_convertible_v<Values, Value> && ...)>>
	explicit constexpr Matrix_base(Values&&... values) : data_{std::forward<Values>(values)...}
	{}

	template<class Expr2>
	Matrix_base(const Expression<Expr2>& expr)
	{
		Dense_base::assign_expr(expr);
	}

	///////////////////////////////////////////////////////////////////////
	//* Assignments */

	using Dense_base::operator=;

	Matrix_base& operator=(const Matrix_base&) = default;
	Matrix_base& operator=(Matrix_base&&) = default;

	////////////////////////////////////////////////////////////////////////
	//* Extents */

	using Shape_base::rows;
	using Shape_base::cols;

	static constexpr bool is_empty()
	{
		return rows() == 0 || cols() == 0;
	}

	static constexpr std::size_t size()
	{
		return rows() * cols();
	}

	static constexpr std::size_t capacity()
	{
		return size();
	}

	///////////////////////////////////////////////////////////////////////
	//* Element access */

	constexpr Value& operator()(std::size_t row, std::size_t col)
	{
		return data_[this->linear_index(row, col)];
	}

	constexpr const Value& operator()(std::size_t row, std::size_t col) const
	{
		return data_[this->linear_index(row, col)];
	}

	constexpr Value& operator[](std::size_t index)
	{
		static_assert(internal::is_vector<Expr>, "Expression should be a vector");
		return (*this)(index, 0);
	}

	constexpr const Value& operator[](std::size_t index) const
	{
		static_assert(internal::is_vector<Expr>, "Expression should be a vector");
		return (*this)(index, 0);
	}

	constexpr Value& operator()(std::size_t index)
	{
		return (*this)[index];
	}

	constexpr const Value& operator()(std::size_t index) const
	{
		return (*this)[index];
	}

protected:
	Storage<Value, ct_rows * ct_cols> data_;
};
} // namespace es_la::internal
