#ifndef __AMINO_ACID_H__
#define __AMINO_ACID_H__

#include <converter.h>

namespace AminoAcid {
	enum AminoAcidType {
		AMINO_PHENYL_ALANINE = 0,
		AMINO_LEUCINE = 1,
		AMINO_SERINE = 2,
		AMINO_TYROSINE = 3,
		AMINO_STOP = 4,
		AMINO_CYSTEINE = 5,
		AMINO_TRYPTOPHAN = 6,
		AMINO_PROLINE = 7,
		AMINO_HISTIDINE = 8,
		AMINO_GLUTAMINE = 9,
		AMINO_ARGININE = 10,
		AMINO_ISOLEUCINE = 11,
		AMINO_METHIONINE = 12,
		AMINO_THREONINE = 13,
		AMINO_ASPARAGINE = 14,
		AMINO_LYSINE = 15,
		AMINO_VALINE = 16,
		AMINO_ALANINE = 17,
		AMINO_ASPARTIC_ACID = 18,
		AMINO_GLUTAMIC_ACID = 19,
		AMINO_GLYCINE = 20,
		UNDEFINED = 21
	};

	AminoAcidType GetAminoAcidFromNucleotides(mRNA_Nucleotide base1, mRNA_Nucleotide base2, mRNA_Nucleotide base3);
	void PrintAminoAcid(AminoAcidType aminoAcidType);
}

#endif
