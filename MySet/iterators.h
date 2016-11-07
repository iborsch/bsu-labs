#ifndef iteratorsH
#define iteratorsH

#include "stdafx.h"
#include "element.h"
#include <stack>
#include <string>
#include <iostream>

using namespace std;
template <typename T>
class ISet;

template <typename T>
class ISetIterator
{
	public:
		ISetIterator() : curr(NULL), list() {};
		ISetIterator(ISetIterator<T> const &it)
		{
			list = it.list;
			curr = it.curr;
		};
		ISetIterator(IElement<T> *el) : list()
		{
			curr = el;
		};
		~ISetIterator() { };
		ISetIterator<T> operator = (ISetIterator<T> const &it);
		bool operator == (ISetIterator<T> const &it) const; 
		bool operator == (IElement<T> const *el) const; 
		bool operator != (ISetIterator<T> const &it) const { return !(*this == it); };
		bool operator != (IElement<T> const *el) const { return !(*this == el); };
		friend bool operator == (IElement<T> const *el, ISetIterator<T> const &it) { return it == el; };
		friend bool operator != (IElement<T> const *el, ISetIterator<T> const &it) { return it != el; };
		IElement<T>* operator ->() { return curr; };
		IElement<T>* operator *() { return curr; };
		ISetIterator<T> next();
		ISetIterator<T> operator ++ ();
		ISetIterator<T> operator ++ (int);
		class ErrorIterator
		{
		public:
			string message;
			ErrorIterator(string amessage) : message(amessage) {};
		};
		//template <typename C>
		//friend istream &operator >> (istream &, ISetIterator <C> &);
	private:
		stack<IElement<T>*> list;
		IElement<T> *curr;

		ISetIterator <T> operator = (IElement<T> *el)
		{
			curr = el;
			while (!list.empty())
			{
				list.pop();
			}
			return *this;
		};
		IElement<T>* go_left(IElement<T> *el);
		template <typename T>
		friend class ISet;
};
template <typename T>
bool ISetIterator<T>::operator == (ISetIterator<T> const &it) const
{
	return curr == it.curr;
};
template <typename T>
bool ISetIterator<T>::operator == (IElement<T> const *el) const
{
	return curr == el;
};
template <typename T>
ISetIterator<T> ISetIterator<T>::operator = (ISetIterator<T> const &it)
{
	delete curr;
	list = it.list;
	if (!it.curr) curr = NULL;
	else curr = new IElement<T>(*it.curr);
	return *this;
};
template <typename T>
IElement<T>* ISetIterator<T>::go_left(IElement<T> *el)
{
	if (el == NULL) return NULL;
	while (el->get_left())
	{
		list.push(el);
		el = el->get_left();
	}
	return el;
};
template <typename T>
ISetIterator<T> ISetIterator<T>::next()
{
	if (!curr) throw(ISetIterator<T>::ErrorIterator("This is the last iterator."));
	if (curr->get_right() != NULL)
		curr = go_left(curr->get_right());
	else
		if (list.empty()) curr = NULL;
		else
		{
			curr = list.top();
			list.pop();
		}
	return *this;
};
template <typename T>
ISetIterator<T> ISetIterator<T>::operator ++()
{
	return this->next();
};
template <typename T>
ISetIterator<T> ISetIterator<T>::operator ++ (int)
{
	ISetIterator<T> temp = *this;
	this->next();
	return temp;
};
/*template <typename C>
ostream &ISetIterator<C>::operator << (ostream &os, const ISetIterator <C> &it)
{
	try
	{
		if (!it.curr) throw(ISet<C>::EmptySet("Error. Uncorrect iterator.");
	}
	catch (ISet<C>::EmptySet err)
	{
		os << err.message;
		system("pause");
		exit(1);
	}
	cout << it->get_value();
};*/
#endif