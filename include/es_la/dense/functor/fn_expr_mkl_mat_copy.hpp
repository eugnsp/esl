#pragma once
#include <es_la/dense/tags.hpp>
#include <es_la/dense/type_traits/ct_extent.hpp>
#include <es_la/dense/type_traits/layout.hpp>
#include <es_la/dense/utility/mkl_overloads.hpp>

#include <utility>

namespace es_la::internal
{
// Tag for the X = Y operation
struct Fn_expr_mkl_mat_copy_assign_tag
{};

// Tag for the X = a * Y operation
struct Fn_expr_mkl_mat_copy_scale_assign_tag
{};

template<class Tag>
class Fn_expr_mkl_mat_copy
{
public:
	template<class Expr_dst, class Expr_src>
	void operator()(Expr_dst& dst, const Expr_src& src)
	{
		(*this)(dst, src, Tag{});
	}

private:
	template<class Expr_dst, class Expr_src>
	void operator()(Expr_dst& dst, const Expr_src& src, Fn_expr_mkl_mat_copy_assign_tag)
	{
		(*this)(dst, src, 1);
	}

	template<class Expr_dst, class Expr_src>
	void operator()(Expr_dst& dst, const Expr_src& src, Fn_expr_mkl_mat_copy_scale_assign_tag)
	{
		(*this)(dst, src.expr(), src.scalar());
	}

	template<class Expr_dst, class Expr_src, typename Alpha>
	void operator()(Expr_dst& dst, const Expr_src& src, Alpha alpha)
	{
		using Transp_tag = std::conditional_t<have_same_layout<Expr_dst, Expr_src>, No_transpose, Transpose>;

		const auto rows = have_same_layout<Expr_dst, Expr_src> ? dst.rows() : dst.cols();
		const auto cols = have_same_layout<Expr_dst, Expr_src> ? dst.cols() : dst.rows();

		internal::mkl_omatcopy<Layout_tag<Expr_dst>, Transp_tag>(
			rows, cols, alpha, src.data(), src.lead_dim(), dst.data(), dst.lead_dim());
	}
};
} // namespace es_la::internal