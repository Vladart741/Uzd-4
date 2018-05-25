#include <iostream>
#include <algorithm>
#include <exception>
#include <limits>

#ifndef VECTOR_H
#define VECTOR_H

template <class T>
class Vector 
{
private:
	size_t sz;
	size_t cp;
	T *elem;
public:
	//KONSTRUKTORIAI
	Vector() : sz(0), cp(0), elem(new T[sz]) {} //DEFAULT konstr
	Vector(int s) { sz = s, cp = s, elem = new T[sz]; }
	Vector(int s, double val) : sz(s),cp(s), elem(new T[sz]) { std::fill_n(elem, s, val); }
//	Vector(std::initializer_list<T> il) : sz{ static_cast<int>(il.size()) }, elem{ new T[il.size()] } { std::copy(il.begin(), il.end(), elem); } //Initializer-list konstruktorius
     //copy konstruktorius
	Vector(const Vector& v) : sz{ v.sz }, cp{ v.cp }, elem{ new T[v.sz] }
	{
		for (auto i = 0; i != sz; ++i)
		{
			elem[i] = v.elem[i];
		}
	}  
	//move konstruktorius
	Vector(Vector&& v) : sz{ v.sz }, cp{ v.cp }, elem{ v.elem }
	{
		v.elem = nullptr;
		v.sz = 0;
		v.cp = 0;
	}


	//DESTRUKTOR
	~Vector() { delete[] elem; }

	//Funkcijos
	
	void push_back(const T& x);
	void push_back(T&& x);
	void swap(T& x, T& y);
	void resize(size_t dydis);
	void pop_back();
	void clear();
	void reserve(size_t dydis);
	void shrink_to_fit();
	T* insert(T* pos,const T& value);
	T* insert(const T* pos, const T& value);
	T* insert(const T* pos, T&& value);

	//Element access

	T at(size_t i)
	{
		if (i<0 || i >= size())
		{
			throw std::out_of_range;
		}
		return elem[i];
	}
	T front() { return elem[0]; }
	T back() { return elem[size() - 1]; }

	// Capacity
	bool empty()
	{
		if (sz == 0)
			return true;
		else
			false;
	}
	T size() { return sz; }
	T max_size() { return std::numeric_limits<size_t>::max(); }
	T capacity() { return cp; }
	

	//Operatoriai
	template <typename T>
	const T& operator[](int i)
	{
		if (i < 0 || i >= size())
		{
			throw std::out_of_range{ "Vector::operator[]" };
		}
		return elem[i];
	}
	Vector& operator[](int i)
	{
		if (i < 0 || i >= size())
		{
			throw std::out_of_range{ "Vector::operator[]" };
		}
		return elem[i];
	}
	Vector& operator=(const T& v)
	{
		if (&v = this)
		{
			return *this;
		}
		T* p = new T[v.size()];
		for (auto i = 0; i != v.size(); ++i)
		{
			p[i] = v.elem[i];
		}
		delete[] elem;
		elem = p;
		sz = v.sz;
		return *this;
	}

	
};

#endif