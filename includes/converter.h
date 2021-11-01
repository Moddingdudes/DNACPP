#ifndef __CONVERTER_H__
#define __CONVERTER_H__

enum DNA_Nucleotide {
	DNA_ADENINE = 0,
	DNA_CYTOSINE = 1,
	DNA_GUANINE = 3,
	DNA_THYMINE = 2
};

enum mRNA_Nucleotide {
	MRNA_URACIL = 0,
	MRNA_GUANINE = 1,
	MRNA_CYTOSINE = 3,
	MRNA_ADENINE = 2
};

class Converter {
public:
	inline static mRNA_Nucleotide ConvertToMRNA(int dna);
	inline static mRNA_Nucleotide ConvertToMRNA(DNA_Nucleotide dna);
	inline static DNA_Nucleotide ConvertToDNA(int mRNA);
	inline static DNA_Nucleotide ConvertToDNA(mRNA_Nucleotide mRNA);
};

#endif
