#include "Vector.h"

//Funkcijos

template<class T>
void Vector<T>::swap(T& x, T& y)
{
	T temp{ x };
	x = y;
	y = temp;
}

template <class T>
void Vector<T>::resize(size_t dydis)
{
	elem = (T*)realloc(elem, dydis * sizeof(T));
	cp = dydis;
}

// ----------PUSH_BACK-----------------
template <class T>
void Vector<T>::push_back(const T& x)
{
	sz++;
	if (sz == cp)
	{
		cp *= 2;
	}
	auto *kazkas = new T[cp];
	for (auto i = 0; i != sz - 1; i++)
	{
		kazkas[i] = elem[i];
	}
	delete elem[];
	elem = kazkas;
	elem[sz] = x;	
}
template <class T>
void Vector<T>::push_back(T&& x)
{
	sz++;
	if (sz == cp)
	{
		cp *= 2;
	}
	auto *kazkas = new T[cp];
	for (auto i = 0; i != sz - 1; i++)
	{
		kazkas[i] = elem[i];
	}
	delete elem[];
	elem = kazkas;
	elem[sz] = x;
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
	delete elem[];
	elem = kazkas;
}

template <class T>
void Vector<T>::clear()
{
	auto kazkas = Vector[0];
	delete [] elem;
	elem = kazkas;
	sz = 0; 
	cp = 0;
}

// ----------INSERT-----------
template <class T>
T* Vector<T>::insert(T* pos, const T& value)
{
	if (sz == cp)
	{
		cp *= 2;
		++cp;
		elem = (T*)realloc(elem, cp * sizeof(T));
		++sz;
		std::iterator it
			for (size_t i = sz; i != pos; --i)
			{
				elem[i + 1] = elem[i];
			}
	}
	else
	{
		++sz;
		++cp;
		elem[sz - 1] = item;
		elem = (T*)realloc(elem, cp * sizeof(T));
		std::iterator it
			for (size_t i = sz; i != pos; --i)
			{
				elem[i + 1] = elem[i];
			}
	}
}
template <class T>
T* Vector<T>::insert(const T* pos, const T& value)
{
	if (sz == cp)
	{
		cp *= 2;
		++cp;
		elem = (T*)realloc(elem, cp * sizeof(T));
		++sz;
		std::iterator it
			for (size_t i = sz; i != pos; --i)
			{
				elem[i + 1] = elem[i];
			}
	}
	else
	{
		++sz;
		++cp;
		elem[sz - 1] = item;
		elem = (T*)realloc(elem, cp * sizeof(T));
		std::iterator it
			for (size_t i = sz; i != pos; --i)
			{
				elem[i + 1] = elem[i];
			}
	}
}
template <class T>
T* Vector<T>::insert(const T* pos, T&& value)
{
	if (sz == cp)
	{
		cp *= 2;
		++cp;
		elem = (T*)realloc(elem, cp * sizeof(T));
		++sz;
		std::iterator it
			for (size_t i = sz; i != pos; --i)
			{
				elem[i + 1] = elem[i];
			}
	}
	else
	{
		++sz;
		++cp;
		elem[sz - 1] = item;
		elem = (T*)realloc(elem, cp * sizeof(T));
		std::iterator it
			for (size_t i = sz; i != pos; --i)
			{
				elem[i + 1] = elem[i];
			}
	}
}

template <class T>
void Vector<T>::reserve(size_t dydis)
{
	if (dydis > cp)
	{
		elem = (T*)realloc(elem, dydis * sizeof(T));
		cp = dydis;
	}
}

template <class T>
void Vector<T>::shrink_to_fit() {
	elem = (T*)realloc(elem, sz * sizeof(T));
	cp = sz;
}

