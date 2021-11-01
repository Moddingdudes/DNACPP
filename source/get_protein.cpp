#include <command.h>
#include <vector>
#include <iostream>
#include <get_protein.h>
#include <string_comparisons.h>
#include <terminal_colors.h>
#include <cstring>
#include <diagnostics.h>
#include <amino_acid.h>
#include <bitpacker.h>

extern unsigned char* dnaStream;
extern unsigned long fileSize;

void OnGetProteinCalled(std::vector<const char*>& flagKeys, std::vector<const char*>& flagValues) {
	unsigned long index;

	for (int i=0; i<flagKeys.size(); i++) {
		if (StringComparisons::StringsAreEqual(flagKeys[i], (const char*)"-i")) {
			if (!StringComparisons::StringIsNullOrEmpty(flagValues[i])) {
				index = std::stol(flagValues[i]);
			}
			else {
				TerminalColors::RedPrint("Argument -i requires a numeric value");
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

	unsigned char base1 = (unsigned char)Bitpacker::GetNucleotideFromDNAStream(dnaStream, index, true);
	unsigned char base2 = (unsigned char)Bitpacker::GetNucleotideFromDNAStream(dnaStream, index+1, true);
	unsigned char base3 = (unsigned char)Bitpacker::GetNucleotideFromDNAStream(dnaStream, index+2, true);

	if (AminoAcid::GetAminoAcidFromNucleotides((mRNA_Nucleotide)base1, (mRNA_Nucleotide)base2, (mRNA_Nucleotide)base3) == AminoAcid::AMINO_STOP) {
		TerminalColors::RedPrint("Cannot get protein at index where protein is STOP");
		return;
	}

	bool foundStop = true;

	long index1 = index;
	long index2 = index+1;
	long index3 = index+2;

	while (AminoAcid::GetAminoAcidFromNucleotides((mRNA_Nucleotide)base1, (mRNA_Nucleotide)base2, (mRNA_Nucleotide)base3) != AminoAcid::AMINO_STOP) {
		index1 -= 3;
		index2 -= 3;
		index3 -= 3;

		if ((index1 < 0) || (index2 < 0) || (index3 < 0)) {
			unsigned char offset = index % 3;
			std::string error = "No stop found at beginning. Starting from index offset " + std::to_string(offset);
			TerminalColors::YellowPrint(error.c_str());
			index1 = offset;
			index2 = offset+1;
			index3 = offset+2;

			foundStop = false;
			break;
		}

		base1 = Bitpacker::GetNucleotideFromDNAStream(dnaStream, index1, true);
		base2 = Bitpacker::GetNucleotideFromDNAStream(dnaStream, index2, true);
		base3 = Bitpacker::GetNucleotideFromDNAStream(dnaStream, index3, true);
	}

	if (foundStop) {
		index1 += 3;
		index2 += 3;
		index3 += 3;
	}

	base1 = Bitpacker::GetNucleotideFromDNAStream(dnaStream, index1, true);
	base2 = Bitpacker::GetNucleotideFromDNAStream(dnaStream, index2, true);
	base3 = Bitpacker::GetNucleotideFromDNAStream(dnaStream, index3, true);

	AminoAcid::AminoAcidType aminoAcidType = AminoAcid::GetAminoAcidFromNucleotides((mRNA_Nucleotide)base1, (mRNA_Nucleotide)base2, (mRNA_Nucleotide)base3);

	while (aminoAcidType != AminoAcid::AMINO_STOP) {
		AminoAcid::PrintAminoAcid(aminoAcidType);
		index1 += 3;
		index2 += 3;
		index3 += 3;

		if ((index1 >= fileSize) || (index2 >= fileSize) || (index3 >= fileSize)) {
			TerminalColors::RedPrint("No stop found. Hit end of file");
			return;
		}

		base1 = Bitpacker::GetNucleotideFromDNAStream(dnaStream, index1, true);
		base2 = Bitpacker::GetNucleotideFromDNAStream(dnaStream, index2, true);
		base3 = Bitpacker::GetNucleotideFromDNAStream(dnaStream, index3, true);

		aminoAcidType = AminoAcid::GetAminoAcidFromNucleotides((mRNA_Nucleotide)base1, (mRNA_Nucleotide)base2, (mRNA_Nucleotide)base3);

		TerminalColors::RedPrint("-", false);

		if (aminoAcidType == AminoAcid::AMINO_STOP)
			TerminalColors::GreenPrint("STOP");
	}
}

Command* GetProteinCommand() {
	const char* commandName = (char*)"getprotein";
	const char* commandDescription = (char*)"Gets protein at certain index";
	std::vector<const char*> flags{(char*)"-i"};
	unsigned int flagCount = flags.size();
	std::vector<const char*> descriptions = {(char*)"The index of the protein you want to get"};
	void (*onCall)(std::vector<const char*>&, std::vector<const char*>&) = OnGetProteinCalled;

	Command* command = new Command(commandName, commandDescription, flags, flagCount, descriptions, onCall);

	Command& commandReference = *command;

	return command;
}
