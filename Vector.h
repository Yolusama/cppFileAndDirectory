#pragma once
#include"Array.h"
namespace MStd {
	template<typename T>
	class Vector {
	public:
		class Vector_Iterator :public Iterator<T> {
		public:
			Vector_Iterator() :Iterator<T>(nullptr) {}
			Vector_Iterator(T* it) :Iterator<T>(it) {
			}
			Vector_Iterator& operator --(int)
			{
				--this->Ptr;
				return *this;
			}
			Vector_Iterator operator --(){
				this->Ptr--;
				return *this;
			}
			Vector_Iterator operator +(size_t count){
				return Vector_Iterator(this->Ptr + count);
			}
		};
		class Vector_ReIterator:public ReIterator<T>
		{
		public:
			Vector_ReIterator() :ReIterator<T>(nullptr) {}
			Vector_ReIterator(T* rit) :ReIterator<T>(rit) {}
			Vector_ReIterator& operator ++(int)
			{
				--this->Ptr;
				return *this;
			}
			Vector_ReIterator operator ++() {
				this->Ptr--;
				return *this;
			}
			Vector_ReIterator& operator --(int)
			{
				++this->Ptr;
				return *this;
			}
			Vector_ReIterator operator --() {
				this->Ptr++;
				return *this;
			}
			bool operator > (Vector_ReIterator iterator) {
				return this->Ptr< iterator.Ptr;
			}
			bool operator >= (Vector_ReIterator iterator) {
				return this->Ptr <= iterator.Ptr;
			}
			bool operator < (Vector_ReIterator iterator) {
				return this->Ptr > iterator.Ptr;
			}
			bool operator <= (Vector_ReIterator iterator) {
				return this->Ptr >= iterator.Ptr;
			}
			Vector_ReIterator operator +(size_t count) {
				return Vector_ReIterator(this->Ptr-count);
			}
		};
		using VIterator = Vector_Iterator;
		using VReIterator = Vector_ReIterator;
		using VLong = long long;
	private:
		T* data;
		size_t len = 0;
		size_t cap = 0;
	protected:
		void alloc(size_t newCapacity) {
			T* data = new T[newCapacity];
			if (this->data != nullptr)
			{
				CopyData(data, this->data, len);
				delete[] this->data;
			}
			this->data = data;
			cap = newCapacity;
		}
		void CopyData(T*& to, T* from, size_t length) {
			for (size_t i = 0; i < length; i++)
				to[i] = std::move(from[i]);
		}
	public:
		Vector(){
			alloc(2);
		}
		Vector(T* arr, VLong length) {
			data = new T[length];
			CopyData(data, arr, length);
			len = length;
			cap = len;
		}
		Vector(std::initializer_list<T> data) {
			cap = data.size();
			alloc(cap);
			for (T datum : data) {
				this->data[len++] = datum;
			}
		}
		Vector(VIterator head, VIterator tail) {
			cap = tail.Ptr - head.Ptr;
			alloc(cap);
			for (VIterator a = head; a < tail; a++)
				data[len++] = *a;
		}
		Vector(const size_t count, T val) {
			cap = count;
			alloc(cap);
			for (size_t i = 0; i < count; i++)
				data[len++] = val;
		}
		Vector(Vector&& other) noexcept {
			this->data = new T[other.len];
			CopyData(this->data, other.data, other.len);
			this->len = other.len;
			this->cap = other.cap;
		}
		Vector(Array<T> array) {
			alloc(array.size());
			CopyData(this->data,(T*) array.Array_data(), array.size());
			len = array.size();
		}
		void assign(T* arr, size_t length) {
			if (data) {
				clear();
			}
			data = new T[length];
			CopyData(data, arr, length);
			len = length;
			cap = len;
		}
		void assign(Array<T> array) {
			if (data) {
				clear();
			}
			alloc(array.size());
			len = array.size();
			CopyData(data, (T*)array.Array_data(), len);
		}
		void assign(std::initializer_list<T> data) {
			if (this->data)
				clear();
			cap = data.size();
			alloc(cap);
			for (T datum : data) {
				this->data[len++] = datum;
			}
		}
		void assign(VIterator head, VIterator tail) {
			if (data)
				clear();
			cap = tail.Ptr - head.Ptr;
			alloc(cap);
			for (VIterator a = head; a < tail; a++)
				data[len++] = *a;
		}
		void assign(const size_t count, T val) {
			if (data)
				clear();
			cap = count;
			alloc(cap);
			for (size_t i = 0; i < count; i++)
				data[len++] = val;
		}
		const T front()const {
			return data[0];
		}
		const T back()const {
			return data[len - 1];
		}
		VIterator begin() const {
			return Vector_Iterator(data);
		}
		VIterator end() const {
			return VIterator(data + len);
		}
		VReIterator rbegin() const {
			return VReIterator(data + len-1);
		}
		VReIterator rend() const {
			return VReIterator(data-1);
		}
		void push_back(const T& val) {
			if (full())return;
			if (len + 1 > cap)
				alloc(cap + cap / 2);
			data[len++] = val;
		}
		void push_back(T&& val) {
			T _val = std::move(val);
			push_back(_val);
		}
		template<typename... Args>
		void emplace_back(Args... construct_arg) {
			push_back(T(std::forward<Args>(construct_arg)...));
		}
		template<typename... Args>
		void emplace(VIterator where,Args... construct_arg) {
			insert(T(std::forward<Args>(construct_arg)...), where);
		}
		template<typename... Args>
		void emplace(size_t pos, Args... construct_arg) {
			insert(T(std::forward<Args>(construct_arg)...),pos);
		}
		void pop_back() {
			if (len == 0)return;
			data[len - 1].~T();
			len--;
		}
		VLong last_index_of(T val) {
			for (VLong i = len - 1; i >= 0; i--)
				if (val == data[i])
					return i;
			return -1;
		}
		VLong index_of(T val) const{
			for (VLong i = 0; i < len; i++)
				if (data[i] == val)
					return i;
			return -1;
		}
		VIterator find(T val) const{
			for (VIterator it = begin(); it != end(); it++)
				if (*it == val)
					return it;
			return end();
		}
		VIterator find_last(T val) const{
			for (VIterator i = rbegin(); i != rend(); i++)
				if (*i == val)
					return i;
			return rend();
		}
		void insert(const T&val,VLong pos) {
			if (full())return;
			if (len + 1 > cap)
				alloc(cap + cap / 2);
			if (pos<0 || pos>len)return;
			if (pos == len) {
				push_back(val);
				return;
			}
			size_t i;
			if (pos == 0) {
				for (i = len; i >0; i--)
					data[i] = data[i-1];
				data[pos] = val;
				len++;
				return;
			}
			for (i = len - 1; i >= pos; i--)
				data[i + 1] = data[i];
			data[pos] = val;
			len++;
		}
		void insert(T&& val, VLong pos)
		{
			T _val = std::move(val);
			insert(val, pos);
		}
		void insert(const T& val, VIterator where) {
			size_t pos = where.Ptr - begin().Ptr;
			insert(val, pos);
		}
		void insert(T&& val, VIterator where) {
			T _val = std::move(val);
			insert(val, where);
		}
		T remove(size_t pos) {
			if (pos >= len)
				return *(end());
			T val;
			if (pos == len - 1)
			{
				val = data[len - 1];
				pop_back();
				return val;
			}
			size_t i;
			val = data[pos];
			for (i = pos; i < len; i++)
				data[i] = data[i+1];
			len--;
			return val;
		}
		T remove(VIterator where) {
			size_t pos = where.Ptr - this->begin().Ptr;
			return remove(pos);
		}
		void clear() {
			this->len = 0;
			this->cap = 0;
			delete[] this->data;
			this->data = nullptr;
		}
		T at(size_t index) const{
			T val = (*this)[index];
			return val;
		}
		T& operator[](size_t index) const {
			if (index >= len)
			{
				T a = T();
				return a;
			}
			return data[index];
		}
		Vector(const Vector& other) {
			this->data = new T[other.len];
			CopyData(this->data, other.data, other.len);
			this->len = other.len;
			this->cap = other.cap;
		}
		size_t size()const {
			return len;
		}
		size_t capacity() const{
			return cap;
		}
		T* VecData() const{
			return this->data;
		}
		~Vector() {
			if (data)
				clear();
	   }
	   Vector& operator =(const Vector& other) {
			if (data) {
				delete[] data;
				this->len = 0;
				this->cap = 0;
			}
			data = new T[other.len];
			this->len = other.len;
			this->cap = other.cap;
			CopyData(data, other.data,this->len);
			return *this;
	    }
	   Vector& operator =(Vector&& other) {
		   if (data) {
			   delete[] data;
			   this->len = 0;
			   this->cap = 0;
		   }
		   data = new T[other.len];
		   this->len = other.len;
		   this->cap = other.cap;
		   CopyData(data, other.data, this->len);
		   return *this;
	   }
	   bool empty()const {
		   return len == 0;
	   }
	   void shrink_to_fit() {
		   cap = len;
	   }
	   void reserve(size_t count) {
		   this->cap = count;
	   }
	   void reverse() {
		   for (size_t i = 0; i < len / 2; i++)
		   {
			   T t = data[i];
			   data[i] = data[len - 1 - i];
			   data[len - 1 - i] = t;
		   }
	   }
	   void swap(Vector& other) {
		   Vector temp(*this);
		   T* data = other.VecData();
		   this->assign(data,other.size());
		   this->cap = other.cap;
		   other = temp;
	   }
	   size_t max_size()const {
		   return ULLONG_MAX / sizeof(T);
	   }
	   void sort(Function<bool, T, T> comparor = [](T a, T b) {return a < b; }) {
		   MStd::sort(begin(), end(), comparor);
	   }
	   void resize(size_t size,T val=T()) {
		   if (size == len)return;
		   if (size < len)
		   {
			   for (size_t i = 0; i < len - size; i++)
				   pop_back();
			   return;
		   }
		   if (size > len) {
			   if (size >= cap)
				   alloc(len);
			   for (size_t i = 0; i > size - len; i++)
				   push_back(val);
			   return;
		   }
	   }
	   Array<T> to_array() const{
		   return Array<T>(begin(),end());
	   }
	   void unique() {
		   Array<T> unqiueArr = MStd::unique(begin(), end());
		   this->assign(unqiueArr);
	   }
	   bool full() const{
		   return len == max_size();
	   }
	   Vector find_if(Function<bool, T>func) {
		   Vector v;
		   for (size_t i = 0; i < size(); i++)
			   if (func(v[i]))
				   v.push_back(v[i]);
		   return v;
	   }
	};
}