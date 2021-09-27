/*********************************************************************
* Assignment: Lab 14 - Doubly Linked List implementation            *
* Author: Martin Plut                                                *
* Date: Fall 2017                                                    *
* File: Lab 14 header++ file                                       *
*                                                                    *
* Description: This file contains the class descitption and function *
* implementations for our linked list                                *
*********************************************************************/

#ifndef ORDEREDSET_HPP
#define ORDEREDSET_HPP
#include <iostream>
#include <cstdlib>
#include <sstream>
using namespace std;

enum dtype { FORWARD, BACKWARD };
template <class ST> class OrderedSet;
template <class ST> ostream & operator << (ostream & outs, const OrderedSet<ST> & L);

template <class ST>
class OrderedSet
{


   public:
      class Iterator {
        	public:
        		Iterator();
        		Iterator (LNode * NP);
        		const ST operator * () const;
        		Iterator operator ++ ();
        		Iterator operator ++ (int);
        		Iterator operator -- ();
        		Iterator operator -- (int);
        		bool operator == (const Iterator & other) const;
        		bool operator != (const Iterator & other) const;
        	private:
        		LNode * current;
    	};

      class Exception {
        	public:
        		Exception ();
        		Exception (string msg);
        		Exception (int idx);
        		string Message () const;
        	private:
        		string message;
    	};

      OrderedSet ();
      OrderedSet (const OrderedSet & other);
      ~OrderedSet ();
      OrderedSet & operator = (const OrderedSet & other);
      bool operator == (const OrderedSet & other);
      int Size () const;
      void SetDirection (dtype dir);
      dtype GetDirection () const;
      void PrintList (ostream & outs, int whichLines);
      friend ostream & operator << <> (ostream & outs, const OrderedSet<ST> & L);
      void Forward (void function (const ST & param));
      void Backward (void funciton (const ST & param));
      Iterator begin() const;
      Iterator rbegin() const;
      Iterator end() const;
      Iterator rend() const;
      ST & operator [] (const int & index) const;
      void Clear();
      bool IsEmpty() const;
      bool IsIn(const ST & value) const;
      bool Insert(const ST & value);
      bool Delete(const ST & value);
      OrderedSet operator + (const OrderedSet & other);
      OrderedSet operator * (const OrderedSet & other);
    private:
       struct LNode
       {
          LNode ();
          ST data;
          LNode * next;
          LNode * prev;
       };

      LNode * first;
      LNode * last;
      int size;
      dtype direction;
      bool InsertFirst(const ST & value);
      bool InsertLast(const ST & value);
      bool DeleteFirst();
      bool DeleteLast();
};
template <class ST>
OrderedSet<ST>::Exception::Exception()
{
    message = "<default message>";
}
template <class ST>
OrderedSet<ST>::Exception::Exception(string msg)
{
	message = msg;
}
template <class ST>
OrderedSet<ST>::Exception::Exception(int idx)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << "Subscript [" << idx << "] out of range";
	getline(ss, message);
}
template <class ST>
string OrderedSet<ST>::Exception::Message() const
{
	return message;
}

template <class ST>
void OrderedSet<ST>::Clear()
{
	LNode * del = first;
	while (del != NULL)
	{
		first = first->next;
		delete del;
		del = first;
	}
}
template <class ST>
bool OrderedSet<ST>::IsEmpty() const
{
	return size == 0;
}

template <class ST>
bool OrderedSet<ST>::IsIn(const ST & value) const
{
	for (LNode * n = first; n!=NULL; n=n->next)
	{
		if(n->data == value)
			return true;
	}
}

template <class ST>
bool OrderedSet<ST>::Insert(const ST & value)
{
	if(IsEmpty())
		return InsertFirst(value);
	if(value > last->data)
		return InsertLast(value);
	if(value < first->data)
		return InsertFirst(value);
	if(IsIn(value))
		return false;
	LNode * nn = new LNode;
	if (nn == NULL)
		return false;
	nn->data=value;
	LNode * nx = first;
	while (nx->data<value)
	{
		nx = nx->next;
	}
	LNode * pv = nx->prev;
	nn->prev = pv;
	nx->prev = nn;
	pv->next = nn;
	nn->next = nx;
	size++;
	return true;
}

