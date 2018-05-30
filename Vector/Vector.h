#include <iostream>
#include <algorithm>
#include <exception>
#include <limits>
#include <utility>

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
	//MEMBER TYPES
	typedef T           value_type;
	typedef unsigned int size_type;
	typedef ptrdiff_t   difference_type;
	typedef T &         reference;
	typedef const T &   const_reference;
	typedef T *         pointer;
	typedef const T *   const_pointer;
	typedef T *         iterator;
	typedef const T * const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef iterator    InputIt;

	//KONSTRUKTORIAI
	Vector() : sz(0), cp(0), elem(new T[sz]) {} //DEFAULT konstr
	Vector(int s) { sz = s, cp = s, elem = new T[sz]; }
	Vector(int s, double val) : sz(s), cp(s), elem(new T[sz]) { std::fill_n(elem, s, val); }
	Vector(std::initializer_list<T> il) : sz{ static_cast<int>(il.size()) }, elem{ new T[il.size()] } { std::copy(il.begin(), il.end(), elem); } //Initializer-list konstruktorius
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
	T* insert(T* pos, const T& value);
	T* insert(const T* pos, const T& value);
	T* insert(const T* pos, T&& value);
	void insert(T* pos, T first, T last);
	T* erase(T* pos);
	T* erase(const T* pos);
	T* erase(T* first, T* last);
	T* erase(const T* first, const  T* last);
	void assign(unsigned int count, const T& value);
	void assign(T* first, T* last);

	//Element access

	T& at(size_t i)
	{
		if (i < 0 || i >= size())
		{
			throw std::out_of_range;
		}
		return elem[i];
	}
	T* begin() { return &elem[0]; }
	T* end() { return &elem[sz]; }
	T& front() { return elem[0]; }
	T& back() { return elem[sz]; }

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
	T& operator[](unsigned int i) { return elem[i]; }
	const T& operator[](unsigned int i)const { return elem[i]; }
	Vector<T>& operator = (const Vector<T> & v);
	Vector<T>& operator=(Vector&& v);

	/*template< class... Args >
	T* emplace(const T* pos, Args&&... args);*/


};
//----------SWAP---------------------
template<class T>
void Vector<T>::swap(T& x, T& y)
{
	T temp{ x };
	x = y;
	y = temp;
}

//-----------RESIZE-------------------
template <class T>
void Vector<T>::resize(size_t dydis)
{
	if (cp < dydis)
	{
		cp = dydis;
	}
	auto *kazkas = new T[cp];
	for (auto i = 0; i != sz; i++)
	{
		kazkas[i] = elem[i];
	}
	sz = dydis;

	delete elem;
	elem = kazkas;
}

// ----------PUSH_BACK-----------------
template <class T>
void Vector<T>::push_back(const T& x)
{
	if (cp == 0)
	{
		auto kazkas = new T[0];
		sz++;
		cp++;
	}
	if (sz == cp || sz > cp)
	{
		cp = sz * 2;
		auto kazkas = new T[cp];
		for (auto i = 0; i != sz - 1; i++)
		{
			kazkas[i] = elem[i];
		}
		delete elem;
		elem = kazkas;
	}

	elem[sz - 1] = x;
}
template <class T>
void Vector<T>::push_back(T&& x)
{
	if (cp == 0)
	{
		auto kazkas = new T[0];
		sz++;
		cp++;
	}
	if (sz == cp || sz > cp)
	{
		cp = sz * 2;
		auto kazkas = new T[cp];
		for (auto i = 0; i != sz - 1; i++)
		{
			kazkas[i] = elem[i];
		}
		delete elem;
		elem = kazkas;
	}
	
	elem[sz - 1] = x;
}

// ----------POP_BACK-----------------
template <class T>
void Vector<T>::pop_back()
{
	sz--;
	auto *kazkas = new T[cp];
	for (auto i = 0; i != sz; i++)
	{
		kazkas[i] = elem[i];
	}
	delete elem;
	elem = kazkas;
}

// -----------CLEAR-------------------
template <class T>
void Vector<T>::clear()
{
	//Vector<T> kazkas;
	T* kazkas = new T[0];
	delete elem;
	elem = kazkas;
	sz = 0;
	cp = 0;
}

