#pragma once
#include "Address.h"
#include <set>
#include <map>
#include <algorithm>

class AddressBook
{
	typedef std::multiset<Address> addrByName_t;
	typedef std::map<int, addrByName_t::iterator> addrByID_t;
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

	int countName(const std::string& firstname, 
				  const std::string& lastname) const;
	typedef addrByName_t::const_iterator const_iterator;
	const_iterator begin() const {return addresses_.begin();}
	const_iterator end() const {return addresses_.end();}
	const_iterator firstNameStartsWith(const std::string& 
		firstname, const std::string& lastname = "") const ;
	const_iterator findNextContains(const std::string& 
		searchStr, const_iterator start) const;
	const_iterator findRecordID(int recordID)  
		throw(AddressNotFound);


	void print() const;

private:
	static int nextID_;
	addrByID_t addrByID_;
	addrByName_t addresses_;
	addrByName_t::iterator getByID(int recordID)
				throw(AddressNotFound);
	addrByName_t::const_iterator getByID(int recordID) const
				throw(AddressNotFound);
	enum {notFound = -1};
	AddressBook(const AddressBook&);
	AddressBook operator=(const AddressBook&);
};

