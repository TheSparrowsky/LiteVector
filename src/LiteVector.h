#include <cstdio>

namespace LV
{
	template<typename T>
	class LiteVector
	{
		public:
			LiteVector();
			LiteVector(size_t capacity);

			~LiteVector();

			void reserve(size_t newCapacity);
			void push_back(const T& value);
			void push_back(const T&& value);
		
		private:
			bool capacity_reached() { return m_size >= m_capacity; }

		private:
			T* m_data = nullptr;
			size_t m_size = 0;
			size_t m_capacity = 0;
	};
}

#include "LiteVector.tpp"
