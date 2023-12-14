#include <iostream>
#include <string>
#include <iomanip>
#pragma region Windows UTF8 output in console
#include <windows.h>
#pragma execution_character_set( "utf-8" )
#pragma endregion

using namespace std;

class My {
	string* ptr;
public:
	My(const My& other) :ptr{ new string{ *other.ptr } } {
		cout << "Costruttore di copia di " << *this << endl;
	}
	My& operator=(const My& other) {
		ptr = new string{ *other.ptr };
		cout << "Operatore di assegnazione di copia di " << *this << endl;
		return *this;
	}
	My(My&& other) noexcept : ptr{ other.ptr } {
		other.ptr = nullptr;
		cout << "Costruttore per spostamento di " << *this << endl;
	}
	My& operator=(My&& other) noexcept {
		delete ptr;
		ptr = other.ptr;
		other.ptr = nullptr;
		cout << "Operatore di spostamento di " << *this << endl;
		return *this;
	}

	My(string s) :ptr{ new string(s) } {
		cout << "Costruttore di " << *this << endl;
	}
	virtual ~My() {
		if (ptr)
			cout << "Distruttore di " << *this << endl;
		else
			cout << "Sto eseguendo il distruttore dell'oggetto, ma probabilmente è stato spostato, perché non esiste la stringa al suo interno!" << endl;
		delete ptr;
	}

	static friend ostream& operator<<(ostream& s, const My& my) {
		if (my.ptr)
			return s << "My(" << quoted(*(my.ptr)) << ')';
		return s << "Ops ptr == nullptr!!! Sei sicuro che non stai cercando di stampare un oggetto spostato?";
	}
};

static My factory(string content) {
	return My{ content };
}
int main()
{
#pragma region Windows UTF8 output in console
	SetConsoleOutputCP(65001);
#pragma endregion

	My my{ "Riga 61"s };
	cout << "Riga 62 " << my << endl;
	My my2 = my; // <=> My m2{ my };
	cout << "Riga 63 " << my2 << endl;
	My m3{ "Riga 65" };
	m3 = my;
	cout << "Riga 67 " << m3 << endl;
	m3 = factory("Chiamata a Factory di riga 67");
	cout << "Riga 68 " << m3 << endl;
	//My m4{ factory("Riga 59") };
	My m4 = move(factory("Riga 71"));
	m3 = move(m4);
	cout << m4 << endl;
}