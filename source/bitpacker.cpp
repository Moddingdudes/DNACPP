#include <bitpacker.h>
#include <terminal_colors.h>
#include <iostream>

unsigned char Bitpacker::AppendNucleotide(const unsigned char toAppend, unsigned char appendTo, unsigned char index) {
	if (index > 3 || index < 0) {
		TerminalColors::RedPrint("(AppendNucleotide) Index can only be between 0-3...");
	}
	return ((toAppend << 6) >> (index << 1)) | appendTo;
}
void Bitpacker::AppendNucleotideToDNAStream(const unsigned char toAppend, unsigned char* dnaStream, unsigned long index) {
	unsigned int numberIn = (unsigned int)(index / 4);
	unsigned int relativeIndex = index & 3;

	//NumberIn = 1
	//Relative Index = 2
	//ToAppend = 10

	// 00000000
	// 00000000 = 00000000 | 00000010 << (6 - (4)
	// 00000000 = 00000000 | 00000010 << 2
	// 00000000 = 00000000 | 00001000
	// 00000000 = 00001000
	// 00001000

	*(dnaStream+numberIn) = (*(dnaStream+numberIn)) | (toAppend << (6 - (relativeIndex << 1)));
}
DNA_Nucleotide Bitpacker::GetNucleotide(const unsigned char getFrom, const unsigned char index, bool pushToEnd) {
	if (index > 3 || index < 0) {
		TerminalColors::RedPrint("(GetNucleotide) Index can only be between 0-3...");
		return (DNA_Nucleotide)0;
	}

	unsigned char result = (getFrom << (index << 1)) & 192;
	if (pushToEnd) {
		result = result >> 6;
	}
	return (DNA_Nucleotide)result;
}
DNA_Nucleotide Bitpacker::GetNucleotideFromDNAStream(const unsigned char* dnaStream, const unsigned long index, bool pushToEnd) {
	unsigned int numberIn = (int)(index / 4);
	unsigned int relativeIndex = index & 3;

	return (DNA_Nucleotide)GetNucleotide(*(dnaStream+numberIn), relativeIndex, pushToEnd);
}

unsigned char Bitpacker::GetBaseFromChar(char character) {
	return (character >> 1) & 3;
}
