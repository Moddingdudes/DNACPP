#ifndef __GET_PROTEIN_H
#define __GET_PROTEIN_H

#include <vector>

void OnGetProteinCalled(std::vector<const char*>& flagKeys, std::vector<const char*>& flagValues);
Command* GetProteinCommand();

#endif
