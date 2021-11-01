#include <command.h>
#include <vector>
#include <iostream>
#include <search_dna.h>
#include <cstring>
#include <terminal_colors.h>
#include <bitpacker.h>
#include <diagnostics.h>
#include <string_comparisons.h>

extern long fileSize;
extern unsigned char* dnaStream;

void OnSearchDNACalled(std::vector<const char*>& flagKeys, std::vector<const char*>& flagValues) {
	unsigned long index;
	unsigned long length = 1;
	std::string factor;

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
		else if (StringComparisons::StringsAreEqual(flagKeys[i], (const char*)"-f")) {
			if (!StringComparisons::StringIsNullOrEmpty(flagValues[i])) {
				factor = flagValues[i];
			}
			else {
				TerminalColors::RedPrint("Attribute -f requires a string factor");
			}
		}
		else {
			std::string error(std::string("No argument ") + flagKeys[i]);
			TerminalColors::RedPrint(error.c_str());
			return;
		}
	}

	if (index >= fileSize) {
		TerminalColors::RedPrint("ERROR: Index out of bounds. Index too high or negative?");
		return;
	}

	if (factor.size() > length) {
		TerminalColors::RedPrint("ERROR: Factor cannot be larger than length");
	}

	std::string buffer;

	bool previousMatched = false;
	unsigned long matchedIndex = 0;
	unsigned char factorBase = Bitpacker::GetBaseFromChar(factor[matchedIndex]);
	unsigned long foundIndex = 0;

	for (int i=0; i<length; i++) {
		if ((index+i) >= fileSize) {
			TerminalColors::RedPrint("\nERROR: Index went out of bounds. Index or length too high or negative?");
			return;
		}

		DNA_Nucleotide nucleotide = Bitpacker::GetNucleotideFromDNAStream(dnaStream, (index+i), true);

		if (nucleotide == factorBase) {
			++matchedIndex;
			if (matchedIndex >= factor.size()) {
				//Found match

				buffer = (const char*)"Found factor: " + factor + "\tAt index: " + std::to_string(foundIndex);
				matchedIndex = 0;
				foundIndex = index+i+1;
				TerminalColors::GreenPrint(buffer.c_str());
			}
		}
		else {
			matchedIndex = 0;
			foundIndex = index+i+1;
		}

		factorBase = Bitpacker::GetBaseFromChar(factor[matchedIndex]);
	}

	if (buffer == "") {
		TerminalColors::GreenPrint("Did not find any matches...");
	}
}

Command* GetSearchDNACommand() {
	const char* commandName = (char*)"searchdna";
	const char* commandDescription = (char*)"Searches for DNA through a set of indices";
	std::vector<const char*> flags{(char*)"-i", (char*)"-f", (char*)"-l"};
	unsigned int flagCount = flags.size();
	std::vector<const char*> descriptions = {(char*)"The starting index", (char*)"The search factor. Example '-f ACCGA'", (char*)"The length to search through"};
	void (*onCall)(std::vector<const char*>&, std::vector<const char*>&) = OnSearchDNACalled;

	Command* command = new Command(commandName, commandDescription, flags, flagCount, descriptions, onCall);

	Command& commandReference = *command;

	return command;
}
