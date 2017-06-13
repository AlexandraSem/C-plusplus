#pragma once

#include <initializer_list>
#include <iostream>

template<class T>
class DynArray
{
public:
	DynArray(int capacity);

	DynArray(std::initializer_list<T> const& list);
	DynArray() = default;
	DynArray(DynArray<T> const& dynArray);
	DynArray<T>& operator=(DynArray<T> const& dynArray);
	DynArray<T>& operator=(DynArray<T>&& dynArray);
	DynArray(DynArray<T>&& dynArray);
	DynArray<T> operator*(T element);

	template<class T>
	friend std::ostream& operator<<(std::ostream& stream, DynArray<T> const& array);

	~DynArray();
	int GetCount() const;
	void PushBack(T const& element);
	T& operator[](int idx);
	T const& operator[](int idx) const;

	void Reserve(int newCapacity);


private:
	T* m_data = nullptr;
	int m_capacity = 0;
	int m_count = 0;
};

template<class T>
DynArray<T>::~DynArray()
{
	delete[] m_data;
};

template<class T>
int DynArray<T>::GetCount() const
{
	return m_count;
}

template<class T>
std::ostream& operator<<(std::ostream& stream, DynArray<T> const& array)
{
	for (int i = 0; i < array.m_count; i++)
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
	m_data = new T[m_capacity];
	T* ptr = m_data;
	/*std::initializer_list<T>::iterator it = list.begin();
	for (; it != list.end(); ++it)
	{
	*(ptr++) = *it;
	} */

	for (T const& element : list)
	{
		*(ptr++) = element;
	}
	m_count = m_capacity;
}

template<class T>
DynArray<T>::DynArray(DynArray<T> const& dynArray)
{
	m_capacity = dynArray.m_capacity;
	m_count = dynArray.m_count;
	m_data = new T[m_capacity];

	for (int i = 0; i < m_count; i++)
	{
		m_data[i] = dynArray.m_data[i];
	}
}

template<class T>
DynArray<T>& DynArray<T>::operator=(DynArray<T> const& dynArray)
{
	if (this != &dynArray)
	{
		DynArray<T> tmp(dynArray);
		*this = std::move(tmp);
	}
	return *this;
}

