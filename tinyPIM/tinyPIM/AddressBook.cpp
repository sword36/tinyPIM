#include "AddressBook.h"
#include <iostream>

int AddressBook::nextID_ = 1;

AddressBook::AddressBook(void)
{
}


AddressBook::~AddressBook(void)
{
}

int AddressBook::insertAddress(const Address& addr, int recordID) throw(DuplicateID)
{
	if (recordID == 0)
		recordID = nextID_++;
	else if (recordID >= nextID_)
		nextID_ = recordID + 1;
	else if (getByID(recordID) != addresses_.end())
		throw DuplicateID();

	addrlist::iterator i;
	for (i = addresses_.begin(); i != addresses_.end(); ++i)
		if (addr < *i)
			break;
	i = addresses_.insert(i, addr);
	i -> recordID(recordID);

	return recordID;
}

AddressBook::addrlist::iterator AddressBook::getByID(int recordID) 
{
	for (std::list<Address>::iterator i = addresses_.begin(); i != addresses_.end(); ++i)
		if (i -> recordID() == recordID)
			return i;
	return addresses_.end();
}

void AddressBook::eraseAddress(int recordID) throw(AddressNotFound)
{
	std::list<Address>::iterator index = getByID(recordID);
	if (index == addresses_.end())
		throw AddressNotFound();
	addresses_.erase(index);
}

void AddressBook::replaceAddress(const Address& addr, int recordID) throw(AddressNotFound)
{
	if (recordID == 0)
		recordID = addr.recordID();
	std::list<Address>::iterator index = getByID(recordID);
	if (index == addresses_.end())
		throw AddressNotFound();
	eraseAddress(recordID);
	insertAddress(addr, recordID);
}

const Address& AddressBook::getAddress(int recordID) const throw(AddressNotFound)
{
	std::list<Address>::const_iterator index;
	for (index = addresses_.begin(); index != addresses_.end(); ++index)
		if (index -> recordID() == recordID)
			break;
	if (index == addresses_.end())
		throw AddressNotFound();
	return *index;
}

void AddressBook::print() const
{
	for (AddressBook::addrlist::const_iterator i = addresses_.begin(); i != addresses_.end(); ++i)
	{
		const Address& a = *i;
		std::cout <<"*****************\n"<<
			a.recordID()<<"\n"<<
			a.firstname()<<" "<<a.lastname()<<"\n"<<
			a.address() << "\n"<< a.phone() << "\n"<<
			std::endl;
	}
}