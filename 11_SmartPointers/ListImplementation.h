#pragma once
#include <functional>
#include <iostream>

template<class T>
class List;

template<class T>
class Functor {
public:
	virtual void operator()(const T* item) = 0;
};

template<class T>
using Functional = std::function<void(const T*)>;

template<class T>
class Node
{
	std::unique_ptr<T> item;
	std::unique_ptr<Node> next;

	Node(T&& item) : item{ new T{item} }, next{ nullptr } {
		std::cout << "Creating " << item << std::endl;
	}

	template<typename T>
	friend class List;
public:
	~Node() { std::cout << "Deleting " << *item << std::endl; }
};

template<class T>
class List
{
	std::unique_ptr<Node<T>> root;

	void append(T&& item, Node<T>* n) {
		if (n->next != nullptr)
			append(std::forward<T&&>(item), n->next.get());
		else
			n->next.reset(new Node<T>{ std::forward<T&&>(item) });
	}

	void navigate(Node<T>* n, Functor<T>&& f) {
		if (n == nullptr) return;
		f(n->item.get());
		navigate(n->next.get(), std::forward<Functor<T>>(f));
	}

	void navigate(Node<T>* n, Functional<T>&& f) {
		if (n == nullptr) return;
		f(n->item.get());
		navigate(n->next.get(), std::forward<Functional<T>>(f));
	}
public:
	List() : root{ nullptr } {}

	void append(T&& item) {
		if (root == nullptr) {
			root.reset(new Node<T>(std::forward<T&&>(item)));
		}
		else
			append(std::forward<T&&>(item), root.get());
	}

	template<class C>
	void emplace_back(C&& item) {
		append(std::forward<T&&>(item));
	}

	void navigate(Functor<T>&& f) {
		navigate(root.get(), std::forward<Functor<T>>(f));
	}

	void navigate(Functional<T>&& f) {
		navigate(root.get(), std::forward<Functional<T>>(f));
	}
};

