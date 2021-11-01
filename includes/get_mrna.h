#ifndef __GET_MRNA_H__
#define __GET_MRNA_H__

#include <vector>

void OnGetMRNACalled(std::vector<const char*>& flagKeys, std::vector<const char*>& flagValues);
Command* GetMRNACommand();

#endif
