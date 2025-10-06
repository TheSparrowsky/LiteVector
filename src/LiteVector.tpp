#include <memory>

namespace LV
{
	template<typename T, typename Allocator>
	LiteVector<T, Allocator>::LiteVector()
	{
	}

	template<typename T, typename Allocator>
	LiteVector<T, Allocator>::LiteVector(size_t capacity) 
	{
		reserve(capacity);
	}

	template<typename T, typename Allocator>
	LiteVector<T, Allocator>::LiteVector(std::initializer_list<T> list)
	{
		reserve(list.size());
		for(const T& item : list)
			emplace_back(item);
	}

	template<typename T, typename Allocator>
	LiteVector<T, Allocator>::LiteVector(const LiteVector<T>& other)
	{
		reserve(other.size());

		for(size_t i = 0; i < other.size(); i++)
		{
			traits::construct(m_allocator, m_data + i, other[i]);
			m_size++;
		}
	}

	template<typename T, typename Allocator>
	LiteVector<T, Allocator>::LiteVector(LiteVector<T>&& other) noexcept
		: m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity)
	{
		other.m_size = 0;
		other.m_capacity = 0;
		other.m_data = nullptr;
	}

	template<typename T, typename Allocator>
	LiteVector<T, Allocator>::~LiteVector()
	{
		clear();
	}

	template<typename T, typename Allocator>
	LiteVector<T, Allocator>& LiteVector<T, Allocator>::operator=(const LiteVector<T>& other)
	{
		if(this == &other)
			return *this;

		clear();

		reserve(other.m_size);
		m_size = other.m_size;

		for(size_t i = 0; i < m_size; i++)
			traits::construct(m_allocator, m_data + i, other[i]);

		return *this;
	}

	template<typename T, typename Allocator>
	LiteVector<T, Allocator>& LiteVector<T, Allocator>::operator=(LiteVector<T>&& other) noexcept
	{
		if(this == &other)
			return *this;

		clear();

		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = other.m_data;

		other.m_size = 0;
		other.m_capacity = 0;
		other.m_data = nullptr;

		return *this;
	}

	template<typename T, typename Allocator>
	void LiteVector<T, Allocator>::reserve(size_t newCapacity)
	{
		if(newCapacity < m_size)
			return;

		pointer tempPtr = traits::allocate(m_allocator, newCapacity);
		
		for(size_t i = 0; i < m_size; i++)
		{
			traits::construct(m_allocator, tempPtr + i, std::move_if_noexcept(m_data[i]));
			traits::destroy(m_allocator, m_data + i);
		}

		traits::deallocate(m_allocator, m_data, m_capacity);

		m_data = tempPtr;
		m_capacity = newCapacity;
	}

	template<typename T, typename Allocator>
	void LiteVector<T, Allocator>::shrink_to_fit()
	{
		reserve(m_size);
	}

	template<typename T, typename Allocator>
	void LiteVector<T, Allocator>::push_back(const T& value)
	{
		if(capacity_reached())
			reserve(m_capacity == 0 ? 1 : m_capacity * 2);

		traits::construct(m_allocator, m_data + m_size, value);
		m_size++;
	}
	
	template<typename T, typename Allocator>
	void LiteVector<T, Allocator>::push_back(T&& value)
	{
		if(capacity_reached())
			reserve(m_capacity == 0 ? 1 : m_capacity * 2);

		traits::construct(m_allocator, m_data + m_size, std::move(value));
		m_size++;
	}

	template<typename T, typename Allocator>
	template<typename... Args>
	void LiteVector<T, Allocator>::emplace_back(Args&&... args)
	{
		if(capacity_reached())
			reserve(m_capacity == 0 ? 1 : m_capacity * 2);

		new (m_data + m_size) T(std::forward<Args>(args)...);
		m_size++;
	}

	template<typename T, typename Allocator>
	void LiteVector<T, Allocator>::clear()
	{
		for(size_t i = m_size; i > 0; --i)
			traits::destroy(m_allocator, m_data - (i - 1));

		if(m_data != nullptr)
			traits::deallocate(m_allocator, m_data, m_capacity);

		m_data = nullptr;
		m_size = 0;
		m_capacity = 0;
	}
}
