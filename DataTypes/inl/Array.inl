#include <cassert>
#include "Array.h"

namespace aie
{
	template<typename T, int GROW_SIZE>
	inline Array<T, GROW_SIZE>::Array()
		: m_length{ 0 }, m_capacity{ GROW_SIZE }, m_data{ new T[GROW_SIZE] }
	{}

	template<typename T, int GROW_SIZE>
	inline Array<T, GROW_SIZE>::Array(initializer_list<T> data)
		: m_length{ 0 }, m_capacity{ GROW_SIZE }, m_data{ new T[GROW_SIZE] }
	{
		assert(data.size() < m_capacity);

		for (size_t i = 0; i < data.size(); ++i)
		{
			m_data[i] = *(data.begin() + i);
		}

		m_length = data.size();
	}

	template<typename T, int GROW_SIZE>
	inline Array<T, GROW_SIZE>::Array(const Array& arr)
		: m_length{ arr.m_length }, m_capacity{ arr.m_capacity }, m_data{ new T[arr.m_capacity] }
	{
		memcpy_s(m_data, m_capacity * sizeof(T), arr.m_data, arr.m_capacity * sizeof(T));
	}

	template<typename T, int GROW_SIZE>
	inline Array<T, GROW_SIZE>::Array(Array&& arr) noexcept
		: m_length{ arr.m_length }, m_capacity{ arr.m_capacity }, m_data{ new T[arr.m_capacity] }
	{
		memmove_s(m_data, m_capacity * sizeof(T), arr.m_data, arr.m_capacity * sizeof(T));
	}

	template<typename T, int GROW_SIZE>
	inline Array<T, GROW_SIZE>::~Array()
	{
		delete[] m_data;
		m_data = nullptr;

		m_length = 0;
	}

	template<typename T, int GROW_SIZE>
	inline void Array<T, GROW_SIZE>::Add(T item)
	{
		if (m_length + 1 >= m_capacity)
		{
			Resize();
		}

		m_data[m_length++] = item;
	}

	template<typename T, int GROW_SIZE>
	inline void Array<T, GROW_SIZE>::AddRange(T* items, size_t count)
	{
		for (size_t i = 0; i < count; i++)
		{
			Add(items[i]);
		}
	}

	template<typename T, int GROW_SIZE>
	inline void Array<T, GROW_SIZE>::AddRange(initializer_list<T> items)
	{
		for (T item : items)
		{
			Add(item);
		}
	}

	template<typename T, int GROW_SIZE>
	inline void Array<T, GROW_SIZE>::RemoveAt(size_t index)
	{
		assert(index < m_length);

		m_data[index] = T();

		for (size_t i = index; i < m_length - 1; ++i)
		{
			m_data[i] = m_data[i + 1];
		}

		m_length--;
	}

	template<typename T, int GROW_SIZE>
	inline size_t Array<T, GROW_SIZE>::Length() const
	{
		return m_length;
	}

	template<typename T, int GROW_SIZE>
	inline size_t Array<T, GROW_SIZE>::Capacity() const
	{
		return m_capacity;
	}

	template<typename T, int GROW_SIZE>
	inline Array<T, GROW_SIZE>& Array<T, GROW_SIZE>::operator=(const Array& rhs)
	{
		if (*this == rhs)
		{
			return *this;
		}

		if (m_data != nullptr)
		{
			delete[] m_data;
			m_data = nullptr;
		}

		m_capacity = rhs.m_capacity;
		m_length = rhs.m_length;
		m_data = new T[m_capacity];

		memcpy_s(m_data, m_capacity * sizeof(T), rhs.m_capacity, rhs.m_capacity * sizeof(T));

		return *this;
	}

	template<typename T, int GROW_SIZE>
	inline Array<T, GROW_SIZE>& Array<T, GROW_SIZE>::operator=(Array&& rhs) noexcept
	{
		if (*this == rhs)
		{
			return *this;
		}

		if (m_data != nullptr)
		{
			delete[] m_data;
			m_data = nullptr;
		}

		m_capacity = rhs.m_capacity;
		m_length = rhs.m_length;
		m_data = new T[m_capacity];

		memmove_s(m_data, m_capacity * sizeof(T), rhs.m_capacity, rhs.m_capacity * sizeof(T));

		return *this;
	}

	template<typename T, int GROW_SIZE>
	inline bool Array<T, GROW_SIZE>::operator==(const Array& rhs)
	{
		// If the length or the capacity are different, return false
		if (m_length != rhs.m_length || m_capacity != rhs.m_capacity)
		{
			return false;
		}

		// Validate each data element matches.
		for (size_t i = 0; i < m_length; ++i)
		{
			if (m_data[i] != rhs.m_data[i])
			{
				// One of the elements aren't the same, so this is not an equal array
				return false;
			}
		}

		// All components are equal so we are a valid comparison
		return true;
	}

	template<typename T, int GROW_SIZE>
	inline bool Array<T, GROW_SIZE>::operator!=(const Array& rhs)
	{
		return !(*this == rhs);
	}

	template<typename T, int GROW_SIZE>
	T& Array<T, GROW_SIZE>::operator[](size_t index)
	{
		assert(index < m_length);

		return m_data[index];
	}

	template<typename T, int GROW_SIZE>
	const T& Array<T, GROW_SIZE>::operator[](size_t index) const
	{
		assert(index < m_length);

		return m_data[index];
	}

	template<typename T, int GROW_SIZE>
	inline void Array<T, GROW_SIZE>::Resize()
	{
		size_t oldCapacity = m_capacity;
		m_capacity += GROW_SIZE;

		T* copy = new T[m_capacity];
		memcpy_s(copy, m_capacity * sizeof(T), m_data, oldCapacity * sizeof(T));

		delete[] m_data;
		m_data = copy;
	}

	template<typename T, int GROW_SIZE>
	ostream& operator<<(ostream& stream, const Array<T, GROW_SIZE>& arr)
	{
		stream << "{ ";

		for (size_t i = 0; i < arr.Length(); ++i)
		{
			stream << arr[i] << (i + 1 < arr.Length() ? ", " : " ");
		}

		stream << "}";
		return stream;
	}
}