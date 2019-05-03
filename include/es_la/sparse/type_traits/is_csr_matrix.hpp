#pragma once
#include <es_la/sparse/forward.hpp>

#include <es_util/type_traits.hpp>

#include <type_traits>

namespace es_la::internal
{
template<class T>
struct Is_csr_matrix_impl : std::false_type
{};

template<typename Value, class Symmetry_tag, typename Index>
struct Is_csr_matrix_impl<Csr_matrix<Value, Symmetry_tag, Index>> : std::true_type
{};

template<class T>
inline constexpr bool is_csr_matrix = Is_csr_matrix_impl<es_util::Remove_cvref<T>>::value;
} // namespace es_la::internal
