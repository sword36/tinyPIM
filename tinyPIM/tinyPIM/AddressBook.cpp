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

	Address addrCopy(addr);
	addrCopy.recordID(recordID);
	addresses_.insert(addrCopy);

	return recordID;
}

AddressBook::addrByName_t::iterator AddressBook::getByID(int recordID) 
	throw(AddressNotFound)
{
	for (addrByName_t::iterator i = addresses_.begin(); i != addresses_.end(); ++i)
		if (i -> recordID() == recordID)
			return i;
	return addresses_.end();
}

AddressBook::addrByName_t::const_iterator AddressBook::getByID(int recordID) const 
	throw(AddressNotFound)
{
	for (addrByName_t::const_iterator i = addresses_.begin(); i != addresses_.end(); ++i)
		if (i -> recordID() == recordID)
			return i;
	return addresses_.end();
}

void AddressBook::eraseAddress(int recordID) throw(AddressNotFound)
{
	addrByName_t::iterator index = getByID(recordID);
	if (index == addresses_.end())
		throw AddressNotFound();
	addresses_.erase(index);
}

void AddressBook::replaceAddress(const Address& addr, int recordID) throw(AddressNotFound)
{
	if (recordID == 0)
		recordID = addr.recordID();
	addrByName_t::iterator index = getByID(recordID);
	if (index == addresses_.end())
		throw AddressNotFound();
	eraseAddress(recordID);
	insertAddress(addr, recordID);
}

/*const Address& AddressBook::getAddress(int recordID) const throw(AddressNotFound)
{
	std::list<Address>::const_iterator index;
	for (index = addresses_.begin(); index != addresses_.end(); ++index)
		if (index -> recordID() == recordID)
			break;
	if (index == addresses_.end())
		throw AddressNotFound();
	return *index;
}*/

int AddressBook::countName(const std::string& firstname,
						   const std::string& lastname) const
{
	Address searchAddr;
	searchAddr.firstname(firstname);
	searchAddr.lastname(lastname);
	return addresses_.count(searchAddr);
}

AddressBook::const_iterator 
	AddressBook::firstNameStartsWith(const std::string &firstname,
									const std::string& lastname) const
{
	Address searchAddr;
	searchAddr.firstname(firstname);
	searchAddr.lastname(lastname);
	return addresses_.lower_bound(searchAddr);
}

AddressBook::const_iterator 
	AddressBook::findNextContains(const std::string& 
		searchStr, const_iterator start) const
{
	return std::find_if(start, addresses_.end(), [searchStr](const Address& a) -> bool
		{return a.firstname().find(searchStr) != std::string::npos || 
				a.lastname().find(searchStr) != std::string::npos ||
				a.phone().find(searchStr) != std::string::npos ||
				a.address().find(searchStr) != std::string::npos;
		});
}

AddressBook::const_iterator 
	AddressBook::findRecordID(int recordID) throw(AddressNotFound)
{
	if (getByID(recordID) == addresses_.end())
		throw AddressNotFound();
	else return getByID(recordID);

}

/*void AddressBook::print() const
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
}*/