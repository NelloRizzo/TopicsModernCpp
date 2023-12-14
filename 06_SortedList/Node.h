#pragma once
#include <memory>
#include "LinkedList.h"

template<class T>
class Node
{
	std::shared_ptr<T> item;
	std::shared_ptr<Node> next;
	std::shared_ptr<Node> prev;

	Node(T item) :Node(item, nullptr, nullptr) {}
	Node(T item, std::shared_ptr<Node> next, std::shared_ptr<Node> prev) :item{ std::make_shared<T>(item) }, next{ next }, prev{ prev } {}

	template<typename T>
	friend class LinkedList;
};

