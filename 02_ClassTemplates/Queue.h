#pragma once
template<class T>
class Queue
{
private:
	T* _queue;
	int _capacity;
	int _current;

	void dispose() {
		delete[] _queue;
		_queue = nullptr;
	}
public:
	Queue() :Queue(20) {}
	Queue(int capacity) :_capacity{ capacity }, _queue{ new T[capacity] }, _current{ 0 } {}

	virtual ~Queue() { dispose(); }

	inline int capacity() const { return _capacity; }

	void enqueue(T);
	T offer();
};

template<class T>
inline void Queue<T>::enqueue(T item)
{
	_queue[_current] = item;
	_current = (_current + 1) % _capacity;
}

template<class T>
inline T Queue<T>::offer()
{
	T item = _queue[_current];
	_current--;
	if (_current < 0) _current = _capacity - 1;
	return item;
}
