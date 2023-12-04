#include <iostream>

#include "DateTime.h"

int main()
{
	DateTime d = DateTime::now();

	cout << "Data attuale: " << d << endl;
	d.addDays(1);
	cout << "Domani: " << d << endl;
	d.addDays(-2);
	cout << "Ieri: " << d << endl;
	d.addMonths(2);
	cout << "Dopo due mesi: " << d << endl;
	d.endOfMonth();
	cout << "Alla fine del mese: " << d << endl;

	cout << "Esempio di toString per orari: " <<
		d.toString("^una cifra:\n\tora: ^h^\n\tmin: ^i^\n\tsec: ^s^\ndue cifre:\n\tora: ^H^\n\tmin: ^I^\n\tsec: ^S^\nam 1 cifra: ^a^\nam 2 cifre:^ A") << endl;
	cout << "Esempio di toString per date: " << d.toString("y, Y, m, M, d, D") << endl;
	cout << "Data in formato ISO: " << d.toString() << endl;
	cout << "+ 10 giorni - 2 ore: " << d + "D10H-2" << endl;
	cout << "+ 10 giorni - 2 ore: " << d + 10_days - 2_h << endl;

	DateTime dt = DateBuilder().withDay(1).withYear(2024).withMonth(12).build();
	cout << dt << endl;
}
