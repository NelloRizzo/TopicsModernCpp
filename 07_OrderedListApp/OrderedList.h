#pragma once
#include <memory>
#include <iostream>
#include <functional>

/// <summary>
/// Requisito di ordinamento per gli elementi della lista
/// </summary>
template<class T>
concept Ordered = requires (T t1, T t2) { {t1 > t2 } -> std::_Implicitly_convertible_to<bool>; };

template<Ordered T> class OrderedList;

/// <summary>
/// Un nodo della lista.
/// </summary>
/// <typeparam name="T">Tipo di dato gestito nel nodo.</typeparam>
template <Ordered T>
class Node
{
	/// <summary>
	/// Il contenuto del nodo.
	/// </summary>
	std::shared_ptr<T> item;
	/// <summary>
	/// Il prossimo nodo.
	/// </summary>
	std::shared_ptr<Node<T>> next;
	/// <summary>
	/// Friendship con la lista che gestisce i nodi.
	/// </summary>
	friend class OrderedList<T>;
	/// <summary>
	/// Costruttore.
	/// </summary>
	/// <param name="item">Elemento gestito dal nodo.</param>
	/// <param name="next">Nodo successivo.</param>
	Node(T item, std::shared_ptr<Node<T>> next) :item{ std::make_shared<T>(item) }, next{ next } {}
public:
	/// <summary>
	/// Costruttore template per il perfect forwarding degli elementi.
	/// </summary>
	/// <typeparam name="C">Tipo di dato gestito nel nodo.</typeparam>
	/// <param name="item">Elemendo gestito nel nodo.</param>
	template<Ordered C>
	Node(C&& item) :Node(item, nullptr) {}
};

template<class T>
using NodePtr = std::shared_ptr<Node<T>>;

/// <summary>
/// Una lista ordinata di elementi.
/// </summary>
/// <typeparam name="T">Tipo di elemento gestito nella lista.</typeparam>
template<Ordered T>
class OrderedList
{
	/// <summary>
	/// Nodo radice.
	/// </summary>
	NodePtr<T> root;
	/// <summary>
	/// Aggiunge ricorsivamente un nodo al punto giusto nella lista.
	/// </summary>
	/// <param name="item">Elemento da inserire nel nodo.</param>
	/// <param name="parent">Nodo parent.</param>
	void append(T item, NodePtr<T>& parent) {
		if (item > *parent->item) { // se il nodo da aggiungere è maggiore del corrente
			if (parent->next) { // se esiste un successivo
				append(item, parent->next); // aggiunge al successivo (ricorsione)
			}
			else
				parent->next = std::make_shared<Node<T>>(item); // altrimenti il successivo è proprio questo nodo
		}
		else { // se il nodo non è maggiore, va inserito prima del corrente
			auto p = parent; // memorizza il puntatore corrente
			parent = std::make_shared<Node<T>>(item); // il corrente è il nuovo nodo
			parent->next = p; // il successivo è il vecchio corrente
		}
	}
	/// <summary>
	/// Visita l'albero ricorsivamente.
	/// </summary>
	/// <param name="start">Nodo di partenza.</param>
	/// <param name="f">Funzione che visita i nodi uno alla volta</param>
	void visit(NodePtr<T> start, std::function<void(const T)> f) {
		if (start == nullptr) return; // se il nodo è nullo, esce
		// visita il nodo passandolo alla funzione che lo gestirà
		f(*start->item);
		// passa al nodo successivo
		visit(start->next, f);
	}
public:
	/// <summary>
	/// Costruttore.
	/// </summary>
	OrderedList() :root{} {}
	/// <summary>
	/// Aggiunge un elemento implementando il perfect forwarding.
	/// </summary>
	/// <typeparam name="C">Tipo di dato gestito dalla lista.</typeparam>
	/// <param name="item">Elemento da aggiungere alla lista.</param>
	template<Ordered C>
	void append(C&& item) {
		if (root) // se root è stato già inizializzato
			append(std::forward<T>(item), root); // aggiunge ricorsivamente
		else // altrimenti
			root = std::make_shared<Node<T>>(std::forward<Node<T>>(Node<T>{ item })); // imposta root
	}
	/// <summary>
	/// Visita l'albero attraverso una funzione.
	/// </summary>
	/// <param name="f">Funzione visitor.</param>
	void visit(std::function<void(const T)> f) { visit(root, std::move(f)); }
};



