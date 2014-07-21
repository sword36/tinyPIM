#include "Address.h"



Address::Address(void)
{
}

void Address::firstname(std::string& ch)
{
	firstname_ = ch;
}

void Address::lastname(std::string& ch)
{
	lastname_ = ch;
}

void Address::phone(std::string& ch)
{
	phone_ = ch;
}

void Address::address(std::string& ch)
{
	address_ = ch;
}
Address::~Address(void)
{
}
