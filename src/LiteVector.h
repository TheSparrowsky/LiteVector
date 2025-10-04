#pragma once
#include <cstdio>

namespace LV
{
	template<typename T>
	class LiteVector
	{
		public:
			LiteVector();
			LiteVector(size_t capacity);
			LiteVector(std::initializer_list<T> list);

			LiteVector(const LiteVector& other);
			LiteVector(LiteVector&& other) noexcept;

			~LiteVector();
			
			size_t size() const { return m_size; }

			void reserve(size_t newCapacity);
			void shrink_to_fit();
			void push_back(const T& value);
			void push_back(T&& value);

			template<typename... Args>
			void emplace_back(Args&&... args);
		
			LiteVector<T>& operator=(const LiteVector<T>& other);
			LiteVector<T>& operator=(LiteVector<T>&& other) noexcept;

			T& operator[](size_t index) { return m_data[index]; }
			const T& operator[](size_t index) const { return m_data[index]; }

		private:
			void clear();
			bool capacity_reached() { return m_size >= m_capacity; }

		private:
			T* m_data = nullptr;
			size_t m_size = 0;
			size_t m_capacity = 0;
	};
}

#include "LiteVector.tpp"
