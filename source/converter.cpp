#include <converter.h>

mRNA_Nucleotide Converter::ConvertToMRNA(int dna) {
	return (mRNA_Nucleotide)dna;
}

mRNA_Nucleotide Converter::ConvertToMRNA(DNA_Nucleotide dna) {
	return (mRNA_Nucleotide)dna;
}

DNA_Nucleotide Converter::ConvertToDNA(int mRNA) {
	return (DNA_Nucleotide)mRNA;
}

DNA_Nucleotide Converter::ConvertToDNA(mRNA_Nucleotide mRNA) {
	return (DNA_Nucleotide)mRNA;
}
