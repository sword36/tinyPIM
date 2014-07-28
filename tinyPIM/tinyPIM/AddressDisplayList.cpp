#include "AddressDisplayList.h"
#include <iostream>
#include <iomanip>

AddressDisplayList::AddressDisplayList(AddressBook& addrBook)
	:addressBook_(addrBook)
{
}


AddressDisplayList::~AddressDisplayList(void)
{
}

void AddressDisplayList::displayRecord(int recordID)
{
	Address record = addressBook_.getAddress(recordID);
	std::string name = record.firstname();
	if (!record.lastname().empty())
		name.append(", ").append(record.lastname());
	std::cout << std::setw(40) << std:: setfill(' ') <<
		std::left << name << record.phone();
}

 bool AddressDisplayList::fetchMore(int startID, int numRecords,
							std::vector<int>& result)
{

	return true;
}