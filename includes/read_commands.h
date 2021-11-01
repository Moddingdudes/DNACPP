#ifndef __READ_COMMANDS_H__
#define __READ_COMMANDS_H__

#include <vector>
#include <command.h>

namespace ReadCommands {
	void Init();
	void ReadCommand(const char* commandString);
	void GetCommandFlags(const char* commandString, unsigned int& flagCount, std::vector<const char*>*& commandFlagKeys, std::vector<const char*>*& commandFlagValues, const char*& commandName);
}

#endif
