#ifndef __BITPACKER_H__
#define __BITPACKER_H__

#include <converter.h>

namespace Bitpacker {
	/*inline*/ unsigned char AppendNucleotide(const unsigned char toAppend, unsigned char appendTo, unsigned char index);
	/*inline*/ void AppendNucleotideToDNAStream(const unsigned char toAppend, unsigned char* dnaStream, unsigned long index);
	/*inline*/ DNA_Nucleotide GetNucleotide(const unsigned char getFrom, const unsigned char index, bool pushToEnd=false);
	/*inline*/ DNA_Nucleotide GetNucleotideFromDNAStream(const unsigned char* dnaStream, const unsigned long index, bool pushToEnd=false);
	/*inline*/ unsigned char GetBaseFromChar(char character);
};

#endif
