#include <command.h>
#include <iostream>
#include <vector>

Command::~Command() {
	delete this;
}

const char* Command::GetCommandName() const {
	return commandName;
}

const char* Command::GetCommandDescription() const {
	return commandDescription;
}

const std::vector<const char*>& Command::GetFlags() const {
	return flags;
}

const std::vector<const char*>& Command::GetDescriptions() const {
	return descriptions;
}

void Command::CallCommandOnCall(std::vector<const char*>& flagKeys, std::vector<const char*>& flagValues) {
	onCall(flagKeys, flagValues);
}

Command::Command(const char* commandName, const char* commandDescription, std::vector<const char*> flags, unsigned int flagCount, std::vector<const char*> descriptions, void(*onCall)(std::vector<const char*>&, std::vector<const char*>&)) {
	this->commandName = commandName;
	this->commandDescription = commandDescription;
	this->flags = flags;
	this->flagCount = flagCount;
	this->descriptions = descriptions;
	this->onCall = onCall;
}

void Command::PrintHelp() {
	for (int i=0; i<flagCount; i++) {
		std::cout << flags[i] << "\t" << descriptions[i] << "\n";
	}
}
