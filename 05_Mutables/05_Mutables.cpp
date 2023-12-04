#include <iostream>
#include <string>
using namespace std;

// Customer Class
class Customer {
	string name;
	mutable string placedorder;
	int tableno;
	mutable int bill;
public:
	Customer(string s, string m, int a, int p) :name{ s }, placedorder{ m }, tableno{ a }, bill{ p } {}

	void changePlacedOrder(string p) const { placedorder = p; }

	void changeBill(int s) const { bill = s; }

	void display() const
	{
		cout << "Customer name is: " << name << endl;
		cout << "Food ordered by customer is: " << placedorder << endl;
		cout << "table no is: " << tableno << endl;
		cout << "Total payable amount: " << bill << endl;
	}
};

// Driver code
int main()
{
	const Customer c1("Pravasi Meet", "Ice Cream", 3, 100);
	c1.display();
	c1.changePlacedOrder("GulabJammuns");
	c1.changeBill(150);
	c1.display();
	return 0;
}
