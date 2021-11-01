#ifndef __TERMINAL_COLORS_H__
#define __TERMINAL_COLORS_H__

class TerminalColors {
public:
	static void GreenPrint(const char* textToPrint, const bool endLine=true);
	static void RedPrint(const char* textToPrint, const bool endLine=true);
	static void BluePrint(const char* textToPrint, const bool endLine=true);
	static void YellowPrint(const char* textToPrint, const bool endLine=true);
private:
	static void ColorPrint(const char* properties, const char* textToPrint, const bool endLine);
};

#endif
