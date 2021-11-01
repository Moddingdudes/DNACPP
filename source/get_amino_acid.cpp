#include <command.h>
#include <vector>
#include <iostream>
#include <get_amino_acid.h>
#include <amino_acid.h>
#include <cstring>
#include <terminal_colors.h>
#include <bitpacker.h>
#include <string_comparisons.h>

extern long fileSize;
extern unsigned char* dnaStream;

void OnGetAminoAcidCalled(std::vector<const char*>& flagKeys, std::vector<const char*>& flagValues) {
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


	if ((index % 3) != 0) {
		TerminalColors::YellowPrint("WARNING: Index is not a factor of 3");
	}

	if ((index+2) >= fileSize) {
		TerminalColors::RedPrint("ERROR: Index out of bounds. Index too high or negative?");
		return;
	}

	for (int i=0; i<length*3; i+=3) {
		if ((index+i+2) >= fileSize) {
			TerminalColors::RedPrint("\nERROR: Index went out of bounds. Index or length too high or negative?");
			return;
		}
		AminoAcid::PrintAminoAcid(GetAminoAcidType(index+i, true));
		if ((i+3) < (length*3)) {
			TerminalColors::RedPrint("-", false);
		}
		else {
			std::cout << "\n";
		}
	}
}

AminoAcid::AminoAcidType GetAminoAcidType(unsigned long index, bool suppressWarnings) {
	std::string buffer;

	if ((index % 3) != 0) {
		if (!suppressWarnings) {
			buffer = "WARNING: Index " + std::to_string(index) + " is not a factor of 3 (Assuming beginning index is lined up). In line index is " + std::to_string((int)(index / 3)) + "\n";
			TerminalColors::YellowPrint(buffer.c_str());
		}
	}

	if ((index + 3) >= fileSize) {
		buffer = "ERROR: Index was outside of bounds.\n";
		TerminalColors::RedPrint(buffer.c_str());
		return AminoAcid::UNDEFINED;
	}

	//Explicitly cast output from GetNucleotideFromDNAStream to mRNA, this is the same as using Converter functions.

	mRNA_Nucleotide base1 = (mRNA_Nucleotide)Bitpacker::GetNucleotideFromDNAStream(dnaStream, index, true); 
	mRNA_Nucleotide base2 = (mRNA_Nucleotide)Bitpacker::GetNucleotideFromDNAStream(dnaStream, index+1, true);
	mRNA_Nucleotide base3 = (mRNA_Nucleotide)Bitpacker::GetNucleotideFromDNAStream(dnaStream, index+2, true);

	return AminoAcid::GetAminoAcidFromNucleotides(base1, base2, base3);
}

Command* GetAminoAcidCommand() {
	const char* commandName = (char*)"getaminoacid";
	const char* commandDescription = (char*)"Gets amino acids at certain index";
	std::vector<const char*> flags{(char*)"-i", (char*)"-l"};
	unsigned int flagCount = flags.size();
	std::vector<const char*> descriptions = {(char*)"The index of the amino acid you want to get", (char*)"The length of how many amino acids to print"};
	void (*onCall)(std::vector<const char*>&, std::vector<const char*>&) = OnGetAminoAcidCalled;

	Command* command = new Command(commandName, commandDescription, flags, flagCount, descriptions, onCall);

	Command& commandReference = *command;

	return command;
}
