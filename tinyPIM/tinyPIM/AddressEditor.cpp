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
	editPhone("Phone number", phone) &&
	editMultiLine("Address", address);

	if (status() == canceled)
		return false;

	addr_.firstname(firstname);
	addr_.lastname(lastname);
	addr_.phone(phone);
	addr_.address(address);
	return true;
}

bool AddressEditor::editPhone(const std::string &prompt, std::string &phone)
{
	if (!editSingleLine(prompt, phone))
		return false;
	static const std::string digits("1234567890");
	std::string::size_type suffix = phone.find_first_not_of(digits + "()_\/-/");
	if (suffix == std::string::npos)
		suffix = phone.length();
	suffix = phone.find_last_of(digits, suffix);
	if (suffix == std::string::npos)
		return true;
	suffix++;
	std::string newnum;
	std::string::size_type p = phone.find_first_of(digits);
	while (p < suffix)
	{
		std::string::size_type q = phone.find_first_not_of(digits, p);
		newnum.append(phone, p, q - p);
		if (std::string::npos == q)
			break;
		p = phone.find_first_of(digits, q);
	}

	switch (newnum.length())
	{
	case 7: 
		newnum.insert(5, 1, '-');
		newnum.insert(3, 1, '-');
		break;
	case 8: 
		if (newnum[0] != '1')
				return true;
		newnum.insert(4, 1, '-');
		newnum.insert(1, 1, '-');
		break;
	case 11: 
		if (newnum[0] != '8')
			return true;
		newnum.insert(7, 1, '-');
		newnum.insert(4, 1, '-');
		newnum.insert(1, 1, '-');
		break;
	default:
		return true;
	}
	phone.replace(0, suffix, newnum);
	return true;
}


AddressEditor::~AddressEditor(void)
{
}
