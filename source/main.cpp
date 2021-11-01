#include <iostream>
#include <stdio.h>
#include <cstring>
#include <converter.h>
#include <terminal_colors.h>
#include <bitpacker.h>
#include <diagnostics.h>
#include <read_commands.h>
#include <read_dna.h>
#include <string_comparisons.h>

#define MAX_BUFFER 64


const char* banner = 
"DDDDDDDDDDDDD        NNNNNNNN        NNNNNNNN               AAA                  CCCCCCCCCCCCC\n"
"D::::::::::::DDD     N:::::::N       N::::::N              A:::A              CCC::::::::::::C\n"
"D:::::::::::::::DD   N::::::::N      N::::::N             A:::::A           CC:::::::::::::::C\n"
"DDD:::::DDDDD:::::D  N:::::::::N     N::::::N            A:::::::A         C:::::CCCCCCCC::::C       +++++++              +++++++\n"
"  D:::::D    D:::::D N::::::::::N    N::::::N           A:::::::::A       C:::::C       CCCCCC       +:::::+              +:::::+\n"
"  D:::::D     D:::::DN:::::::::::N   N::::::N          A:::::A:::::A     C:::::C                     +:::::+              +:::::+\n"
"  D:::::D     D:::::DN:::::::N::::N  N::::::N         A:::::A A:::::A    C:::::C               +++++++:::::+++++++  +++++++:::::+++++++\n"
"  D:::::D     D:::::DN::::::N N::::N N::::::N        A:::::A   A:::::A   C:::::C               +:::::::::::::::::+  +:::::::::::::::::+\n"
"  D:::::D     D:::::DN::::::N  N::::N:::::::N       A:::::A     A:::::A  C:::::C               +:::::::::::::::::+  +:::::::::::::::::+\n"
"  D:::::D     D:::::DN::::::N   N:::::::::::N      A:::::AAAAAAAAA:::::A C:::::C               +++++++:::::+++++++  +++++++:::::+++++++\n"
"  D:::::D     D:::::DN::::::N    N::::::::::N     A:::::::::::::::::::::AC:::::C                     +:::::+              +:::::+\n"
"  D:::::D    D:::::D N::::::N     N:::::::::N    A:::::AAAAAAAAAAAAA:::::AC:::::C       CCCCCC       +:::::+              +:::::+\n"
"DDD:::::DDDDD:::::D  N::::::N      N::::::::N   A:::::A             A:::::AC:::::CCCCCCCC::::C       +++++++              +++++++\n"
"D:::::::::::::::DD   N::::::N       N:::::::N  A:::::A               A:::::ACC:::::::::::::::C\n"
"D::::::::::::DDD     N::::::N        N::::::N A:::::A                 A:::::A CCC::::::::::::C\n"
"DDDDDDDDDDDDD        NNNNNNNN         NNNNNNNAAAAAAA                   AAAAAAA   CCCCCCCCCCCCC\n";



void ClearScreen();
void Prompt(char* buffer, const char* promptMessage=">> ");

unsigned long compressedSize;
unsigned char* dnaStream;
unsigned long fileSize;

int main(int argc, char** argv) {
	char* inputBuffer = new char[MAX_BUFFER];
	char* text_file = nullptr;

	ClearScreen();

	TerminalColors::RedPrint(banner);

	ReadCommands::Init();
	//std::cout << "Welcome to DNAC++, A DNA analyzing tool...\n";
	TerminalColors::GreenPrint("Welcome to DNAC++, A DNA analyzing tool...");

	//Decipher argument values

	std::string error_code;

	for (int i=1; i<argc; i++) {
		if (StringComparisons::StringsAreEqual(argv[i], (const char*)"-i")) {
			//Detected input file
			text_file = argv[++i];
		}
		else {
			error_code = "No Attribute '" + std::string(argv[i]) + "'";
			TerminalColors::RedPrint(error_code.c_str());
			exit(1);
		}
	}

	if (text_file == nullptr) {
		//No text file found
		TerminalColors::RedPrint("No input file provided. Example 'dnac++ -i example.txt'");
		exit(1);
	}

	std::string output_buffer;

	output_buffer = "Loading file...";

	TerminalColors::BluePrint(output_buffer.c_str());

	unsigned long dnaStreamLength = 0;
	bool isFactorOfThree;

	dnaStream = ReadDNA::AllocateDNA(text_file, dnaStreamLength, fileSize, compressedSize, isFactorOfThree);

	if (dnaStream == nullptr) {
		std::cout << "Could not allocate DNA..." << std::endl;
		exit(1);
	}

	ReadDNA::PrintFileSize(fileSize, compressedSize);

	std::cout << "\n";

	if (!isFactorOfThree) {
		TerminalColors::YellowPrint("WARNING: Input file did not contain a factor of 3 nucleotides");
	}

	for(;;) {
		Prompt(inputBuffer);

		ReadCommands::ReadCommand(inputBuffer);
	}
	/*for (int i=0; i<dnaStreamLength; i++) {
		std::cout << "At index " << i << ": " << Diagnostics::ConvertDNANucleotideToString(Bitpacker::GetNucleotideFromDNAStream(dnaStream, i, true)) << "\n";
		//std::cout << "At index " << i << ": " << (int)Bitpacker::GetNucleotideFromDNAStream(dnaStream, i, true) << std::endl;
	}*/

	delete[] inputBuffer;
	delete dnaStream;

	return 0;
}

void ClearScreen() {
	//Use ANSI escape codes to clear screen and reset terminal cursor position
	std::cout << "\033[2J\033[1;1H";
}

void Prompt(char* buffer, const char* promptMessage) {
	std::string bufferString;
	std::cout << promptMessage;
	std::getline(std::cin, bufferString);
	strcpy(buffer, bufferString.c_str());
}
