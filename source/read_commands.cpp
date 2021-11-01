#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <string_comparisons.h>
#include <read_commands.h>

#include <command.h>
#include <get_protein.h>
#include <get_amino_acid.h>
#include <help.h>
#include <exit.h>
#include <get_dna.h>
#include <get_mrna.h>
#include <search_dna.h>
#include <spill.h>

std::vector<Command*>* commands = nullptr;

void ReadCommands::Init() {
	commands = new std::vector<Command*>; //We do not need to free this, as it will last the duration of the program

	//I would like to rewrite this to have commands automatically register in their own command class
	//As well as rewrite a few other parts to make coding more understandable

	commands->push_back(GetProteinCommand());
	commands->push_back(GetAminoAcidCommand());
	commands->push_back(GetHelpCommand());
	commands->push_back(GetExitCommand());
	commands->push_back(GetDNACommand());
	commands->push_back(GetMRNACommand());
	commands->push_back(GetSearchDNACommand());
	commands->push_back(GetSpillCommand());
}

void ReadCommands::ReadCommand(const char* commandString) {
	unsigned int flagCount = 0;
	const char* commandName = nullptr;
	std::vector<const char*>* commandFlagKeys = nullptr;
	std::vector<const char*>* commandFlagValues = nullptr;

	GetCommandFlags(commandString, flagCount, commandFlagKeys, commandFlagValues, commandName);

	bool foundCommand = false;

	for (int i=0; i<commands->size(); i++) {
		Command& commandReference = *(commands->at(i));

		if (StringComparisons::StringsAreEqual(commandReference.GetCommandName(), commandName)) {
			//Found a command match
			commandReference.CallCommandOnCall(*commandFlagKeys, *commandFlagValues);
			foundCommand = true;
		}
	}

	if (!foundCommand) {
		//Could not find the command
		std::cout << "Could not find command with name: " << commandName << std::endl;
	}

	//Free all memory

	for (int i=0; i<commandFlagKeys->size(); i++) {
		delete[] commandFlagKeys->at(i);
	}

	for (int i=0; i<commandFlagValues->size(); i++) {
		delete[] commandFlagValues->at(i);
	}

	delete commandFlagKeys;
	delete commandFlagValues;
}

void ReadCommands::GetCommandFlags(const char* commandString, unsigned int& flagCount, std::vector<const char*>*& commandFlagKeys, std::vector<const char*>*& commandFlagValues, const char*& commandName) {
	std::string buffer;

	commandFlagKeys = new std::vector<const char*>;
	commandFlagValues = new std::vector<const char*>;

	const char* characterPointer = commandString;

	std::vector<const char*> splitCommands;

	while ((*characterPointer) != '\0') {
		if (*characterPointer == ' ') {
			const char* bufferString = buffer.c_str();
			char* newBufferString = new char[sizeof(buffer.size() + 1)];
			strcpy(newBufferString, bufferString);

			if (commandName == nullptr) {
				commandName = newBufferString;
			}
			else {
				splitCommands.push_back(newBufferString); //Add a deep clone of the buffer string so it's not destroyed when the function goes out of scope
			}
			buffer = "";
			++characterPointer;
			continue;
		}

		buffer += *characterPointer;
		++characterPointer;
	}

	const char* bufferString = buffer.c_str();
	char* newBufferString = new char[sizeof(buffer.size() + 1)];
	strcpy(newBufferString, bufferString);

	if (commandName == nullptr) {
		commandName = newBufferString;
	}
	else {
		splitCommands.push_back(newBufferString);
	}

	bool previousCommandWasKey = false;

	for (int i=0; i<splitCommands.size(); i++) {
		if (*(splitCommands[i]) == '-') {
			++flagCount;
			//Flag detected, add it to the keys
			if (previousCommandWasKey) {
				//Got two keys in a row, set the value of the previous key to nothing to keep offsets
				char* emptyChar = new char('\0');

				commandFlagValues->push_back(emptyChar);
			}
			previousCommandWasKey = true;
			commandFlagKeys->push_back(splitCommands[i]);
		}
		else {
			//No flag detected, add it to the values
			previousCommandWasKey = false;
			commandFlagValues->push_back(splitCommands[i]);
		}
	}

	if (previousCommandWasKey) {
		char* emptyChar = new char('\0');

		commandFlagValues->push_back(emptyChar);
	}
}
