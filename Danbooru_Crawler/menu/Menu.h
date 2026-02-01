#ifndef Menu_H
#define Menu_H

#include <string>
#include <vector>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#include <conio.h>
#else
#include<unistd.h>
#include <sys/ioctl.h>
#endif

using std::vector;

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define ESC 27
#define BACKSPACE 8

enum class MenuOptionType {
	Choice,
	TextInput,
	Toggle,
	Action
};

struct MenuOption {
	int operationId;
	std::string name;
	MenuOptionType type;

	vector<std::string> queryChoice = {};
	int selectedChoiceIndex = 0;
	bool toggle = false;
	std::string input = "";

	std::string displayValue() const;
};

class Menu {
private:
	vector<MenuOption> option;
	int selectedIndex = 0;

	int getTerminalWidth();
	void clearScreen();
	void printCenter(const std::string& text, int width);
	void displayMenu();
	void getTextInput(std::string& input);
public:
	Menu();
	void show();
	void clear();
	void addOption(const MenuOption& opt);
	void updateOption(int index, const MenuOption& opt);
	const vector<MenuOption>& getChoice();
};

#endif // !Menu_H