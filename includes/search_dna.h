#ifndef __SEARCH_DNA_H__
#define __SEARCH_DNA_H__

#include <vector>

void OnSearchDNACalled(std::vector<const char*>& flagKeys, std::vector<const char*>& flagValues);
Command* GetSearchDNACommand();

#endif
