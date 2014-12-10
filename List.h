#ifndef _BRIZAN_LIST_H_
#define _BRIZAN_LIST_H_


/*
* List
* Abstract Base Class for a List class.
*/
template <class T>
class List {

public:
	// Public interface. 
	// Each of these must be implemented in derived classes.
	virtual      ~List();   // Must have a virtual destructor

	// Returns true if List has no items
	virtual bool isEmpty() = 0;

	// Returns the number of items on the List
	virtual int  getLength() = 0;

	// Inserts item to position (pos) on the list
	// position is 1-based (NOT like array)
	// May throw an error
	virtual void insert(int pos, T item) = 0;

	// Removes and returns item from position (pos) on list
	// position is 1-based (NOT like array)
	// May throw an error
	virtual void    remove(int pos) = 0;

	// Returns (returns but leaves on list) item at pos
	// position is 1-based (NOT like array)
	// May throw an error
	virtual T    retrieve(int pos) = 0;

};


// Destructor must be defined, even in the Abstract Base Class
template <class T>
List<T>::~List() {
}

#endif