template <class ST>
bool OrderedSet<ST>::Delete (const ST & value)
{
	if (size == 1)
		return DeleteFirst();
	else if (value == last->data)
		return DeleteLast();
	else if (value == first->data)
		return DeleteFirst();
	else if (!IsIn(value))
		return false;
	else
	{
		for (LNode * n = first; n != NULL; n = n->next)
		{
			if (n->data == value)
			{
				LNode * nx = n->next;
				LNode * pv = n->prev;
				pv->next = nx;
				nx->prev = pv;
				delete n;
				size--;
				return true;
			}
		}

	}
	return false;
}
template <class ST>
OrderedSet<ST> OrderedSet<ST>::operator + (const OrderedSet & other)
{
	OrderedSet <int> thiscopy;
	OrderedSet <int> S2;
	OrderedSet <int> Union;
	Union = *this;
	thiscopy = *this;
	for (int i = 0; i < other.Size(); i++)
		S2.Insert(other[i]);
	if (size >= other.Size())
	{
		for (int i = 0; i < other.Size(); i++)
			Union.Insert(other[i]);
		return Union;
	}
	else
	{
		for (int i = 0; i < size; i++)
			S2.Insert(thiscopy[i]);
		return S2;
	}
}

template <class ST>
OrderedSet<ST> OrderedSet<ST>::operator * (const OrderedSet & other)
{
	OrderedSet<int>Intersection;
	OrderedSet<int>thiscopy;
	OrderedSet<int>Intersection2;
	thiscopy = *this;
	for (int i = 0; i < other.Size(); i++)
		Intersection2.Insert(other[i]);
	if (size >= other.Size())
	{
		for (int i = 0; i < other.Size(); i++)
		{
			if (Intersection.IsIn(other[i]))
				thiscopy.Insert(other[i]);
		}
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (Intersection2.IsIn(thiscopy[i]));
				Intersection.Insert(thiscopy[i]);
		}
	}
	return Intersection;
}

template <class ST>
ST & OrderedSet<ST>::operator [] (const int & index) const
{
	if (index < 0)
		throw (Exception (index));
	if (index >= size)
		throw(Exception (index));
	typename OrderedSet<ST>::LNode * n = first;
	for (int i = 0; i < index; i++)
		n = n->next;
	return n->data;
}

template <class ST>
OrderedSet<ST>::LNode::LNode ()
{ // This function will set the value of data to 0 and the value of next to NULL.
  // This is the default constructor for the LNode struct
	data = 0;
	next = NULL;
	prev= NULL;
}

template <class ST>
OrderedSet<ST>::OrderedSet ()
{ // This function will set the value of size to 0 and the value of first to NULL
  // THis is the default constructor for the OrderedSet Class
	size = 0;
	first = NULL;
	last = NULL;
	direction = FORWARD;
}
template <class ST>
void OrderedSet<ST>::Forward(void function (const ST & param))
{
	for (LNode * n = first; n; n = n->next)
		function(n->data);
}
template <class ST>
void OrderedSet<ST>::Backward(void function (const ST & param))
{
	for (LNode * n = last; n; n = n->prev)
		function (n->data);
}

template <class ST>
OrderedSet<ST>::OrderedSet (const OrderedSet & other)
{ // This function will copy the contents of one linked list to another
	size = 0;
	first = NULL;
	for (LNode * n = other.first; n != NULL; n = n->next)
		InsertLast(n->data);
	direction = other.direction;
}

template <class ST>
OrderedSet<ST>::~OrderedSet ()
{ // This function will delete all of the elements in a list
	while(first)
		DeleteFirst();
}
template <class ST>
OrderedSet<ST> & OrderedSet<ST>::operator = (const OrderedSet<ST> & other)
{ // This function will make a copy of a list
	if (this == &other)
		return * this;
	while(first)
		DeleteFirst();
	for (LNode * n = other.first; n != NULL; n = n->next)
		InsertLast (n->data);
	direction = other.direction;
	return * this;
}

template <class ST>
bool OrderedSet<ST>::operator == (const OrderedSet & other)
{ // This function will compare two lists checking if its elements are the same
	if (size != other.size)
		return false;
	LNode * n = first;
	LNode * m = other.first;
	while (n != NULL)
	{
		if (n->data != m->data)
			return false;
		n = n->next;
		m = m->next;
	}
	return true;
}

template <class ST>
int OrderedSet<ST>::Size () const
{ // This function will return the value of Size
	return size;
}
template <class ST>
void OrderedSet<ST>::SetDirection (dtype dir)
{
	direction = dir;
}

