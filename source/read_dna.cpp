#include <fstream>
#include <bitset>
#include <iostream>
#include <read_dna.h>
#include <terminal_colors.h>
#include <bitpacker.h>
#include <converter.h>
#include <diagnostics.h>
#include <cmath>
#include <array>
#include <algorithm>
#include <iomanip>

unsigned char* ReadDNA::AllocateDNA(const char* fileName, unsigned long& dnaStreamLength, unsigned long& fileSize, unsigned long& compressedSize, bool& isFactorOfThree) {
	unsigned char* dnaStream = nullptr;

	std::fstream file;

	file.open(fileName, std::ios::binary | std::ios::in);

	if (file.is_open()) {
		//Successfully opened file

		//Initialize DNA stream in memory
		file.seekg(0, std::ios::end);
		fileSize = file.tellg();

		int finalLength = (int)(fileSize / 4);

		if ((fileSize % 4) != 0) {
			finalLength++;
		}

		dnaStream = new unsigned char[finalLength];

		for (int i=0; i<finalLength; i++) {
			*(dnaStream+i) = 0;
		}

		dnaStreamLength = finalLength;

		file.seekg(0);

		char character;
		unsigned char binary;
		unsigned long index = 0;

		while (file >> character) {
			binary = (unsigned char)Bitpacker::GetBaseFromChar(character);
			Bitpacker::AppendNucleotideToDNAStream(binary, dnaStream, index);
			index++;
		}

		isFactorOfThree = (index % 3 == 0) ? true : false;
		compressedSize = (unsigned long)(index / 4);
		if ((index % 4) != 0) compressedSize++;
	}
	else {
		std::string error_code("Could not open up file '" + std::string(fileName) + "'");
		TerminalColors::RedPrint(error_code.c_str());
	}

	file.close();

	return dnaStream;
}

void ReadDNA::PrintFileSize(unsigned int bytes, unsigned int compressedSize) {
	//Eventually add suffixes such as KB, MB, GB, and TB

	std::string toPrint = "Loaded file with size: " + std::to_string(bytes) + " bytes (Compressed size: " + std::to_string(compressedSize) + " bytes)...";

	TerminalColors::BluePrint(toPrint.c_str());
}
