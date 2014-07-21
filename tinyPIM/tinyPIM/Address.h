#pragma once
#include <string>

class Address
{
public:
	Address(void);
	~Address(void);
	std::string lastname() const {return lastname_;}
	void lastname(std::string& ch);

	std::string firstname() const {return firstname_;}
	void firstname(std::string& ch);

	std::string phone() const {return phone_;}
	void phone(std::string& ch);

	std::string address() {return address_;}
	void address(std::string& ch);


private:
	std::string firstname_;
	std::string lastname_;
	std::string phone_;
	std::string address_;
};

