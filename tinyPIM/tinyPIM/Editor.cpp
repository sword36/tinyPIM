#include "Editor.h"

Editor::~Editor(void)
{
}

bool Editor::editSingleLine(const std::string &prompt, std::string &value)
{
	status_ = normal;
	std::cout << prompt;
	if (!value.empty())
		std::cout << " [" << value << ']';
	std::cout << ':';
	std::string result;
	std::getline(std::cin, result, '\n');
	if (std::cin.fail())
	{
		status_ = canceled;
		return false;
	}
	if (result.empty())
		return true;
	if (result == ".")
	{
		status_ = finished;
		return false;
	}
	if (result == "!x")
	{
		status_ = canceled;
		return false;
	}

	value = result;
	return true;
}

bool Editor::editMultiLine(const std::string &prompt, std::string &value)
{
	status_ = normal;
	value += '\n';
	std::string::size_type lineBegin(0), lineEnd(0), lineLen(0);
	while (true)
	{
		if (lineBegin >= value.length())
			value += '\n';
		std::string line;
		lineEnd = value.find('\n', lineBegin);
		lineLen = lineEnd - lineBegin;
		line = value.substr(lineBegin, lineLen);
		if (!editSingleLine(prompt, line))
			break;
		if (line == "!n")
			break;
		if (line == "!i")
		{
			value.insert(lineBegin, "\n");
			continue;
		}
		if (line == "!d")
		{
			value.erase(lineBegin, lineLen + 1);
			continue;
		}
		value.replace(lineBegin, lineLen, line);
		lineBegin += line.length() + 1;
	}
	std::string::size_type strip = value.find_last_not_of('\n') + 1;
	value.erase(strip, std::string::npos);
	return (status() == normal);
}