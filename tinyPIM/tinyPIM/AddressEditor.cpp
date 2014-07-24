#include "AddressEditor.h"
#include <iostream>


bool AddressEditor::edit()
{
	std::string firstname = addr_.firstname();
	std::string lastname = addr_.lastname();
	std::string phone = addr_.phone();
	std::string address = addr_.address();

	editSingleLine("First name", firstname) &&
	editSingleLine("Last name", lastname) &&
	editSingleLine("Phone number", phone) &&
	editMultiLine("Address", address);

	if (status() == canceled)
		return false;

	addr_.firstname(firstname);
	addr_.lastname(lastname);
	addr_.phone(phone);
	addr_.address(address);
	return true;
}


AddressEditor::~AddressEditor(void)
{
}
