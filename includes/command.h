#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <vector>

class Command {
public:
	Command();
	~Command();
	const char* GetCommandName() const;
	const char* GetCommandDescription() const;
	const std::vector<const char*>& GetFlags() const;
	const std::vector<const char*>& GetDescriptions() const;
	void CallCommandOnCall(std::vector<const char*>& flagKeys, std::vector<const char*>& flagValues);
	Command(const char* commandName, const char* commandDescription, std::vector<const char*> flags, unsigned int flagCount, std::vector<const char*> descriptions, void(*onCall)(std::vector<const char*>&, std::vector<const char*>&));
	void PrintHelp();
private:
	const char* commandName = nullptr;
	const char* commandDescription = nullptr;
	std::vector<const char*> flags;
	unsigned int flagCount;
	std::vector<const char*> descriptions;
	void(*onCall)(std::vector<const char*>&, std::vector<const char*>&);
};

#endif
