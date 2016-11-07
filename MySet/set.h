#ifndef setH
#define setH

#include "iterators.h"
#include "element.h"
#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

template <typename T>
class ISet;
template <typename T>
class IHelp;
template <typename T>
class ISetIterators;

template <typename T>
ostream &operator << (ostream &, const ISet <T> &);
template <typename T>
istream &operator >> (istream &, ISet <T> &);

template <typename T>
class ISet
{
public:
	typedef ISetIterator<T> iterator;
private:
	IElement <T> *root;
	iterator beg;
	int card;

	void remove(IElement <T> *, IElement <T> **);
	void remove_less_two(IElement <T> *, IElement <T> **);
	void remove_two(IElement <T> *, IElement <T> **);
	bool find(const T, IElement <T>*&, IElement <T>**&, bool b = false);
	void clear(IElement <T> *&);
	IElement <T>* copyhelper(IElement <T> *, ISetIterator<T>);

	//IElement<T>* find_new_begin();
	class EmptySet
	{
	public:
		string message;
		EmptySet(string amessage) : message(amessage) {};
	};


public:
	ISet(IElement <T> *aroot = NULL) : root(aroot), card(0), beg(aroot) {};
	ISet(const ISet <T> &T);
	~ISet() { clear(root); };
	void add(const T);
	bool remove(const T);
	IElement<T>* find(const T) const;

	iterator begin() { return beg; };
	iterator const cbegin() { return beg; };
	iterator end() { return NULL; };
	iterator const cend() { return NULL; };

	int size() const { return card; };
	bool empty() const { return root ? false : true; };
	void clear() { clear(root); };
	void swap(ISet <T> &);

	ISet<T> &operator = (const ISet <T> &);
	ISet<T> operator + (const ISet <T> &) const;
	ISet<T> &operator += (const ISet <T> &);
	ISet<T> operator * (const ISet <T> &) const;
	ISet<T> &operator *= (const ISet <T> &);
	ISet<T> operator / (const ISet <T> &) const;
	ISet<T> &operator /= (const ISet <T> &);
	ISet<T> operator - (const ISet <T> &) const;
	ISet<T> &operator -= (const ISet <T> &);

	bool operator == (const ISet <T> &) const;
	bool operator != (const ISet <T> &) const;
	bool operator < (const ISet <T> &) const;
	bool operator <= (const ISet <T> &) const;
	bool operator > (const ISet <T> &) const;
	bool operator >= (const ISet <T> &) const;

	IHelp<T> operator [] (const ISet <T> &);
	IHelp<T> operator [] (const IElement <T> &);
	IHelp<T> operator [] (const T &);
	friend ostream &operator << <> (ostream &, const ISet <T> &);
	friend istream &operator >> <> (istream &, ISet <T> &);
};


template <typename T>
void ISet<T>::add(const T a)
{
	IElement <T> *p = root;
	IElement <T> **pp = &root;
	bool b = false;
	if (!root) b = true;
	while (p)
	{
		if (a == p->value)
			return;
		if (a > p->value)
		{
			pp = &(p->right);
			p = p->right;
		}
		else
		{
			if (beg == p) b = true;
			pp = &(p->left);
			p = p->left;
		}
	}
	*pp = new IElement<T>(a);
	if (b) beg = *pp;
	++card;
};
template <typename T>
IElement<T>* ISet<T>::find(const T a) const
{
	IElement <T> *ret = NULL;
	IElement <T> *p = root;
	while (p)
	{
		if (a > p->value) p = p->right;
		else
		{
			if (a < p->value) p = p->left;
			else
			{
				if (a == p->value)
				{
					ret = p;
					break;
				}
			}
		}
	}
	return ret;
};
template <typename T>
bool ISet<T>::find(const T a, IElement <T> *&p, IElement <T> **&pp, bool b)
{
	p = root;
	pp = &root;
	if (p && b && p->value == a && beg == p)	beg = p->get_right();
	while (p)
	{
		if (a == p->value)
			return true;
		if (a > p->value)
		{
			pp = &(p->right);
			p = p->right;
		}
		else
		{
			if (b && p->left == beg && p->left->value == a) beg = p;
			pp = &(p->left);
			p = p->left;
		}
	}
	return false;
};
template <typename T>
void ISet<T>::remove_less_two(IElement <T> *p, IElement <T> **pp)
{
	if (p->left) *pp = p->left;
	else *pp = p->right;
	delete p;
	--card;
};
template <typename T>
void ISet<T>::remove_two(IElement <T> *p, IElement <T> **pp)
{
	IElement <T> *ptr = p;
	IElement <T> **pptr = pp;
	pptr = &(ptr->left);
	ptr = ptr->left;
	while (ptr->right)
	{
		pptr = &(ptr->right);
		ptr = ptr->right;
	}
	p->value = ptr->value;
	remove_less_two(ptr, pptr);
};
template <typename T>
void ISet<T>::remove(IElement <T> *p, IElement <T> **pp)
{
	if (p->left && p->right) remove_two(p, pp);
	else remove_less_two(p, pp);
};
template <typename T>
bool ISet<T>::remove(const T a)
{
	IElement <T> *p, **pp;
	bool ret = find(a, p, pp, true);
	if (ret) remove(p, pp);
	return ret;
};
template <typename T>
void ISet<T>::clear(IElement <T> *&p)
{
	if (!p) return;
	clear(p->left);
	clear(p->right);
	delete p;
	p = NULL;
	--card;
}

