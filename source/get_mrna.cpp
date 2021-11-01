#include <command.h>
#include <vector>
#include <iostream>
#include <get_mrna.h>
#include <cstring>
#include <terminal_colors.h>
#include <bitpacker.h>
#include <diagnostics.h>
#include <string_comparisons.h>

extern long fileSize;
extern unsigned char* dnaStream;

void OnGetMRNACalled(std::vector<const char*>& flagKeys, std::vector<const char*>& flagValues) {
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
				TerminalColors::RedPrint("Attribute -l requires a numeric value.");
				return;
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

	std::string buffer;

	for (int i=0; i<length; i++) {
		if ((index+i) >= fileSize) {
			TerminalColors::RedPrint("\nERROR: Index went out of bounds. Index or length too high or negative?");
			return;
		}
		mRNA_Nucleotide nucleotide = (mRNA_Nucleotide)Bitpacker::GetNucleotideFromDNAStream(dnaStream, (index+i), true);
		buffer += Diagnostics::ConvertMRNANucleotideToString(nucleotide);
		TerminalColors::GreenPrint(buffer.c_str(), false);
		if (i+1 >= length) {
			std::cout << "\n";
		}
		else {
			TerminalColors::RedPrint("-", false);
		}
		buffer = "";
	}
}

Command* GetMRNACommand() {
	const char* commandName = (char*)"getmrna";
	const char* commandDescription = (char*)"Gets MRNA at certain index";
	std::vector<const char*> flags{(char*)"-i", (char*)"-l"};
	unsigned int flagCount = flags.size();
	std::vector<const char*> descriptions = {(char*)"The index of the MRNA you want to get", (char*)"The length of how many MRNA to print"};
	void (*onCall)(std::vector<const char*>&, std::vector<const char*>&) = OnGetMRNACalled;

	Command* command = new Command(commandName, commandDescription, flags, flagCount, descriptions, onCall);

	Command& commandReference = *command;

	return command;
}
