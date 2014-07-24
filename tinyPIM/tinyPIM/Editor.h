#pragma once
#include <iostream>
#include <string>
class Editor
{
public:
	Editor(void):
		status_(normal) {}

	~Editor(void);
	enum editStatus {
		normal,
		finished,
		canceled
	};
	bool editMultiLine(const std::string &prompt, std::string &value);
	bool editSingleLine(const std::string &prompt, std::string &value);
	editStatus status() const {return status_;}

private:
	editStatus status_;
};

