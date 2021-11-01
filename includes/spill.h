#ifndef __SPILL_H__
#define __SPILL_H__

#include <vector>

void OnSpillCalled(std::vector<const char*>& flagKeys, std::vector<const char*>& flagValues);
Command* GetSpillCommand();

#endif
