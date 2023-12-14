#pragma once
#include <functional>
#include "Node.h"

template<class T>
class Functor {
public:
	virtual void operator()(const T*) = 0;
};

template<class T>
using Functional = std::function<void(const T*)>;

template<class T>
class LinkedList
{
	Node<T>* root;

	void append(T* item, Node<T>* n) {
		if (n->next != nullptr)
			append(item, n->next);
		else
			n->next = new Node<T>(item);
	}

	void navigate(Node<T>* n, Functor<T>&& f) {
		if (n == nullptr) return;
		f(n->item);
		navigate(n->next, std::forward<Functor<T>>(f));
	}

	void navigate(Node<T>* n, Functional<T>&& f) {
		if (n == nullptr) return;
		f(n->item);
		navigate(n->next, std::forward<Functional<T>>(f));
	}
public:
	LinkedList() : root{ nullptr } {}

	void append(T* item) {
		if (root == nullptr) {
			root = new Node<T>(item);
		}
		else
			append(item, root);
	}

	void navigate(Functor<T>&& f) {
		navigate(root, std::forward<Functor<T>>(f));
	}

	void navigate(Functional<T>&& f) {
		navigate(root, std::forward<Functional<T>>(f));
	}
};

