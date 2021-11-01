#ifndef __GET_AMINO_ACID_H__
#define __GET_AMINO_ACID_H__

#include <vector>
#include <amino_acid.h>

void OnGetAminoAcidCalled(std::vector<const char*>& flagKeys, std::vector<const char*>& flagValues);
Command* GetAminoAcidCommand();
AminoAcid::AminoAcidType GetAminoAcidType(unsigned long index, bool suppressWarnings=false);

#endif
