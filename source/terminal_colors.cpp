#include <terminal_colors.h>
#include <iostream>

void TerminalColors::ColorPrint(const char* properties, const char* textToPrint, const bool endLine) {
	std::cout << "\033[" << properties << "m" << textToPrint << "\033[0m";
	if (endLine) {
		std::cout << "\n";
	}
}

void TerminalColors::GreenPrint(const char* textToPrint, const bool endLine) {
	ColorPrint("32;1", textToPrint, endLine);
}

void TerminalColors::RedPrint(const char* textToPrint, const bool endLine) {
	ColorPrint("91;1", textToPrint, endLine);
}

void TerminalColors::BluePrint(const char* textToPrint, const bool endLine) {
	ColorPrint("34;1", textToPrint, endLine);
}

void TerminalColors::YellowPrint(const char* textToPrint, const bool endLine) {
	ColorPrint("33;1", textToPrint, endLine);
}
