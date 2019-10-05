#pragma once
#include <es_la/dense/tags.hpp>

namespace es_la::internal
{
template<class Layout>
struct Transpose_layout;

template<>
struct Transpose_layout<void>
{
	using Type = void;
};

template<>
struct Transpose_layout<Col_major>
{
	using Type = Row_major;
};

template<>
struct Transpose_layout<Row_major>
{
	using Type = Col_major;
};

///////////////////////////////////////////////////////////////////////

template<class... Ts>
struct Common_layout
{
	using Type = Col_major;
};

template<class... Ts>
struct Common_layout<void, Ts...> : Common_layout<Ts...>
{};
} // namespace es_la
