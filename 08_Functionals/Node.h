#pragma once
#include "LinkedList.h"

template<class T>
class Node
{
	T* item;
	Node* next;

	Node(T* item) :Node(item, nullptr) {}
	Node(T* item, Node* next) :item{ item }, next{ next } {}
	
	template<typename T>
	friend class LinkedList;
};

