#pragma once
#include <string>
#include <stack>

class Menu
{
public:
	Menu(void);
	virtual ~Menu(void);
	virtual void mainLoop() = 0;
	static Menu* activeMenu() {return menuStack_.top();}
	static void enterMenu(Menu* m) {menuStack_.push(m);}
	static void exitMenu() {menuStack_.pop();}
	static bool isActive() {return !menuStack_.empty();}

protected:
	static char getMenuSelection(const std::string& menu,
								const std::string& choices);
	static void clearScreen();
private:
	static std::stack<Menu*> menuStack_;
};

