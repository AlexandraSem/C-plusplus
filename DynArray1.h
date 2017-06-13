#pragma once
#include <iostream>
#include <initializer_list>

template<class T>
class DynArray
{
public:
	DynArray(int capacity);
	DynArray() = default;
	DynArray(std::initializer_list<T> const& list);
	DynArray(DynArray<T> const& dynArray);
	DynArray<T>& operator=(DynArray<T> const& dynArray);
	DynArray<T>& operator=(DynArray<T>&& dynArray);
	DynArray(DynArray<T>&& dynArray);
	DynArray<T> operator*(T element);
	~DynArray()
	{
		delete[] m_data;
	}
	int GetCount() const
	{
		return m_count;
	}
	
	template<class T>
	friend std::ostream& operator<<(std::ostream& stream, DynArray<T> const& array);
private:
	T* m_data = nullptr;
	int m_capacity = 0;
	int m_count = 0;
};

template<class T>
std::ostream& operator<<(std::ostream& stream, DynArray<T> const& array)
{
	for (int i = 0; i < array.m_count; ++i)
	{
		stream << array.m_data[i] << " ";
	}
	return stream;
}

template<class T>
DynArray<T>::DynArray(int capacity) :
	m_capacity(capacity)
{
	m_data = new T[m_capacity];
}

template<class T>
DynArray<T>::DynArray(std::initializer_list<T> const& list)
{
	m_capacity = list.size();
	std::initializer_list<T>::iterator it = list.begin();
	m_data = new T[m_capacity];
	T* ptr = m_data;
	/*std::initializer_list<T>::iterator it = list.begin();
	for (; it != list.end(); ++it)
	{
	*(ptr++) = *it;
	} */
	for (T const& element : list/*текущий элемент : контейнер*/)
	{
		*(ptr++) = element;
	}
	m_count = m_capacity;
}

//template<class T>
//DynArray<T>::DynArray() :
//	m_count(0), m_capacity(0), m_data(nullptr)
//{
//}

template<class T>
DynArray<T>::DynArray(DynArray<T> const& dynArray)
{
	m_capacity = dynArray.m_capacity;
	m_count = dynArray.m_count;
	m_data = new T[m_capacity]; 
	for (int i = 0; i < m_count; ++i)
	{
		m_data[i] = dynArray.m_data[i];
	}
}
template<class T>
DynArray<T>& DynArray<T>::operator=(DynArray<T> const& dynArray)
{
	if (this != &dynArray)
	{
		m_capacity = dynArray.m_capacity;
		m_count = dynArray.m_count;
		delete[] m_data;
		m_data = m_capacity != 0 ? new T[m_capacity] : nullptr;
		for (int i = 0; i < m_count; ++i)
		{
			m_data[i] = dynArray.m_data[i];
		}
	}
	return *this;
}

template<class T>
DynArray<T>& DynArray<T>::operator=(DynArray<T>&& dynArray)
{
	if (this != &dynArray)
	{
		DynArray<T> tmp(dynArray);
		*this = std::move(tmp);
	}
	return *this;
}
template<class T>
DynArray<T>::DynArray(DynArray<T>&& dynArray)
{
	delete[] m_data;
	m_data = dynArray.m_data;
	m_capacity = dynArray.m_capacity;
	m_count = dynArray.m_count;
	dynArray.m_data = nullptr;
	dynArray.m_capacity = 0;
	dynArray.m_count = 0;
}
template<class T>
DynArray<T> DynArray<T>::operator*(T element)
{
	DynArray result(*this);
	for (int i = 0; i < m_count; i++)
	{
		result.m_data[i] *= element;
	}
	return result;
}
