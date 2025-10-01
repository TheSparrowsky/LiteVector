#include <memory>

namespace LV
{
	template<typename T>
	LiteVector<T>::LiteVector()
	{
	}

	template<typename T>
	LiteVector<T>::LiteVector(size_t capacity)
	{
		reserve(capacity);
	}

	template<typename T>
	LiteVector<T>::~LiteVector()
	{
		for(size_t i = 0; i < m_size; i++)
		{
			m_data[i].~T();
		}

		::operator delete(m_data);
		m_data = nullptr;
	}
	
	template<typename T>
	void LiteVector<T>::reserve(size_t newCapacity)
	{
		if(newCapacity <= m_capacity)
			return;

		T* tempPtr = static_cast<T*>(::operator new(sizeof(T) * newCapacity));

		for(size_t i = 0; i < m_size; i++)
		{
			new (tempPtr + i) T(std::move_if_noexcept(m_data[i]));
			m_data[i].~T();
		}

		::operator delete(m_data);

		m_data = tempPtr;
		m_capacity = newCapacity;
	}
	
	template<typename T>
	void LiteVector<T>::push_back(const T& value)
	{
		if(capacity_reached())
			reserve(m_capacity == 0 ? 1 : m_capacity * 2);

		new (m_data + m_size) T(value);
		m_size++;
	}
	
	template<typename T>
	void LiteVector<T>::push_back(T&& value)
	{
		if(capacity_reached())
			reserve(m_capacity == 0 ? 1 : m_capacity * 2);

		new (m_data + m_size) T(std::move(value));
		m_size++;
	}
}
