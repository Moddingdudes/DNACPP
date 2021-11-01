#include <command.h>
#include <vector>
#include <iostream>
#include <exit.h>

void OnExitCalled(std::vector<const char*>& flagKeys, std::vector<const char*>& flagValues) {
	exit(0);
}

Command* GetExitCommand() {
	const char* commandName = (char*)"exit";
	const char* commandDescription = (char*)"Exits the program";
	std::vector<const char*> flags;
	unsigned int flagCount = flags.size();
	std::vector<const char*> descriptions;
	void (*onCall)(std::vector<const char*>&, std::vector<const char*>&) = OnExitCalled;

	Command* command = new Command(commandName, commandDescription, flags, flagCount, descriptions, onCall);

	Command& commandReference = *command;

	return command;
}
