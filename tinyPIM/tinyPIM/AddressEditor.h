#pragma once
#include "Editor.h"
#include "Address.h"

class AddressEditor: public Editor
{
public:
	AddressEditor(void) {}
	AddressEditor(const Address &a): addr_(a) {}
	~AddressEditor(void);
	bool edit();
	Address addr() const {return addr_;}
	void addr(const Address &a) {addr_ = a;}

private:
	AddressEditor(const AddressEditor&);
	const AddressEditor& operator=(const Address&); 
	Address addr_;
};