template <class ST>
dtype OrderedSet<ST>::GetDirection () const
{
	return direction;
}
template <class ST>
ostream & operator << (ostream & outs, const OrderedSet<ST> & L)
{ // This function will traverse the list outputting data values
	if (L.first == NULL)
		return outs;
	if (L.direction == FORWARD)
	{ // print the list from the beginning (first) to the end
		outs << "{" <<  L.first->data;
		typename OrderedSet<ST>::LNode * n;
		for (n = L.first->next; n != NULL; n = n->next)
			outs << ',' << n->data;
		outs << "}";
	}
	else //L.direction == BACKWARD
	{ // print the list from the end to the beginning
	//	L.first->PrintNode(outs, 2);
		outs << "{" << L.last->data;
		typename OrderedSet<ST>::LNode * n;
		for (n = L.last->prev; n != NULL; n = n->prev)
			outs << ',' << n->data;
		outs <<"}";
	}
	return outs;
}

template <class ST>
void OrderedSet<ST>::PrintList (ostream & outs, int whichLines)
{
	if (first != NULL)
		first->PrintNode (outs, whichLines);
}
template <class ST>
bool OrderedSet<ST>::InsertFirst (const ST & value)
{ // This function will insert a value to the first position in our linked list
	LNode * nn = new LNode; // Allocation of space for new node
	if (nn ==NULL) // check if space cannot be allocated and return false if so
		return false;
	nn->data = value; // set data of the new node to the input value
	nn->next = first; // set the next of the list to the new node
	nn->prev = NULL;
	if (first != NULL)
		first->prev = nn;
	first = nn; // set first of new list to the new node
	if (size == 0)
		last = nn;
	size++; // increment size of the list
	return true;
}

template <class ST>
bool OrderedSet<ST>::InsertLast (const ST & value)
{ // This function will insert a value at the end of the list
	if (size == 0)
		return InsertFirst(value);
	LNode * nn = new LNode;
	if (nn == NULL)
		return false;
	nn->data = value;
	nn->prev = last;
	nn->next = NULL;
	last->next=nn;
	last = nn;
	size++;
	return true;
}

template <class ST>
bool OrderedSet<ST>::DeleteFirst ()
{ // This function will delete the first value in the linked list
	if (first==NULL)
		return false;
	LNode*np=first;
	first=first->next;
	if (size == 1)
	{
		first = NULL;
		last = NULL;
	}
	else
		np->next->prev = NULL;

	free(np);
	size--;
	return true;
}

template <class ST>
bool OrderedSet<ST>::DeleteLast ()
{ // This function will delete the last element in the list
	if (size == 0)
		return false;
	if (size == 1)
		return DeleteFirst();
	LNode * p = last->prev;
	p->next = NULL;
	delete last;
	last = p;
	size--;
	return true;
}

template <class ST>
OrderedSet<ST>::Iterator::Iterator()
{
	current = NULL;
}

template <class ST>
OrderedSet<ST>::Iterator::Iterator(LNode * NP)
{
	current = NP;
}

template <class ST>
const ST OrderedSet<ST>::Iterator::operator * () const
{
	if (current == NULL)
		throw(Exception("Cannot dereference a NULL pointer"));
	return current->data;
}
template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator ++()
{
	if (current == NULL)
		throw (Exception("Cannot post-increment a NULL iterator"));
	current = current->next;
	return * this;
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator ++(int)
{
 	if (current == NULL)
		throw(Exception("Cannot increment a NULL iterator"));
	Iterator temp = *this;
	current = current->next;
	return temp;
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator --()
{
	if (current == NULL)
		throw(Exception("Cannont post-decrement a NULL pointer"));
	current = current->prev;
	return *this;
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator --(int)
{
	if (current == NULL)
		throw(Exception("Cannot decrement a NULL iterator"));
	Iterator temp = *this;
	current = current->prev;
	return temp;
}

template <class ST>
bool OrderedSet<ST>::Iterator::operator == (const Iterator & other) const
{
	return current == other.current;
}

template <class ST>
bool OrderedSet<ST>::Iterator::operator != (const Iterator & other) const
{
	return current != other.current;
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::begin() const
{
	Iterator temp(first);
	return temp;
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::rbegin() const
{
	Iterator temp(last);
	return temp;
}
template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::end() const
{
	Iterator temp;
	return temp;
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::rend() const
{
	Iterator temp;
	return temp;
}
#endif
