#pragma once

#include <initializer_list>
#include <ostream>

using std::initializer_list;
using std::ostream;

namespace aie
{
	template<typename T, const int GROW_SIZE = 8>
	class Array
	{
	public:
		Array();
		Array(initializer_list<T> data);

		Array(const Array& arr);
		Array(Array&& arr) noexcept;

		~Array();

	public:
		void Add(T item);
		void AddRange(T* items, size_t count);
		void AddRange(initializer_list<T> items);
		void RemoveAt(size_t index);

		size_t Length() const;
		size_t Capacity() const;

	public:
		Array& operator=(const Array& rhs);
		Array& operator=(Array&& rhs) noexcept;

		bool operator==(const Array& rhs);
		bool operator!=(const Array& rhs);

		T& operator[](size_t i);
		const T& operator[](size_t i) const;

		T* operator*();

		template<typename U, const int G_S>
		friend ostream& operator<<(ostream& stream, const Array<U, G_S>& arr);

	private:
		size_t m_length;
		size_t m_capacity;

		T* m_data;

	private:
		void Resize();

	};
}

#include "inl/Array.inl"