template <typename T>
void ISet <T>::swap(ISet <T> &set)
{
	if (root != set.root)
	{
		ISet temp(set);
		set = *this;
		*this = temp;
	}
};
template <typename T>
ISet<T>::ISet(const ISet <T> &set)
{
	if (root == set.root) return;
	root = copyhelper(set.root, set.beg);
	card = set.card;
};
template <typename T>
IElement<T> *ISet<T>::copyhelper(IElement <T> *p, ISetIterator<T> it)
{
	if (!p) return NULL;
	IElement <T> *l = copyhelper(p->left, it);
	IElement <T> *r = copyhelper(p->right, it);
	IElement<T>* temp = new IElement<T>(p->value, l, r);
	if (p == it) beg = temp;
	return temp;
};
template <typename T>
ISet <T> &ISet<T>::operator = (const ISet <T>&set)
{
	if (this->root != set.root)
	{
		clear();
		root = copyhelper(set.root, set.beg);
		card = set.card;
	}
	return *this;
};
template <typename T>
ISet <T> ISet<T>::operator + (const ISet <T> &set) const
{
	ISet <T> temp(*this);
	if (set.root)
	{
		stack <IElement <T> *> r;
		IElement <T> *q = set.root;
		IElement <T> *prev = NULL;
		while (1)
		{
			while (q)
			{
				r.push(q);
				q = q->get_left();
			}
			if (r.empty()) break;
			q = r.top();
			r.pop();
			temp.add(q->value);
			q = q->get_right();
		}
	}
	return temp;
};