// ----------INSERT-----------
template <class T>
T* Vector<T>::insert(T* pos, const T& value)
{
	size_t x = std::distance(&elem[0], pos);
	if (sz == cp || sz > cp)
	{

		cp = sz * 2;
		++cp;
		++sz;
		auto *kazkas = new T[cp];
		for (auto i = 0; i != x; i++)
		{
			kazkas[i] = elem[i];
		}
		kazkas[x] = value;
		for (auto i = x + 1; i != sz; i++)
		{
			kazkas[i] = elem[i - 1];
		}
		delete elem;
		elem = kazkas;
	}
	else
	{
		++cp;
		++sz;
		auto *kazkas = new T[cp];
		for (auto i = 0; i != x; i++)
		{
			kazkas[i] = elem[i];
		}
		kazkas[x] = value;
		for (auto i = x + 1; i != sz; i++)
		{
			kazkas[i] = elem[i - 1];
		}
		delete elem;
		elem = kazkas;
	}
	return pos;
}
template <class T>
T* Vector<T>::insert(const T* pos, const T& value)
{
	size_t x = std::distance(&elem[0], pos);
	if (sz == cp || sz > cp)
	{
		cp = sz * 2;
		++cp;
		++sz;
		auto *kazkas = new T[cp];
		for (auto i = 0; i != x; i++)
		{
			kazkas[i] = elem[i];
		}
		kazkas[x] = value;
		for (auto i = x + 1; i != sz; i++)
		{
			kazkas[i] = elem[i - 1];
		}
		delete elem;
		elem = kazkas;
	}
	else
	{
		++cp;
		++sz;
		auto *kazkas = new T[cp];
		for (auto i = 0; i != x; i++)
		{
			kazkas[i] = elem[i];
		}
		kazkas[x] = value;
		for (auto i = x + 1; i != sz; i++)
		{
			kazkas[i] = elem[i - 1];
		}
		delete elem;
		elem = kazkas;
	}
	return pos;
}
template <class T>
T* Vector<T>::insert(const T* pos, T&& value)
{
	size_t x = std::distance(&elem[0], pos);
	if (sz == cp || sz > cp)
	{
		cp = sz * 2;
		++cp;
		++sz;
		auto *kazkas = new T[cp];
		for (auto i = 0; i != x; i++)
		{
			kazkas[i] = elem[i];
		}
		kazkas[x] = value;
		for (auto i = x + 1; i != sz; i++)
		{
			kazkas[i] = elem[i - 1];
		}
		delete elem;
		elem = kazkas;
	}
	else
	{
		++cp;
		++sz;
		auto *kazkas = new T[cp];
		for (auto i = 0; i != pos; i++)
		{
			kazkas[i] = elem[i];
		}
		kazkas[x] = value;
		for (auto i = x + 1; i != sz; i++)
		{
			kazkas[i] = elem[i - 1];
		}
		delete elem;
		elem = kazkas;
	}
	return pos;
}
template< class T >
void insert(T* pos, T first, T last)
{
	size_t x = std::distance(&elem[0], pos);
	size_t atstumas = std::distance(first, last);
	if (sz == cp || sz > cp)
	{
		cp = sz * 2;
		++sz;
		auto *kazkas = new T[cp + atstumas];
		for (auto i = 0; i != x; i++)
		{
			kazkas[i] = elem[i];
		}
		for (auto i = x; i != atstumas; i++)
		{
			kazkas[i] = value;
		}

		for (auto i = x + atstumas + 1; i != sz; i++)
		{
			kazkas[i] = elem[i - atstumas - 1];
		}
		delete elem;
		elem = kazkas;
	}
	else
	{
		++cp;
		++sz;
		auto *kazkas = new T[cp];
		for (auto i = 0; i != pos; i++)
		{
			kazkas[i] = elem[i];
		}
		kazkas[x] = value;
		for (auto i = x + 1; i != sz; i++)
		{
			kazkas[i] = elem[i - 1];
		}
		delete elem;
		elem = kazkas;
	}
	return pos;
}

