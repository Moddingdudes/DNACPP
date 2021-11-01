#ifndef __READ_DNA_H__
#define __READ_DNA_H__

namespace ReadDNA {
	unsigned char* AllocateDNA(const char* fileName, unsigned long& dnaStreamLength, unsigned long& fileSize, unsigned long& compressedSize, bool& isFactorOfThree);
	void PrintFileSize(unsigned int bytes, unsigned int compressedSize);
};
#endif