template <typename T>
ISet <T> &ISet<T>::operator += (const ISet <T>&set)
{
	return *this = *this + set;
};
template <typename T>
ISet <T> ISet<T>::operator * (const ISet <T>&set) const
{
	ISet <T> temp;
	if (root)
	{
		stack <IElement <T> *>  r;
		IElement <T> *q = root;
		IElement <T> *prev = NULL;
		while (1)
		{
			while (q)
			{
				r.push(q);
				q = q->get_left();
			}
			if (r.empty()) break;
			q = r.top();
			r.pop();
			if (set.find(q->value)) temp.add(q->value);
			q = q->get_right();
		}
	}
	return temp;
};
template <typename T>
ISet<T> &ISet<T>::operator *= (const ISet <T> &set)
{
	return (*this) = (*this) * set;
};
template <typename T>
ISet<T> ISet<T>::operator / (const ISet <T> &set) const
{
	ISet temp;
	if (root)
	{
		stack <IElement<T>*> r;
		IElement <T> *q = root;
		IElement <T> *prev = NULL;
		while (1)
		{
			while (q)
			{
				r.push(q);
				q = q->get_left();
			}
			if (r.empty()) break;
			q = r.top();
			r.pop();
			if (!set.find(q->value)) temp.add(q->value);
			q = q->get_right();
		}
	}
	return temp;
};
template <typename T>
ISet<T> &ISet<T>::operator /= (const ISet<T> &set)
{
	return *this = *this - set;
};
template <typename T>
ISet<T> ISet<T>::operator - (const ISet <T> &set) const
{
	return ((*this) / set) + (set / (*this));
};
template <typename T>
ISet<T> &ISet<T>::operator -= (const ISet <T> &set)
{
	return *this = ((*this) / set) + (set / (*this));
};
template <typename T>
bool ISet<T>::operator == (const ISet<T> &set) const
{
	int count = 0;
	if (root != set.root)
	{
		stack <IElement<T>*> r;
		IElement<T> *q = root;
		IElement<T>*prev = NULL;
		while (1)
		{
			while (q)
			{
				r.push(q);
				q = q->get_left();
			}
			if (r.empty()) break;
			q = r.top();
			r.pop();
			if (set.find(q->value)) ++count;
			else return false;
			q = q->get_right();
		}
	}
	if (count != set.card) return false;
	else return true;
};
template <typename T>
bool ISet<T>::operator != (const ISet <T> &set) const
{
	return !(*this == set);
};
template <typename T>
bool ISet<T>::operator < (const ISet <T> &set) const
{
	int count = 0;
	if (root != set.root)
	{
		stack <IElement<T>*> r;
		IElement<T> *q = root;
		IElement<T> *prev = NULL;
		while (1)
		{
			while (q)
			{
				r.push(q);
				q = q->get_left();
			}
			if (r.empty()) break;
			q = r.top();
			r.pop();
			if (set.find(q->value)) ++count;
			else return false;
			q = q->get_right();
		}
	}
	if (count == set.card) return false;
	else return true;
};
template <typename T>
bool ISet<T>::operator <= (const ISet <T>&set) const
{
	if (root != set.root)
	{
		stack <IElement<T>*> r;
		IElement<T> *q = root;
		IElement<T> *prev = NULL;
		while (1)
		{
			while (q)
			{
				r.push(q);
				q = q->get_left();
			}
			if (r.empty()) break;
			q = r.top();
			r.pop();
			if (!set.find(q->value)) return false;
			q = q->get_right();
		}
	}
	return true;
};
template <typename T>
bool ISet<T>::operator > (const ISet<T> &set) const
{
	return !(*this <= set);
};
template <typename T>
bool ISet<T>::operator >= (const ISet <T> &set) const
{
	return !(*this < set);
};
template <typename T>
ostream &operator << (ostream &os, const ISet <T> &set)
{
	if (!set.root) return os;
	stack <IElement<T>*> r;
	IElement <T> *q = set.root;
	IElement <T> *prev = NULL;
	while (1)
	{
		while (q)
		{
			r.push(q);
			q = q->get_left();
		}
		if (r.empty()) break;
		q = r.top();
		r.pop();
		os << q->get_value() << " ";
		q = q->get_right();
	}
	return os;
};
template <typename T>
istream &operator >> (istream &is, ISet <T> &set)
{
	T val;
	char ch;
	while (1)
	{
		is.get(ch);
		if (ch == ' ') continue;
		if (ch == 10) break;
		is.putback(ch);
		is >> val;
		set.add(val);
	}
	return is;
}
template <typename T>
IHelp<T> ISet<T>::operator [] (const ISet <T>&s)
{
	IHelp<T> sub(this);
	if (root)
	{
		stack <IElement<T>*> r;
		IElement<T> *q = root;
		IElement<T> *prev = NULL;
		while (1)
		{
			while (q)
			{
				r.push(q);
				q = q->get_left();
			}
			if (r.empty()) break;
			q = r.top();
			r.pop();
			if (s.find(q->value)) sub.subset.push_back(q->value);
			q = q->get_right();
		}
	}
	return sub;
};
template <typename T>
IHelp<T> ISet<T>::operator [] (const IElement <T> &el)
{
	ISet<T> temp;
	temp.add(el.value);
	return this->operator[](temp);
};
template <typename T>
IHelp<T> ISet<T>::operator [] (const T &t)
{
	ISet<T> temp;
	temp.add(t);
	return this->operator[](temp);
};


template <typename T>
class IHelp
{
public:
	ISet<T> operator = (const ISet<T> &);
	ISet<T> operator = (const IElement<T> &);
	ISet<T> operator = (const T &);
	operator ISet<T>();
private:
	ISet <T> *set;
	vector <IElement<T> > subset;
	IHelp(ISet<T> *aset) : set(aset) {};
	template <typename T>
	friend class ISet;
};

template <typename T>
IHelp<T>::operator ISet<T>()
{
	ISet<T> temp;
	for (vector <IElement<T> >::iterator it = subset.begin(); it != subset.end(); ++it)
		temp.add((*it).get_value());
	return temp;
}
template <typename T>
ISet<T> IHelp<T>::operator = (const ISet <T> &s)
{
	for (vector <IElement<T> >::iterator it = subset.begin(); it != subset.end(); ++it)
		set->remove((*it).get_value());
	return *set += s;
};
template <typename T>
ISet<T> IHelp<T>::operator = (const IElement<T> &el)
{
	ISet<T> temp;
	temp.add(el.get_value());
	return this->operator=(temp);
};
template <typename T>
ISet<T> IHelp<T>::operator = (const T &t)
{
	ISet<T> temp;
	temp.add(t);
	return this->operator=(temp);
};

#endif