#pragma once
#include"Iterator.h"
#include"Function.h"
#include"StrParser.h"
#define var auto

namespace MStd {
	template<typename T>
	void exc(T& a, T& b) {
		T t = a;
		a = b;
		b = t;
	}
	class QSort
	{
		template<class T>
		static Iterator<T> position(Iterator<T> begin, Iterator<T> end, Function<bool, T, T> comparor) {
			T key = *begin;
			Iterator<T> i = begin;
			Iterator<T> j = end;
			while (i<j) {
				while(i<j&&(comparor(key,*j)||key==*j))
					j--;
				exc(*i, *j);
				while(i<j&&(comparor(*i,key)||key==*i))
					i++;
				exc(*i, *j);
			}
			return i;
		}
	public:
		template<class T>
		static void QuickSort(Iterator<T> begin, Iterator<T> end, Function<bool, T, T> comparor){
			if (end<=begin)return;
				Iterator<T> pos = position<T>(begin, end, comparor);
				QuickSort(pos + 1, end, comparor);
				QuickSort(begin, pos - 1, comparor);
		}
	};
	template<class T>
	void sort(Iterator<T> begin, Iterator<T> end, Function<bool, T, T> comparor) {
		QSort::QuickSort(begin, end-1, comparor);
	}
	template<class T1,class T2>
	struct Pair{
		T1 first;
		T2 second;
		Pair(){}
		Pair(T1 item1, T2 item2) :first(item1), second(item2) {}
		void swap(Pair& other) {
			Pair t(*this);
			this->first = other.first;
			this->second = other.second;
			other = t;
		}
	};
	template<class T1,class T2>
	Pair<T1, T2> MakePair(T1 item1, T2 item2) {
		return Pair<T1, T2>(item1, item2);
	}
	template<class T>
	struct Node
	{
		T val;
		Node() :val(T()) {}
		Node(T _val) :val(_val) {}
	};
	template<class T>
	class Data {
	private:
		T value;
	public:
		Data(T value) :value(value) {}
		const T get()const {
			return value;
		}
		void set(const T& value) {
			this->value = value;
		}
		void set(T&& value) {
			T _value = std::move(value);
			set(_value);
		}
		virtual const std::string to_string()const {
			return std::to_string(value);
		}
		virtual bool operator <(const Data& other)const {
			return value < other.value;
		}
		virtual bool operator <=(const Data& other)const {
			return value <= other.value;
		}
		virtual bool operator >(const Data& other)const {
			return value > other.value;
		}
		virtual bool operator >=(const Data& other)const {
			return value >= other.value;
		}
		virtual bool operator ==(const Data& other)const {
			return value == other.value;
		}
		virtual bool operator !=(const Data& other)const {
			return value != other.value;
		}
		virtual Data operator+(const Data& other) const{
			return Data(value + other.value);
		}
		virtual Data operator-(const Data& other) const{
			return Data(value - other.value);
		}
		virtual Data operator*(const Data& other) const{
			return Data(value * other.value);
		}
		virtual Data operator /(const Data& other) const{
			return Data(value / other.value);
		}
		virtual Data& operator +=(const Data& other) {
			this->set(value + other.value);
			return *this;
		}
		virtual Data& operator -=(const Data& other) {
			this->set(value - other.value);
			return *this;
		}
		virtual Data& operator *=(const Data& other) {
			this->set(value * other.value);
			return *this;
		}
		virtual Data& operator /=(const Data& other) {
			this->set(value / other.value);
			return *this;
		}
		virtual Data& operator +=(Data&& other) {
			this->set(value + other.value);
			return *this;
		}
		virtual Data& operator -=(Data&& other) {
			this->set(value - other.value);
			return *this;
		}
		virtual Data& operator *=(Data&& other) {
			this->set(value * other.value);
			return *this;
		}
		virtual Data& operator /=(Data&& other) {
			this->set(value / other.value);
			return *this;
		}
		virtual ~Data() {}
		template<typename Ty> friend std::ostream& operator <<(std::ostream& out, Data<Ty> data);
		template<typename Ty> friend std::istream& operator >>(std::istream& in, const Data<Ty>& data);
	};
	template<typename Ty>
	std::ostream& operator<<(std::ostream& out, Data<Ty> data)
	{
		out << data.to_string();
		return out;
	}
	template<typename Ty>
	std::istream& operator>>(std::istream& in,const Data<Ty>& data)
	{
		in >> data.value;
		return in;
	}
	class Integer :public Data<int>
	{
	public:
		Integer(int value=0):Data<int>(value) {}
		Integer(std::string val) :Data<int>(StrParser::parse_int(val)) {}
		Integer& operator =(const Data<int>& other) {
			this->set(other.get());
			return *this;
		}
		Integer& operator =(Data<int>&& other){
			this->set(other.get());
			return *this;
		}
	};
	class UInteger :public Data<uint>
	{
	public:
		UInteger(uint value = 0) :Data<uint>(value) {}
		UInteger(std::string val) :Data<uint>(StrParser::parse_uint(val)) {}
		UInteger& operator =(const Data<uint>& other) {
			this->set(other.get());
			return *this;
		}
		UInteger& operator =(Data<uint>&& other) {
			this->set(other.get());
			return *this;
		}
	};
	class Long :public Data<long>
	{
	public:
		Long(long value = 0) :Data<long>(value) {}
		Long(std::string val) :Data<long>(StrParser::parse_long(val)) {}
		Long& operator =(const Data<long>& other) {
			this->set(other.get());
			return *this;
		}
		Long& operator =(Data<long>&& other) {
			this->set(other.get());
			return *this;
		}
	};
	class ULong :public Data<ulong>
	{
	public:
		ULong(ulong value = 0) :Data<ulong>(value) {}
		ULong(std::string val) :Data<ulong>(StrParser::parse_ulong(val)) {}
		ULong& operator =(const Data<ulong>& other) {
			this->set(other.get());
			return *this;
		}
		ULong& operator =(Data<ulong>&& other) {
			this->set(other.get());
			return *this;
		}
	};
	class LongLong :public Data<long long> {
	public:
		LongLong(long long value = 0) :Data<long long>(value) {}
		LongLong(std::string val) :Data<long long>(StrParser::parse_longlong(val)) {}
		LongLong& operator =(const Data<long long>& other) {
			this->set(other.get());
			return *this;
		}
		LongLong& operator =(Data<long long>&& other) {
			this->set(other.get());
			return *this;
		}
	};
	class ULongLong :public Data<ulonglong> {
	public:
		ULongLong(ulonglong value = 0) :Data<ulonglong>(value) {}
		ULongLong(std::string val) :Data<ulonglong>(StrParser::parse_long(val)) {}
		ULongLong& operator =(const Data<ulonglong>& other) {
			this->set(other.get());
			return *this;
		}
		ULongLong& operator =(Data<ulonglong>&& other) {
			this->set(other.get());
			return *this;
		}
	};
	using Bool = Data<bool>;
	using m_byte = unsigned char;
	template<>
	class Data<bool>
	{
	private:
		bool value;
	public:
		Data<bool>(bool value=false):value(value) {}
	    Data<bool>(const std::string& val) {
			if (val != "true" || val != "false")
				this->value = false;
			else {
				if (val == "true")
					this->value = true;
				else this->value = false;
			}
		}
		explicit Data<bool>(m_byte val) {
			if (val)
				value = true;
			else value = false;
		}
		bool operator !() const{
			return !value;
		}
		Data<bool> operator +(const Data<bool>& other) const{
			return Data<bool>(value || other.value);
		}
		Data<bool> operator *(const Data<bool>& other) const{
			return Data<bool>(value && other.value);
		}
		Data<bool> operator ^(const Data<bool>& other) const{
			bool res = value ^ other.value;
			return Data<bool>(res);
		}
		Data<bool>& operator =(const Data<bool>& other) {
			this->set(other.get());
			return *this;
		}
		Data<bool>& operator =(Data<bool>&& other) {
			this->set(other.get());
			return *this;
		}
		bool get()const {
			return value;
		}
		void set(bool value) {
			this->value = value;
		}
		std::string to_string()const {
			return value ? "true" : "false";
		}
		m_byte integer_value()const {
			return value ? 1 : 0;
		}
	};
	class Float :public Data<float> {
	public:
		Float(float value = 0.0f) :Data<float>(value) {}
		Float(const std::string& val) :Data<float>(StrParser::parse_float(val)) {}
		Float& operator =(const Data<float>& other) {
			this->set(other.get());
			return *this;
		}
		Float& operator =(Data<float>&& other) {
			this->set(other.get());
			return *this;
		}
	};
	class Real :public Data <real> {
	public:
		Real(real value = 0.0) :Data<real>(value) {}
		Real(const std::string& val) :Data<real>(StrParser::parse_real(val)) {}
		Real& operator =(const Data<real>& other) {
			this->set(other.get());
			return *this;
		}
		Real& operator =(Data<real>&& other) {
			this->set(other.get());
			return *this;
		}
	};
	class LongReal :public Data<Lreal> {
	public:
		LongReal(float value = 0.0) :Data<Lreal>(value) {}
		LongReal(const std::string& val) :Data<Lreal>(StrParser::parse_real(val)) {}
		LongReal& operator =(const Data<Lreal>& other) {
			this->set(other.get());
			return *this;
		}
		LongReal& operator =(Data<real>&& other) {
			this->set(other.get());
			return *this;
		}
	};
}
