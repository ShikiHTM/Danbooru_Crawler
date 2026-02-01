#include "Menu.h"

#define DEFAULT_WIDTH 80

int Menu::getTerminalWidth() {
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		return csbi.srWindow.Right - csbi.srWindow.Left + 1;
	}
	return DEFAULT_WIDTH;
#else
	struct winsize w;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
		return w.ws_col;
	}
	return DEFAULT_WIDTH;
#endif
}

std::string MenuOption::displayValue() const {
	switch (type) {
	case MenuOptionType::Toggle:
		return toggle ? "X" : " ";

	case MenuOptionType::TextInput:
		return input.empty() ? " " : input;

	case MenuOptionType::Choice:
		if (queryChoice.empty()) return "";
		if (selectedChoiceIndex < 0 || selectedChoiceIndex >= (int)queryChoice.size()) return "?";

		return queryChoice[selectedChoiceIndex];
	case MenuOptionType::Action:
		return "";
	default:
		return "";
	}
}

void Menu::clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void Menu::printCenter(const std::string& text, int width) {
	int padding = (int)(width - text.length()) / 2;
	std::cout << std::string(std::max(0, padding), ' ') << text << std::endl;
}

void Menu::displayMenu() {
	clearScreen();
	int width = getTerminalWidth();

	std::cout << "\n\n";

	printCenter("Danbooru Crawler", width);

	int maxLength = 0;
	for (const auto& opt : option) {
		int len = (int)opt.name.length() + 6;
		if (opt.type == MenuOptionType::Toggle || opt.type == MenuOptionType::Choice || opt.type == MenuOptionType::TextInput) {
			len += 4;
		}
		maxLength = std::max(maxLength, len);
	}

	int padding = (width - maxLength) / 2;
	padding = std::max(0, padding);

	for (int i = 0; i < (int)option.size(); i++) {
		std::string optionText = (i == selectedIndex ? " > " : "   ") + option[i].name + " ";
		if (option[i].type == MenuOptionType::Toggle) {
			optionText += "[" + std::string(option[i].toggle ? "X" : " ") + "]";
		}
		else if (option[i].type == MenuOptionType::Choice) {
			optionText += "[" + option[i].displayValue() + "]";
		}
		else if (option[i].type == MenuOptionType::TextInput) {
			optionText += "[" + option[i].input + "]";
		}

		std::cout << std::string(padding, ' ') << optionText << std::endl;
	}
}

void Menu::getTextInput(std::string& input) {
	input.clear();
	std::cout << "Enter your input value: ";
	while (true) {
		int ch = _getch();

		if (ch == 0 || ch == 224) {
			_getch();
			continue;
		}

		if (ch == ENTER) break;

		if (ch == BACKSPACE && !input.empty()) {
			std::cout << "\b \b";
			input.pop_back();
		}
		else if (isprint(static_cast<unsigned char>(ch))) {
			input.push_back(static_cast<unsigned char>(ch));
			std::cout << static_cast<unsigned char>(ch);
		}
	}
}

Menu::Menu() {
	clear();
}

void Menu::show() {	
	while (true) {
		displayMenu();
		int key = _getch();
		if (key == 0 || key == 224) {
			key = _getch();
			if (key == UP && selectedIndex > 0) selectedIndex--;
			else if (key == DOWN && selectedIndex < (int)option.size() - 1) selectedIndex++;
			else if (key == LEFT || key == RIGHT) {
				if (option[selectedIndex].type == MenuOptionType::Choice) {
					int& index = option[selectedIndex].selectedChoiceIndex;
					int maxIndex = (int)option[selectedIndex].queryChoice.size() - 1;
					if (key == LEFT && index > 0) {
						index--;
					}
					else if (key == RIGHT && index < maxIndex) {
						index++;
					}
				}
			}
		}
		else if (key == ENTER) {
			if (option[selectedIndex].type == MenuOptionType::Toggle) option[selectedIndex].toggle = !option[selectedIndex].toggle;
			else if (option[selectedIndex].type == MenuOptionType::TextInput) getTextInput(option[selectedIndex].input);
			else if (option[selectedIndex].type == MenuOptionType::Action) break;
		}
		else if (key == ESC) return;
	}
}

void Menu::clear() {
	option = {
		{0, "Type of process (tags/post)", MenuOptionType::Choice, {"tags", "posts"}},
		{1, "Enter your tags/postId", MenuOptionType::TextInput},
		{2, "A number of Arts you want to crawl", MenuOptionType::TextInput},
		{3, "NSFW", MenuOptionType::Toggle},
		{4, "Random", MenuOptionType::Toggle},
		{5, "Download", MenuOptionType::Toggle},
		{6, "Start", MenuOptionType::Action}
	};
	selectedIndex = 0;
}

const vector<MenuOption>& Menu::getChoice() {
	return option;
}