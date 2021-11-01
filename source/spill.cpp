#include <command.h>
#include <vector>
#include <iostream>
#include <spill.h>
#include <cstring>
#include <terminal_colors.h>
#include <string_comparisons.h>
#include <bitset>

extern long compressedSize;
extern unsigned char* dnaStream;

void OnSpillCalled(std::vector<const char*>& flagKeys, std::vector<const char*>& flagValues) {
	unsigned long index;
	unsigned long length = 1;

	for (int i=0; i<flagKeys.size(); i++) {
		if (StringComparisons::StringsAreEqual(flagKeys[i], (const char*)"-i")) {
			if (!StringComparisons::StringIsNullOrEmpty(flagValues[i])) {
				index = std::stoi(flagValues[i]);
			}
			else {
				TerminalColors::RedPrint("Attribute -i requires a numeric value");
				return;
			}
		}
		else if (StringComparisons::StringsAreEqual(flagKeys[i], (const char*)"-l")) {
			if (!StringComparisons::StringIsNullOrEmpty(flagValues[i])) {
				length = std::stol(flagValues[i]);
			}
			else {
				TerminalColors::RedPrint("Attribute -l requires a numeric value");
				return;
			}
		}
		else {
			std::string error(std::string("No argument ") + flagKeys[i]);
			TerminalColors::RedPrint(error.c_str());
			return;
		}
	}

	if (index >= compressedSize) {
		TerminalColors::RedPrint("ERROR: Index out of bounds. Index too high or negative?");
		return;
	}

	std::string buffer;

	for (int i=0; i<length; i++) {
		if ((index+i) >= compressedSize) {
			TerminalColors::RedPrint("\nERROR: Index went out of bounds. Index or length too high or negative?");
			return;
		}
		buffer = std::bitset<8>(*(dnaStream+index+i)).to_string();
		TerminalColors::GreenPrint(buffer.c_str(), false);
	}
	std::cout << "\n";
}

Command* GetSpillCommand() {
	const char* commandName = (char*)"spill";
	const char* commandDescription = (char*)"Gets DNA converted to binary at certain index";
	std::vector<const char*> flags{(char*)"-i", (char*)"-l"};
	unsigned int flagCount = flags.size();
	std::vector<const char*> descriptions = {(char*)"The index of the DNA binary you want to get", (char*)"The length of how many bytes to print"};
	void (*onCall)(std::vector<const char*>&, std::vector<const char*>&) = OnSpillCalled;

	Command* command = new Command(commandName, commandDescription, flags, flagCount, descriptions, onCall);

	Command& commandReference = *command;

	return command;
}
