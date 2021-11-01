#include <command.h>
#include <vector>
#include <iostream>
#include <help.h>
#include <terminal_colors.h>
#include <string_comparisons.h>

extern std::vector<Command*>* commands;

void OnHelpCalled(std::vector<const char*>& flagKeys, std::vector<const char*>& flagValues) {
	std::string buffer;
	std::string commandName;
	std::string commandDescription;

	const char* toList = nullptr;

	for (int i=0; i<flagKeys.size(); i++) {
		if (StringComparisons::StringsAreEqual(flagKeys[i], (char*)"-l")) {
			if (!StringComparisons::StringIsNullOrEmpty(flagValues[i])) {
				toList = flagValues[i];
			}
			else {
				TerminalColors::RedPrint("Attribute -l requires a command name");
			}
		}
		else {
			std::string error(std::string("No argument ") + flagKeys[i]);
			TerminalColors::RedPrint(error.c_str());
			return;
		}
	}

	if (toList == nullptr) {
		for (int i=0; i<commands->size(); i++) {
			Command& commandReference = *(commands->at(i));
			commandName = commandReference.GetCommandName();
			commandDescription = commandReference.GetCommandDescription();
			buffer = commandName + (const char*)" - " + commandDescription + (const char*)"\n";
			TerminalColors::GreenPrint(buffer.c_str(), false);
			buffer = "";
		}

		buffer += "\nFor help on a certain function, use 'help -l (command)'\n";
		TerminalColors::GreenPrint(buffer.c_str(), false);
	}
	else {
		Command* command = nullptr;
		for (int i=0; i<commands->size(); i++) {
			commandName = (commands->at(i))->GetCommandName();
			if (StringComparisons::StringsAreEqual(commandName.c_str(), toList)) {
				command = commands->at(i);
				break;
			}
		}

		if (command == nullptr) {
			TerminalColors::RedPrint("No command found");
		}
		else {
			//Command name already set
			commandDescription = (*command).GetCommandDescription();
			buffer = commandName + (const char*)" - " + commandDescription + (const char*)"\n";
			TerminalColors::GreenPrint(buffer.c_str());
			const std::vector<const char*>& commandFlags = command->GetFlags();
			const std::vector<const char*>& commandDescriptions = command->GetDescriptions();
			for (int i=0; i<commandFlags.size(); i++) {
				buffer = std::string(commandFlags[i]) + (const char*)" - " + std::string(commandDescriptions[i]);
				TerminalColors::GreenPrint(buffer.c_str());
			}
		}
	}
}

Command* GetHelpCommand() {
	const char* commandName = (char*)"help";
	const char* commandDescription = (char*)"Displays this screen";
	std::vector<const char*> flags {(char*)"-l"};
	unsigned int flagCount = flags.size();
	std::vector<const char*> descriptions {(char*)"Lists properties of a command"};
	void (*onCall)(std::vector<const char*>&, std::vector<const char*>&) = OnHelpCalled;

	Command* command = new Command(commandName, commandDescription, flags, flagCount, descriptions, onCall);

	Command& commandReference = *command;

	return command;
}