template<class T>
DynArray<T>& DynArray<T>::operator=(DynArray<T>&& dynArray)
{
	if (this != &dynArray)
	{
		delete[] m_data;
		m_data = dynArray.m_data;
		m_capacity = dynArray.m_capacity;
		m_count = dynArray.m_count;
		dynArray.m_data = nullptr;
		dynArray.m_capacity = 0;
		dynArray.m_count = 0;
	}
	return *this;
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

template<class T>
DynArray<T>::DynArray(DynArray<T>&& dynArray)
{
	m_data = dynArray.m_data;
	m_capacity = dynArray.m_capacity;
	m_count = dynArray.m_count;
	dynArray.m_data = nullptr;
	dynArray.m_capacity = 0;
	dynArray.m_count = 0;
}

template<class T>
void DynArray<T>::PushBack(T const& element)
{
	if (m_count == m_capacity)
	{
		Reserve(m_capacity == 0 ? 1 : m_capacity * 2);
	}
	m_data[m_count++] = element;
}

template<class T>
T& DynArray<T>::operator[](int idx)
{
	if (!(idx > 0 && idx < m_count))
	{
		std::cout << "Invalid index\n";
		exit(-1);
	}
	return m_data[idx];
}

template<class T>
T const& DynArray<T>::operator[](int idx) const
{
	DynArray<T>* nonConstThis = const_cast<DynArray<T>*>(this);
	return (*nonConstThis)[idx];
}


template<class T>
void DynArray<T>::Reserve(int newCapacity)
{
	m_capacity = newCapacity;
	if (m_count > m_capacity)
	{
		m_count = m_capacity;
	}
	T* newMemory = nullptr;
	if (m_capacity > 0)
	{
		newMemory = new T[m_capacity];
		for (int i = 0; i < m_count; i++)
		{
			newMemory[i] = std::move(m_data[i]);
		}
	}
	delete[] m_data;
	m_data = newMemory;
}
//main


// templates2.cpp : Defines the entry point for the console application.
//

#include "DynArray.h"

#include <iostream>

int main()
{
	DynArray<int> d = { 200, 300, 100 };

	DynArray<int> d1 = d * 5;
	std::cout << d1.GetCount() << "\n";

	/*int arr[] = { 5, 6, 7, 8 };
	for (int el : arr)
	{
	std::cout << el << " ";
	} */

	DynArray<int> const d2(d1);
	std::cout << d2[0] << "\n";
	d1[0] = -5;
	std::cout << d1[0] << "\n";

	return 0;
}////#include "Array.h"
////#include "ComplexClass.h"
////#include "String.h"
////#include "Student.h"
//#include "DynArray.h"
//
//#include <algorithm>
//#include <cstring>
//#include <iostream>
//#include <memory>
//
////template<class T>
////T const& max(T const& a, T const& b)
////{
////	return a > b ? a : b;
////}
////
////char const* max(char const* a, char const* b)
////{
////	return strcmp(a, b) > 0 ? a : b;
////}
////
////template<class T>
////T const& min(T const& a, T const& b)
////{
////	return a < b ? a : b;
////}
////
////template<class T>
////T const& max(T const& a, T const& b, T const& c)
////{
////	return max(max(a, b), c);
////}
////
////template<class T1, class T2>
////bool Greater(T1 const& a, T2 const& b)
////{
////	return a > (T1)b;
////}
////
////bool Greater(int const& a, double const& b)
////{
////	return (double)a > b;
////}
////
////
////template<class T>
////T* Find(T* array, int count, T const& element)
////{
////	for (int i = 0; i < count; i++)
////	{
////		if (array[i] == element)
////		{
////			return array + i;
////		}
////	}
////	return nullptr;
////}
////
////template<typename T>
////class AccumulationTraits;
////
////template<>
////class AccumulationTraits<int>
////{
////public:
////	typedef int AccT;
////};
////
////template<>
////class AccumulationTraits<char>
////{
////public:
////	typedef int AccT;
////};
////
////template<>
////class AccumulationTraits<const char>
////{
////public:
////	typedef int AccT;
////};
////
////template<>
////class AccumulationTraits<double>
////{
////public:
////	typedef double AccT;
////};
////
////template<>
////class AccumulationTraits<float>
////{
////public:
////	typedef double AccT;
////};
////
////template<typename T>
////T Average(T* array, int count)
////{
////	AccumulationTraits<T>::AccT alisa = 0;
////	for (int i = 0; i < count; i++)
////	{
////		alisa += array[i];
////	}
////	return alisa / count;
////}
//
////template<class T>
////class GreaterFromTwo
////{
////public:
////	GreaterFromTwo() = default;
////
////	bool operator()(T const& value1,
////		T const& value2) const
////	{
////		return value1 > value2;
////	}
////};
////
////class GreaterFromTwoStudentByRating
////{
////public:
////	GreaterFromTwoStudentByRating() = default;
////
////	bool operator()(Student const& value1,
////		Student const& value2) const
////	{
////		return value1.GetRating() > value2.GetRating();
////	}
////};
//
////template<class T, class Pred = GreaterFromTwo<T> >
////void BubbleSort(T* arr, int count, Pred compare = GreaterFromTwo<T>())
////{
////	for (int i = count - 1; i > 0; --i)
////	{
////		for (int j = 0; j < i; ++j)
////		{
////			if (compare(arr[j], arr[j + 1]))
////			{
////				// swap(arr[j], arr[j + 1]);
////				T tmp = std::move(arr[j]);
////				arr[j] = std::move(arr[j + 1]);
////				arr[j + 1] = std::move(tmp);
////			}
////		}
////	}
////}
////void plus(int& a, int b = 5)
////{
////	a += b;
////}
////template<class T>
////class Greater
////{
////	T m_value;
////public:
////	Greater() = default;
////	Greater(T value) : m_value(value)
////	{
////	};
////
////	bool operator()(T const& value) const
////	{
////		return m_value < value;
////	}
////};
////
////typedef bool(*GreaterFunc)(int const&);
////
////bool Greater(int const& value)
////{
////	return value > 5;
////}
////
////template<class T>
////class Compare
////{
////	T m_value;
////public:
////	Compare() = default;
////	Compare(T value) : m_value(value)
////	{
////	};
////
////	bool operator()(T const& value) const
////	{
////		return m_value == value;
////	}
////};
////
////typedef bool(*CompareFunc)(int const&);
////
////bool CompareWith5(int const& value)
////{
////	return value == 5;
////}
////
////bool GreaterThan5(int const& value)
////{
////	return value > 5;
////}
//
////template<class T1, class Pred>
////T1* Find(T1* array, int count, Pred compare)
////{
////	for (int i = 0; i < count; i++)
////	{
////		if (compare(array[i]))
////		{
////			return array + i;
////		}
////	}
////	return nullptr;
////}
//
//int main()
//{
//	//int a = 5, b = 6;
//	//int arr[] = { 1, 10, 5, 6, 7 };
//	//Compare<int> cmp(5);
//	//Compare<int> cmp1(3);
//	//int* result = Find(arr, 5, cmp1);
//	//if (result)
//	//{
//	//	std::cout << *result << "\n";
//	//}
//	//GreaterFromTwo<int> greaterFromTwo;
//
//	//BubbleSort(arr, 5);
//
//	//Student studArray[] = { Student("Petrov", 5.0), Student("Ivanov", 7.0) };
//	//BubbleSort(studArray, 2);
//	//BubbleSort(studArray, 2, GreaterFromTwoStudentByRating());
//	DynArray<int> d = { 200, 300, 100 };
//	DynArray<int> d1 = d*5;
//	DynArray<int>const d2(d1);
//	DynArray<int> const d2(d1);
//	std::cout << d2[0] << "\n";
//	d1[0] = -5;
//	std::cout << d1[0] << "\n";
//	//int arr[] = { 5,6,7,8 };
//	std::cout << d1 << "\n";
//	//for (int el : arr)
//	//{
//	//	std::cout << el << " ";
//	//}
//	//int a = 1;
//	//plus(a, 2);
//	//plus(a);
//	return 0;
//}
//	//Compare cmp(5);
//	//Compare cmp1(3);
//	/*if (cmp(a))
//	{
//		std::cout << "true\n";
//	}
//	else
//	{
//		std::cout << "false\n";
//	}
//	if (cmp(b))
//	{
//		std::cout << "true\n";
//	}
//	else
//	{
//		std::cout << "false\n";
//	}*/
//
//
////	int* result = Find(arr, 5, cmp1);
//	//if (result)
//	//{
//	//	std::cout << *result << "\n";
//	//}
