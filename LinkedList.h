#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include "List.h"
#include <stdlib.h>

using namespace std;

template<class T>
struct Node
{
	T item;
	Node *next;
};

template<class T>
class LinkedList: public List<T>
{
	private:
		Node<T> *head;
		int size;
	public:
		LinkedList();
		~LinkedList();
		bool isEmpty();
		int getLength();
		void insert(int pos, T item);
		void remove(int pos);
		T retrieve(int pos);
		T returnRandom();
};

template<class T>
LinkedList<T>::LinkedList()
{
	head=NULL;
	size=0;
}

template<class T>
LinkedList<T>::~LinkedList()
{
	while(!isEmpty())
	{
		remove(1);
	}	
}

template<class T>
bool LinkedList<T>::isEmpty()
{
	if(size==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
int LinkedList<T>::getLength()
{
	return size;
}

template<class T>
void LinkedList<T>::insert(int pos, T item)
{
	Node<T> *prev = new Node<T>();
	Node<T> *curr = new Node<T>();
	Node<T> *newNode=new Node<T>();
	newNode->item=item;
	int nodePos=1;
	curr=head;
	if(head != NULL)
	{
		while((curr->next!=NULL)&&(nodePos<pos))
		{
			prev=curr;
			curr=curr->next;
			nodePos++;
		}
		if(pos==1)
		{
			newNode->next=head;
			head=newNode;
		}
		else if((pos==size+1)&&(curr->next==NULL))
		{
			curr->next=newNode;
			newNode->next=NULL;
		}
		else
		{
			prev->next=newNode;
			newNode->next=curr;
		}
	}
	else
	{
		head=newNode;
		newNode->next=NULL;
	}
	size++;
}

template<class T>
void LinkedList<T>::remove(int pos)
{
	Node<T> *prev = new Node<T>();
	Node<T> *curr = new Node<T>();
	curr=head;
	int nodePos=1;
	while((curr->next!=NULL)&&(nodePos<pos))
	{
		prev=curr;
		curr=curr->next;
		nodePos++;
	}
	if(pos==1)
	{
		head=head->next;
	}
	else
	{
		prev->next=curr->next;
	}
	T item=curr->item;
	delete curr;
	size--;
}

template<class T>
T LinkedList<T>::retrieve(int pos)
{
	Node<T> *curr=new Node<T>();
	curr=head;
	int i=1;
	while(i<pos)
	{
		curr=curr->next;
		i++;
	}
	return curr->item;
}

template<class T>
T LinkedList<T>::returnRandom(){
	int pos = rand() % size + 1;
	while (pos < 1){
		pos = rand() % size + 1;
	}
	return retrieve(pos);
}




#endif




