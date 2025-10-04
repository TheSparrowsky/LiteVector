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
	LiteVector<T>::LiteVector(std::initializer_list<T> list)
	{
		reserve(list.size());
		for(const T& item : list)
			emplace_back(item);
	}

	template<typename T>
	LiteVector<T>::LiteVector(const LiteVector<T>& other)
	{
		reserve(other.size());

		for(size_t i = 0; i < other.size(); i++)
		{
			new (m_data + i) T(other[i]);
			m_size++;
		}
	}

	template<typename T>
	LiteVector<T>::LiteVector(LiteVector<T>&& other) noexcept
		: m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity)
	{
		other.m_size = 0;
		other.m_capacity = 0;
		other.m_data = nullptr;
	}

	template<typename T>
	LiteVector<T>::~LiteVector()
	{
		clear();
	}

	template<typename T>
	LiteVector<T>& LiteVector<T>::operator=(const LiteVector<T>& other)
	{
		if(this == &other)
			return *this;

		clear();

		reserve(other.m_size);
		m_size = other.m_size;

		for(size_t i = 0; i < m_size; i++)
			new (m_data + i) T(other[i]);

		return *this;
	}

	template<typename T>
	LiteVector<T>& LiteVector<T>::operator=(LiteVector<T>&& other) noexcept
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

	template<typename T>
	void LiteVector<T>::reserve(size_t newCapacity)
	{
		if(newCapacity < m_size)
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
	void LiteVector<T>::shrink_to_fit()
	{
		reserve(m_size);
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

	template<typename T>
	template<typename... Args>
	void LiteVector<T>::emplace_back(Args&&... args)
	{
		if(capacity_reached())
			reserve(m_capacity == 0 ? 1 : m_capacity * 2);

		new (m_data + m_size) T(std::forward<Args>(args)...);
		m_size++;
	}

	template<typename T>
	void LiteVector<T>::clear()
	{
		for(size_t i = 0; i < m_size; i++)
			m_data[i].~T();

		if(m_data != nullptr)
			::operator delete(m_data);
		m_data = nullptr;
		m_size = 0;
		m_capacity = 0;
	}
}
