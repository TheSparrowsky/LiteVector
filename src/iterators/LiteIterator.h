#pragma once

namespace LV
{
	template<typename T>
	class LiteIterator 
	{
		public:
			using iterator_category = std::random_access_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = T*;
			using reference = T&;

			explicit LiteIterator(pointer ptr = nullptr) : m_ptr(ptr) {}

			reference operator*() const { return *m_ptr; }
			reference operator->() const { return m_ptr; }

			LiteIterator& operator++() { m_ptr++; return *this; }
			LiteIterator operator++(int) { LiteIterator temp = *this; ++(*this); return temp; }

			LiteIterator& operator--() { m_ptr--; return *this; }
			LiteIterator operator--(int) { LiteIterator temp = *this; --(*this); return temp; }

			LiteIterator operator+(difference_type n) const { return LiteIterator(m_ptr + n); }
			LiteIterator operator-(difference_type n) const { return LiteIterator(m_ptr - n); }
			difference_type operator-(const LiteIterator& other) const { return m_ptr - other.m_ptr; }
			
			LiteIterator& operator+=(difference_type n) { m_ptr += n; return *this; }
			LiteIterator& operator-=(difference_type n) { m_ptr -= n; return *this; }

			reference operator[](difference_type n) const { return *(m_ptr + n); }

			bool operator==(const LiteIterator& other) const { return m_ptr == other.m_ptr; }
			bool operator!=(const LiteIterator& other) const { return m_ptr != other.m_ptr; }
			bool operator<(const LiteIterator& other) const { return m_ptr < other.m_ptr; }
			bool operator>(const LiteIterator& other) const { return m_ptr > other.m_ptr; }
			bool operator<=(const LiteIterator& other) const { return m_ptr <= other.m_ptr; }
			bool operator>=(const LiteIterator& other) const { return m_ptr >= other.m_ptr; }

		private:
			pointer m_ptr;
	};
}
