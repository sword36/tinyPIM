#include "Address.h"
#include "AddressEditor.h"
#include <iostream>

void dump(const Address& a)
{
	std::cout << "***********";
	std::cout << "Record: " << a.recordID() <<"\n"<<
		a.firstname() << " " << a.lastname() << " " << a.phone() <<"\n" <<
		a.address() << std::endl;
}
int main()
{
	Address a;
	AddressEditor editor(a);
	while (a.firstname() != "done")
	{
		editor.edit();
		a = editor.addr();
		std::cout << std::endl;
		dump(a);
	}
	return 0;
}