#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "dsexceptions.h"
#include "QuadraticProbing.h"
#include "Soldier.h"
#include "LinkedList.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <time.h>
#include <stdlib.h>
using namespace std;

// BinaryHeap class
//
// CONSTRUCTION: with an optional capacity (that defaults to 100)
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( minItem )   --> Remove (and optionally return) smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename HashedObj>
class BinaryHeap
{
public:
	explicit BinaryHeap(int capacity = 100)
		: array(capacity + 1), currentSize(0)
	{
	}

	explicit BinaryHeap(const vector<Soldier> & items)
		: array(items.size() + 10), currentSize(items.size())
	{
		for (int i = 0; i < items.size(); i++)
			array[i + 1] = items[i];
		buildHeap();
	}

	bool isEmpty() const
	{
		return currentSize == 0;
	}

	/**
	* Find the smallest item in the priority queue.
	* Return the smallest item, or throw Underflow if empty.
	*/
	const Soldier & findMin() const
	{
		if (isEmpty())
			throw UnderflowException();
		return array[1];
	}
	/**
	* Insert item x, allowing duplicates.
	*/
	void insert(const Soldier & x)
	{
		if (currentSize == array.size() - 1)
			array.resize(array.size() * 2);

		// Percolate up
		int hole = ++currentSize;
		for (; hole > 1 && x < array[hole / 2]; hole /= 2)
			array[hole] = array[hole / 2];
		array[hole] = x;
		myHT.insert(x.returnID(), hole);
	}

	/**
	* Remove the minimum item.
	* Throws UnderflowException if empty.
	*/
	void deleteMin()
	{
		if (isEmpty())
			throw UnderflowException();

		array[1] = array[currentSize--];
		percolateDown(1);
	}

	/**
	* Remove the minimum item and place it in minItem.
	* Throws Underflow if empty.
	*/
	void deleteMin(Soldier & minItem)
	{
		if (isEmpty())
			throw UnderflowException();

		minItem = array[1];
		array[1] = array[currentSize--];
		percolateDown(1);
	}

	void makeEmpty()
	{
		currentSize = 0;
	}

	void decreaseKey(int x, int delta){
		int positionX = myHT.returnPositionX(x);
		int temp = array[positionX].returnTurn() - delta;
		array[positionX].setTurn(temp);
		percolateUp(positionX);
	}

	void increaseKey(int x, int delta){
		int positionX = myHT.returnPositionX(x);
		int temp = array[positionX].returnTurn() + delta;
		array[positionX].setTurn(temp);
		percolateDown(positionX);
	}

	void remove(int x){
		int positionX = myHT.returnPositionX(x);
		Soldier y = findMin();
		int temp = y.returnTurn();
		array[positionX].setTurn(temp - 1);
		deleteMin();
	}

	void buildSoldiers(int a1, int a2){
		for (int i = 1; i <= a1; i++){
			int turn = (rand() % 50) + 1;
			Soldier x(i, turn, 0);
			aliveSpartans.insert(1 , i);
			insert(x);
		}
		for (int i = a1; i < a1 + a2; i++){
			int turn = (rand() % 950) + 51;
			Soldier x(i, turn, 1);
			alivePersians.insert(1, i);
			insert(x);
		}
	}

	int events(){
		while (!alivePersians.isEmpty() || !aliveSpartans.isEmpty()){
			Soldier x = findMin();
			if (x.returnSide() == 0){
				int temp = alivePersians.returnRandom();
				alivePersians.remove(temp);
				temp = myHT.returnValueNum(temp);
				remove(temp);
				int time = rand() % 6 + 1;
				increaseKey(x.returnID(), time);
			}
			if (x.returnSide() == 1){
				int chance = rand() % 100;
				if (chance < 5){
					int ran = aliveSpartans.getLength();
					ran = rand() % ran + 1;
					int t = myHT.returnValueNum(aliveSpartans.retrieve(ran));
					array[t].soldierAttacked();
					if (array[t].getStatus()){//if spartan dies, inspires all other spartans
						remove(t);
						aliveSpartans.remove(ran);
						for (int i = 1; i <= aliveSpartans.getLength(); i++){
							int pos = myHT.returnValueNum(aliveSpartans.retrieve(i));
							decreaseKey(pos, rand() % 2 + 1);
						}
					}
					else{
						int time = rand() % 4 + 1;
						increaseKey(t, time);
					}
				}
				int time = rand() % 51 + 10;
				increaseKey(x.returnID(), time);
			}
			if (alivePersians.isEmpty()){
				cout << "\nSpartans Win!" << endl;
				cout << "The number of alive Spartans is " << aliveSpartans.getLength() << endl;
				makeEmpty();
				return aliveSpartans.getLength();
			}
			if (aliveSpartans.isEmpty()){
				cout << "\nPersians Win!" << endl;
				cout << "The number of alive Persians is " << alivePersians.getLength() << endl;
				makeEmpty();
				return alivePersians.getLength() * -1;
			}
		}
	}


private:
	int                currentSize;  // Number of elements in heap
	vector<Soldier> array;        // The heap array
	HashTable myHT;
	LinkedList<int> aliveSpartans;
	LinkedList<int> alivePersians;

	int totalAliveSpartans;
	int totalAlivePersians;


	/**
	* Establish heap order property from an arbitrary
	* arrangement of items. Runs in linear time.
	*/
	void buildHeap()
	{
		for (int i = currentSize / 2; i > 0; i--)
			percolateDown(i);
	}

	/**
	* Internal method to percolate down in the heap.
	* hole is the index at which the percolate begins.
	*/
	void percolateDown(int hole)
	{
		int child;
		Soldier tmp = array[hole];

		for (; hole * 2 <= currentSize; hole = child)
		{
			child = hole * 2;
			if (child != currentSize && array[child + 1] < array[child])
				child++;
			if (array[child] < tmp)
				array[hole] = array[child];
				
			else
				break;
			myHT.modify(array[hole].returnID(), hole);
		}
		array[hole] = tmp;
		myHT.modify(array[hole].returnID(), hole);
	}

	void percolateUp(int x){
		Soldier tmp = array[x];
		for (; array[x] < array[x / 2]; x /= 2)
		{
			array[x] = array[x / 2];
			array[x / 2] = tmp;
			myHT.modify(array[x].returnID(), x);
		}
		myHT.modify(array[x].returnID(), x);

	}
};

#endif