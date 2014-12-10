#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <string>
using namespace std;

int nextPrime(int n);

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x , v )       --> Insert key x and value v
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hash( string str ) --> Global method to hash strings

class HashTable
{
public:
	explicit HashTable(int size = 101) : array(nextPrime(size))
	{
		makeEmpty();
	}

	bool contains(const int & x) const
	{
		return isActive(findPos(x));
	}

	void makeEmpty()
	{
		currentSize = 0;
		for (int i = 0; i < array.size(); i++)
			array[i].info = EMPTY;
	}

	bool insert(const int & x, int v)
	{
		// Insert x as active
		int currentPos = findPos(x);
		if (isActive(currentPos))
			return false;

		array[currentPos] = HashEntry(x, ACTIVE, v);

		// Rehash; see Section 5.5
		if (++currentSize > array.size() / 2)
			rehash();

		return true;
	}

	bool remove(const int & x){
		int currentPos = findPos(x);
		array[currentPos].info = DELETED;
		return true;
	}

	int returnPositionX(int x){
		return returnValueNum(x);
	}

	int returnKeyValue(const int & x) const
	{
		/*int offset = 1;
		int currentPos = myhash(x);

		// Assuming table is half-empty, and table length is prime,
		// this loop terminates
		while (array[currentPos].info != EMPTY && array[currentPos].element != x)
		{
			currentPos += offset;  // Compute ith probe
			offset += 2;
			if (array[currentPos].element == x)
				return array[currentPos].element;
		}*/
		int position = findPos(x);

		return array[position].element;
	}

	int returnValueNum(const int & x) const
	{
		/*int offset = 1;
		int currentPos = myhash(x);

		// Assuming table is half-empty, and table length is prime,
		// this loop terminates
		while (array[currentPos].info != EMPTY &&
			array[currentPos].element != x)
		{
			currentPos += offset;  // Compute ith probe
			offset += 2;
			if (array[currentPos].element == x)
				return array[currentPos].value;
		}*/
		int position = findPos(x);

		return array[position].value;
	}

	void modify(int ID, int pos){
		int offset = 1;
		int currentPos = myhash(ID);

		// Assuming table is half-empty, and table length is prime,
		// this loop terminates
		while (array[currentPos].info != EMPTY &&
			array[currentPos].element != ID)
		{
			currentPos += offset;  // Compute ith probe
			offset += 2;
			if (array[currentPos].element == ID)
				array[currentPos].value = pos;
		}
	}

	enum EntryType { ACTIVE, EMPTY, DELETED };

private:
	struct HashEntry
	{
		int element; //Soldier ID
		int value; // position in array
		EntryType info;

		HashEntry(const int & e = 0, EntryType i = EMPTY, int v = 0)
			: element(e), info(i), value(v) { }
	};

	vector<HashEntry> array;
	int currentSize;

	bool isActive(int currentPos) const
	{
		return array[currentPos].info == ACTIVE;
	}

	int findPos(const int & x) const
	{
		int offset = 1;
		int currentPos = myhash(x);

		// Assuming table is half-empty, and table length is prime,
		// this loop terminates
		while (array[currentPos].info != EMPTY &&
			array[currentPos].element != x)
		{
			currentPos += offset;  // Compute ith probe
			offset += 2;
			if (currentPos >= array.size())
				currentPos -= array.size();
		}

		return currentPos;
	}

	void rehash()
	{
		vector<HashEntry> oldArray = array;

		// Create new double-sized, empty table
		array.resize(nextPrime(2 * oldArray.size()));
		for (int j = 0; j < array.size(); j++)
			array[j].info = EMPTY;

		// Copy table over
		currentSize = 0;
		for (int i = 0; i < oldArray.size(); i++)
			if (oldArray[i].info == ACTIVE)
				insert(oldArray[i].element, oldArray[i].value);
	}
	int myhash(const int & x) const
	{
		int hashVal = x;

		hashVal %= array.size();
		if (hashVal < 0)
			hashVal += array.size();

		return hashVal;
	}

};

bool isPrime(int n)
{
	if (n == 2 || n == 3)
		return true;

	if (n == 1 || n % 2 == 0)
		return false;

	for (int i = 3; i * i <= n; i += 2)
		if (n % i == 0)
			return false;

	return true;
}

int nextPrime(int n)
{
	if (n <= 0)
		n = 3;

	if (n % 2 == 0)
		n++;

	for (; !isPrime(n); n += 2)
		;

	return n;
}

#endif