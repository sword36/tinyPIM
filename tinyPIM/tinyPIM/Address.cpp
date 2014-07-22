#include "Address.h"



Address::Address(void)
	:recordID_(0)
{
}

void Address::recordID(int i)
{
	recordID_ = i;
}

void Address::firstname(const std::string& ch)
{
	firstname_ = ch;
}

void Address::lastname(const std::string& ch)
{
	lastname_ = ch;
}

void Address::phone(const std::string& ch)
{
	phone_ = ch;
}

void Address::address(const std::string& ch)
{
	address_ = ch;
}
Address::~Address(void)
{
}

bool operator==(const Address& a1, const Address& a2)
{
	return (a1.lastname() == a2.lastname() && a1.firstname() == a2.firstname() &&
		a1.address() == a2.address() && a1.phone() == a2.phone());
}

bool operator<(const Address& a1, const Address& a2)
{
	if (a1.firstname() < a2.firstname())
		return true;
	else if (a1.firstname() > a2.firstname())
		return false;
	else return a1.lastname() < a2.lastname();
}