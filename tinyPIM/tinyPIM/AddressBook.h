#pragma once
#include "Address.h"
#include <list>

class AddressBook
{
public:
	AddressBook(void);
	~AddressBook(void);
	
	class DuplicateID {};
	class AddressNotFound {};

	int insertAddress(const Address& addr, int recordID = 0)
		throw(DuplicateID);
	void eraseAddress(int recordID) throw(AddressNotFound);
	void replaceAddress(const Address& addr, int recordID = 0)
		throw(AddressNotFound);
	const Address& getAddress(int recordID) const
		throw (AddressNotFound);

	void print() const;

private:
	static int nextID_;
	std::list<Address> addresses_;
	std::list<Address>::iterator getByID(int recordID);
	enum {notFound = -1};
	AddressBook(const AddressBook&);
	AddressBook operator=(const AddressBook&);
	typedef std::list<Address> addrlist;
};

