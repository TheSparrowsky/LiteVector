#pragma once
#include <cstdio>
#include "allocators/LiteAllocator.h"

namespace LV
{
	template<typename T, typename Allocator = LiteAllocator<T>>
	class LiteVector
	{
		public:
			using allocator_type = Allocator;
			using traits = std::allocator_traits<allocator_type>;
			using value_type = typename traits::value_type;
			using pointer = typename traits::pointer;

			LiteVector();
			LiteVector(size_t capacity);
			LiteVector(std::initializer_list<T> list);

			LiteVector(const LiteVector<T>& other);
			LiteVector(LiteVector<T>&& other) noexcept;

			~LiteVector();
			
			size_t size() const { return m_size; }

			void reserve(size_t newCapacity);
			void shrink_to_fit();
			void push_back(const T& value);
			void push_back(T&& value);

			template<typename... Args>
			void emplace_back(Args&&... args);
		
			LiteVector<T, Allocator>& operator=(const LiteVector<T>& other);
			LiteVector<T, Allocator>& operator=(LiteVector<T>&& other) noexcept;

			T& operator[](size_t index) { return m_data[index]; }
			const T& operator[](size_t index) const { return m_data[index]; }

		private:
			void clear();
			bool capacity_reached() { return m_size >= m_capacity; }

		private:
			T* m_data = nullptr;
			size_t m_size = 0;
			size_t m_capacity = 0;

			allocator_type m_allocator = allocator_type();
	};
}

#include "LiteVector.tpp"
