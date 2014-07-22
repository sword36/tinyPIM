#include "AddressBook.h"
#include <iostream>

int main()
{
	AddressBook book;
	Address a;
	a.firstname("Jony");
	a.lastname("Kashi");
	a.phone("353245");
	a.address("Akad, Niow, dom21");
	
	Address b;
	b.firstname("Katya");
	b.lastname("Shvedenko");
	b.phone("89056544972");
	b.address("ysman, 35");

	int a_id = book.insertAddress(a);
	int b_id = book.insertAddress(b);
	book.print();

	b.address("ysman, 42");
	b.firstname("Ekater");
	std::cout << "before replace\n";
	book.replaceAddress(b, 2);
	book.print();

	return 0;
}