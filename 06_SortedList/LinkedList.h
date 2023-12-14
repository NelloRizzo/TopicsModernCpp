#pragma once
#include <functional>
#include <memory>
#include "Node.h"

template<class T>
class Functor {
public:
	virtual void operator()(const std::weak_ptr<T>) = 0;
};

template<class T>
using Functional = std::function<void(const std::weak_ptr<T>)>;

template<class T>
class LinkedList
{
	std::shared_ptr<Node<T>> root;

	void append(T& item, std::shared_ptr<Node<T>> n) {
		auto node = std::make_shared<Node<T>>(item);
		if (item < *n->item) {
			n->prev = node;
			node->next = n;
		}
		else {
			n->next = node;
			node->prev = n;
		}
	}

	void navigate(std::shared_ptr<Node<T>> n, Functor<T>&& f) {
		if (n == nullptr) return;
		navigate(n->prev, std::forward<Functor<T>>(f));
		std::weak_ptr<T> wp = n->item;
		f(wp);
		navigate(n->next, std::forward<Functor<T>>(f));
	}

	void navigate(std::shared_ptr<Node<T>> n, Functional<T>&& f) {
		if (n == nullptr) return;
		navigate(n->prev, std::forward<Functional<T>>(f));
		std::weak_ptr<T> wp = n->item;
		f(wp);
		navigate(n->next, std::forward<Functional<T>>(f));
	}
public:
	LinkedList() : root{ nullptr } {}

	void append(T& item) {
		if (root == nullptr) {
			root = std::make_shared<Node<T>>(item);
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

