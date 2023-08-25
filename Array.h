#pragma once
#include"Iterator.h"
#include"Data.h"
#include<initializer_list>

namespace MStd {
	template<class T>
	class Array {
		T* data;
		size_t len;
		void copy_data(T* data, size_t length) {
			for (size_t i = 0; i < length; i++)
			{
				this->data[i] = data[i];
			}
		}
	public:
		Array() :data(nullptr), len(0) {}
		Array(T* data, size_t length) {
			this->data = new T[length];
			copy_data(data, length);
			len = length;
		}
		Array(std::initializer_list<T> data) {
			this->data = new T[data.size()];
			for (T datum : data)
				this->data[len++] = datum;
		}
		Array(const Array& other) {
			this->data = new T[other.len];
			copy_data(other.data, other.len);
			len = other.len;
		}
		Array(Iterator<T> begin, Iterator<T> end) {
			this->data = new T[end - begin];
			len = 0;
			for (Iterator<T> it = begin; it != end; it++)
				this->data[len++] = *it;
		}
		Array(Array&& other) {
			this->data = new T[other.len];
			copy_data(other.data, other.len);
			len = other.len;
		}
		size_t size() const {
			return len;
		}
		void assign(T* array, size_t length) {
			if (data) {
				delete[]data;
				data = nullptr;
				len = 0;
			}
			this->data = new T[length];
			copy_data(array, length);
			len = length;
		}
		void assign(std::initializer_list<T> data) {
			if (this->data) {
				delete[] this->data;
				this->data = nullptr;
				len = 0;
			}
			this->data = new T[data.size()];
			for (T datum : data)
				this->data[len++] = datum;
		}
		void assign(Iterator<T> begin, Iterator<T> end) {
			if (this->data) {
				delete[] this->data;
				this->data = nullptr;
				len = 0;
			}
			this->data = new T[end - begin];
			len = 0;
			for (Iterator<T> it = begin; it != end; it++)
				this->data[len++] = *it;
		}
		Array& operator = (const Array& other) {
			if (data) {
				delete[] data;
				len = 0;
				data = nullptr;
			}
			this->data = new T[other.size()];
			copy_data(other.data, other.len);
			len = other.len;
		}
		Array& operator =(Array&& other) {
			if (data) {
				delete[] data;
				len = 0;
				data = nullptr;
			}
			this->data = new T[other.size()];
			copy_data(other.data, other.len);
			len = other.len;
			return *this;
		}
		T& operator[](size_t index) {
			return data[index];
		}
		const T* Array_data() const{
			return data;
		}
		Iterator<T> begin() {
			return Iterator<T>(data);
		}
		Iterator<T> end() {
			return Iterator<T>(data + len);
		}
		void sort(Function<bool, T, T> comparor = [](T a, T b) {return a < b; }) {
			MStd::sort<T>(begin(), end(), comparor);
		}
		~Array() {
			if (data)
				delete[]data;
		}
	};
	template<class T>
	Array<T> unique(Iterator<T> begin, Iterator<T> end) {
		sort<T>(begin, end, [](T a, T b) {return a < b; });
		T* arr = new T[end - begin];
		size_t len = 0;
		arr[len++] = *begin;
		for (Iterator<T> it = begin + 1; it != end; it++)
			if (*it != *(it - 1))
				arr[len++] = *it;
		Array<T> array(arr, len);
		delete[] arr;
		return array;
	}
	class ByteArray :public Array<char>
	{
	public:
		ByteArray() :Array<char>() {}
		ByteArray(const char* data) {
			assign(data);
		}
		const char* Array_data()const {
			return Array<char>::Array_data();
		}
		size_t size()const {
			return Array<char>::size() - 1;
		}
		void assign(const char* data) {
			size_t len = std::strlen(data);
			Array<char>::assign((char*)data, len + 1);
		}
		void assign(char* data, size_t length) {
			Array<char>::assign(data, length+1);
			(*this)[length] = '\0';
		}
	};
}