//------------ERASE-------------
template <class T>
T* Vector<T>::erase(T* pos)
{
	size_t x = std::distance(&elem[0], pos);

	--cp;
	--sz;
	auto *kazkas = new T[cp];
	for (auto i = 0; i != x; i++)
	{
		kazkas[i] = elem[i];
	}
	for (auto i = x; i != sz; i++)
	{
		kazkas[i] = elem[i + 1];
	}
	delete elem;
	elem = kazkas;

	return pos;
}
template <class T>
T* Vector<T>::erase(const T* pos)
{
	size_t x = std::distance(&elem[0], pos);

	--cp;
	--sz;
	auto *kazkas = new T[cp];
	for (auto i = 0; i != x; i++)
	{
		kazkas[i] = elem[i];
	}
	for (auto i = x; i != sz; i++)
	{
		kazkas[i] = elem[i + 1];
	}
	delete elem;
	elem = kazkas;

	return pos;
}
template <class T>
T* Vector<T>::erase(T* first, T* last)
{
	size_t x = std::distance(&elem[0], first);
	size_t kiek = std::distance(first, last) + 1;

	sz = sz - kiek;
	cp = cp - kiek;

	auto *kazkas = new T[cp];
	for (auto i = 0; i != x; i++)
	{
		kazkas[i] = elem[i];
	}
	for (auto i = x; i != sz; i++)
	{
		kazkas[i] = elem[i + kiek];
	}
	delete elem;
	elem = kazkas;

	return first;
}
template <class T>
T* Vector<T>::erase(const T* first, const  T* last)
{
	size_t x = std::distance(&elem[0], first);
	size_t kiek = std::distance(first, last) + 1;

	sz = sz - kiek;
	cp = cp - kiek;

	auto *kazkas = new T[cp];
	for (auto i = 0; i != x; i++)
	{
		kazkas[i] = elem[i];
	}
	for (auto i = x; i != sz; i++)
	{
		kazkas[i] = elem[i + kiek];
	}
	delete elem;
	elem = kazkas;

	return first;
}

//-------------RESERVE------------
template <class T>
void Vector<T>::reserve(size_t dydis)
{
	if (dydis>cp)
	{
		cp = dydis;
		auto *kazkas = new T[cp];
		for (auto i = 0; i != sz; i++)
		{
			kazkas[i] = elem[i];
		}
		delete elem;
		elem = kazkas;

	}
}
//-------------SHRINK_TO_FIT--------
template <class T>
void Vector<T>::shrink_to_fit() {
	elem = (T*)realloc(elem, sz * sizeof(T));
	cp = sz;
}
//-------------ASSIGN-------------
template <class T>
void Vector<T>::assign(unsigned int count, const T& value)
{
	if (count > cp)
	{
		cp = count;
	}
	sz = count;
	auto *kazkas = new T[cp];

	for (auto i = 0; i != count; i++)
	{
		kazkas[i] = value;
	}
	delete elem;
	elem = kazkas;
}
template <class T>
void Vector<T>::assign(T* first, T* last)
{

	unsigned int count = last - first + 1;
	auto x = first;
	if (cp < count)
	{
		cp = count;
	}
	sz = count;
	auto *kazkas = new T[cp];

	for (unsigned int i = 0; i < count; ++i)
	{
		kazkas[i] = *x;
		x++;
	}
	delete elem;
	elem = kazkas;
}
//-------------OEPRATOR = -----------------
template<class T>
Vector<T>& Vector<T>::operator = (const Vector<T> & v)
{
	auto *kazkas = new T[v.cp];
	for (int i = 0; i != v.sz; i++)
	{
		kazkas[i] = v.elem[i];
	}
	delete elem;
	elem = kazkas;
	sz = v.sz;
	return *this;
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector&& v)
{
	auto *kazkas = new T[v.cp];
	for (int i = 0; i != v.sz; i++)
	{
		kazkas[i] = std::move(v.elem[i]);
	}
	delete elem;
	elem = kazkas;
	sz = v.sz;

	return *this;
}

//------------CIA TUREJO BUT EMPLACE------------
/*template<class T>
template< class... Args >
T* Vector<T>::emplace(const T* pos, Args&&... args)
{
std::allocator<T> alloc;
T* a;
size_t x = std::distance(&elem[0], pos);
if (sz == cp || sz > cp)
{
cp = sz * 2;
++cp;
++sz;
auto *kazkas = new T[cp];
for (auto i = 0; i != x; i++)
{
kazkas[i] = elem[i];
}
kazkas[x] = args;
for (auto i = x + 1; i != sz; i++)
{
kazkas[i] = elem[i - 1];
}
delete elem;
elem = kazkas;
}
else
{
++cp;
++sz;
auto *kazkas = new T[cp];
for (auto i = 0; i != pos; i++)
{
kazkas[i] = elem[i];
}
alloc.construct(pos, args);
for (auto i = x + 1; i != sz; i++)
{
kazkas[i] = elem[i - 1];
}
delete elem;
elem = kazkas;
}
return a;
}*/


#endif
