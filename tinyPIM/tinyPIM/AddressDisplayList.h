#pragma once
#include "displaylist.h"
#include "AddressBook.h"

class AddressDisplayList :
	public DisplayList
{
public:
	AddressDisplayList(AddressBook &addrBook);
	virtual ~AddressDisplayList(void);
	bool findNameStartWith(const std::string& firstname,
						const std::string& lastname = "");
	void linstContainsString(const std::string&);
	void listAll();
protected:
	virtual void displayRecord(int recordID);
	virtual bool fetchMore(int startID, int numRecords,
							std::vector<int>& result);
private:
	AddressBook &addressBook_;
	std::string containsString_;
};

