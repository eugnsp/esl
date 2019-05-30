#pragma once
#include <es_la/dense/storage/memory.hpp>

#include <es_util/type_traits.hpp>

#include <cstddef>
#include <new>
#include <stdexcept>
#include <type_traits>

namespace es_la::internal
{
template<typename T, std::size_t alignment>
class Allocator
{
private:
	static constexpr auto max_size = static_cast<std::size_t>(-1) / sizeof(T);

public:
	[[nodiscard, gnu::malloc, gnu::assume_aligned(alignment)]] static T* allocate(std::size_t size)
	{
		if (size == 0)
			return nullptr;

		if (size > max_size)
			throw std::bad_array_new_length();

		auto ptr = es_la::internal::mem_alloc(size * sizeof(T), alignment);
		if (!ptr)
			throw std::bad_alloc();

		return static_cast<T*>(ptr);
	}

	[[nodiscard, gnu::assume_aligned(alignment)]] static T* reallocate(T* old_ptr, std::size_t size)
	{
		static_assert(es_util::is_trivially_relocatable<T>);

		if (old_ptr == nullptr)
			return allocate(size);

		if (size == 0)
		{
			deallocate(old_ptr);
			return nullptr;
		}

		if (size > max_size)
			throw std::bad_array_new_length();

		auto ptr = es_la::internal::mem_realloc(old_ptr, size * sizeof(T), alignment);
		if (!ptr)
			throw std::bad_alloc();

		return static_cast<T*>(ptr);
	}

	static void deallocate(T* ptr) noexcept
	{
		es_la::internal::mem_free(ptr);
	}
};
} // namespace es_la::internal