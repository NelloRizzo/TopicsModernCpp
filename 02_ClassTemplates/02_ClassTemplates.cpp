#include <iostream>
#include "Queue.h"

using namespace std;
int main()
{
	constexpr int size = 6;
	Queue<int> q{ size };
	cout << "Queue has capacity of " << q.capacity() << endl;
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);
	for (int i = 0; i < size; ++i)
		cout << "Offer: " << q.offer() << endl;
	cout << "Enqueuing 6..." << endl;
	q.enqueue(6);
	for (int i = 0; i < size; ++i)
		cout << "Offer: " << q.offer() << endl;
	cout << "Enqueuing 7..." << endl;
	q.enqueue(7);
	for(int i=0; i < size; ++i)
		cout << "Offer: " << q.offer() << endl;
}
