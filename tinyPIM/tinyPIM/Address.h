#pragma once
#include <string>

class Address
{
public:
	Address(void);
	~Address(void);
	std::string lastname() const {return lastname_;}
	void lastname(const std::string& ch);

	std::string firstname() const {return firstname_;}
	void firstname(const std::string& ch);

	std::string phone() const {return phone_;}
	void phone(const std::string& ch);

	std::string address() const {return address_;}
	void address(const std::string& ch);

	int recordID() const {return recordID_;}
	void recordID(int i);


private:
	std::string firstname_;
	std::string lastname_;
	std::string phone_;
	std::string address_;
	int recordID_;
};

bool operator==(const Address& a1, const Address& a2);
bool operator<(const Address& a1, const Address& a2);

