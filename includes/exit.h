#ifndef __EXIT_H__
#define __EXIT_H__

void OnExitCalled(std::vector<const char*>& flagKeys, std::vector<const char*>& flagValues);
Command* GetExitCommand();

#endif
