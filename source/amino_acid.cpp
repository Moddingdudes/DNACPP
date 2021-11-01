#include <amino_acid.h>
#include <converter.h>
#include <iostream>
#include <cstring>
#include <terminal_colors.h>

namespace AminoAcid {

AminoAcidType GetAminoAcidFromNucleotides(mRNA_Nucleotide base1, mRNA_Nucleotide base2, mRNA_Nucleotide base3) {
	if (base1 == MRNA_URACIL) {
		if (base2 == MRNA_URACIL) {
			if (base3 == MRNA_URACIL) {
				return AMINO_PHENYL_ALANINE;
			}
			if (base3 == MRNA_CYTOSINE) {
				return AMINO_PHENYL_ALANINE;
			}
			if (base3 == MRNA_ADENINE) {
				return AMINO_LEUCINE;
			}
			if (base3 == MRNA_GUANINE) {
				return AMINO_LEUCINE;
			}
		}
		if (base2 == MRNA_CYTOSINE) {
			if (base3 == MRNA_URACIL) {
				return AMINO_SERINE;
			}
			if (base3 == MRNA_CYTOSINE) {
				return AMINO_SERINE;
			}
			if (base3 == MRNA_ADENINE) {
				return AMINO_SERINE;
			}
			if (base3 == MRNA_GUANINE) {
				return AMINO_SERINE;
			}
		}
		if (base2 == MRNA_ADENINE) {
			if (base3 == MRNA_URACIL) {
				return AMINO_TYROSINE;
			}
			if (base3 == MRNA_CYTOSINE) {
				return AMINO_TYROSINE;
			}
			if (base3 == MRNA_ADENINE) {
				return AMINO_STOP;
			}
			if (base3 == MRNA_GUANINE) {
				return AMINO_STOP;
			}
		}
		if (base2 == MRNA_GUANINE) {
			if (base3 == MRNA_URACIL) {
				return AMINO_CYSTEINE;
			}
			if (base3 == MRNA_CYTOSINE) {
				return AMINO_CYSTEINE;
			}
			if (base3 == MRNA_ADENINE) {
				return AMINO_STOP;
			}
			if (base3 == MRNA_GUANINE) {
				return AMINO_TRYPTOPHAN;
			}
		}
	}

	if (base1 == MRNA_CYTOSINE) {
		if (base2 == MRNA_URACIL) {
			if (base3 == MRNA_URACIL) {
				return AMINO_LEUCINE;
			}
			if (base3 == MRNA_CYTOSINE) {
				return AMINO_LEUCINE;
			}
			if (base3 == MRNA_ADENINE) {
				return AMINO_LEUCINE;
			}
			if (base3 == MRNA_GUANINE) {
				return AMINO_LEUCINE;
			}
		}
		if (base2 == MRNA_CYTOSINE) {
			if (base3 == MRNA_URACIL) {
				return AMINO_PROLINE;
			}
			if (base3 == MRNA_CYTOSINE) {
				return AMINO_PROLINE;
			}
			if (base3 == MRNA_ADENINE) {
				return AMINO_PROLINE;
			}
			if (base3 == MRNA_GUANINE) {
				return AMINO_PROLINE;
			}
		}
		if (base2 == MRNA_ADENINE) {
			if (base3 == MRNA_URACIL) {
				return AMINO_HISTIDINE;
			}
			if (base3 == MRNA_CYTOSINE) {
				return AMINO_HISTIDINE;
			}
			if (base3 == MRNA_ADENINE) {
				return AMINO_GLUTAMINE;
			}
			if (base3 == MRNA_GUANINE) {
				return AMINO_GLUTAMINE;
			}
		}
		if (base2 == MRNA_GUANINE) {
			if (base3 == MRNA_URACIL) {
				return AMINO_ARGININE;
			}
			if (base3 == MRNA_CYTOSINE) {
				return AMINO_ARGININE;
			}
			if (base3 == MRNA_ADENINE) {
				return AMINO_ARGININE;
			}
			if (base3 == MRNA_GUANINE) {
				return AMINO_ARGININE;
			}
		}
	}

	if (base1 == MRNA_ADENINE) {
		if (base2 == MRNA_URACIL) {
			if (base3 == MRNA_URACIL) {
				return AMINO_ISOLEUCINE;
			}
			if (base3 == MRNA_CYTOSINE) {
				return AMINO_ISOLEUCINE;
			}
			if (base3 == MRNA_ADENINE) {
				return AMINO_ISOLEUCINE;
			}
			if (base3 == MRNA_GUANINE) {
				return AMINO_METHIONINE;
			}
		}
		if (base2 == MRNA_CYTOSINE) {
			if (base3 == MRNA_URACIL) {
				return AMINO_THREONINE;
			}
			if (base3 == MRNA_CYTOSINE) {
				return AMINO_THREONINE;
			}
			if (base3 == MRNA_ADENINE) {
				return AMINO_THREONINE;
			}
			if (base3 == MRNA_GUANINE) {
				return AMINO_THREONINE;
			}
		}
		if (base2 == MRNA_ADENINE) {
			if (base3 == MRNA_URACIL) {
				return AMINO_ASPARAGINE;
			}
			if (base3 == MRNA_CYTOSINE) {
				return AMINO_ASPARAGINE;
			}
			if (base3 == MRNA_ADENINE) {
				return AMINO_LYSINE;
			}
			if (base3 == MRNA_GUANINE) {
				return AMINO_LYSINE;
			}
		}
		if (base2 == MRNA_GUANINE) {
			if (base3 == MRNA_URACIL) {
				return AMINO_SERINE;
			}
			if (base3 == MRNA_CYTOSINE) {
				return AMINO_SERINE;
			}
			if (base3 == MRNA_ADENINE) {
				return AMINO_ARGININE;
			}
			if (base3 == MRNA_GUANINE) {
				return AMINO_ARGININE;
			}
		}
	}

	if (base1 == MRNA_GUANINE) {
		if (base2 == MRNA_URACIL) {
			if (base3 == MRNA_URACIL) {
				return AMINO_VALINE;
			}
			if (base3 == MRNA_CYTOSINE) {
				return AMINO_VALINE;
			}
			if (base3 == MRNA_ADENINE) {
				return AMINO_VALINE;
			}
			if (base3 == MRNA_GUANINE) {
				return AMINO_VALINE;
			}
		}
		if (base2 == MRNA_CYTOSINE) {
			if (base3 == MRNA_URACIL) {
				return AMINO_ALANINE;
			}
			if (base3 == MRNA_CYTOSINE) {
				return AMINO_ALANINE;
			}
			if (base3 == MRNA_ADENINE) {
				return AMINO_ALANINE;
			}
			if (base3 == MRNA_GUANINE) {
				return AMINO_ALANINE;
			}
		}
		if (base2 == MRNA_ADENINE) {
			if (base3 == MRNA_URACIL) {
				return AMINO_ASPARTIC_ACID;
			}
			if (base3 == MRNA_CYTOSINE) {
				return AMINO_ASPARTIC_ACID;
			}
			if (base3 == MRNA_ADENINE) {
				return AMINO_GLUTAMIC_ACID;
			}
			if (base3 == MRNA_GUANINE) {
				return AMINO_GLUTAMIC_ACID;
			}
		}
		if (base2 == MRNA_GUANINE) {
			if (base3 == MRNA_URACIL) {
				return AMINO_GLYCINE;
			}
			if (base3 == MRNA_CYTOSINE) {
				return AMINO_GLYCINE;
			}
			if (base3 == MRNA_ADENINE) {
				return AMINO_GLYCINE;
			}
			if (base3 == MRNA_GUANINE) {
				return AMINO_GLYCINE;
			}
		}
	}

	return AMINO_SERINE; //Default, should never happen

}

void PrintAminoAcid(AminoAcidType aminoAcidType) {
	std::string output = "No output...";
	switch(aminoAcidType) {
		case AMINO_PHENYL_ALANINE:
			output = "PHENYL_ALANINE";
			break;
		case AMINO_LEUCINE:
			output = "LEUCINE";
			break;
		case AMINO_SERINE:
			output = "SERINE";
			break;
		case AMINO_TYROSINE:
			output = "TYROSINE";
			break;
		case AMINO_STOP:
			output = "STOP";
			break;
		case AMINO_CYSTEINE:
			output = "CYSTEINE";
			break;
		case AMINO_TRYPTOPHAN:
			output = "TRYPTOPHAN";
			break;
		case AMINO_PROLINE:
			output = "PROLINE";
			break;
		case AMINO_HISTIDINE:
			output = "HISTIDINE";
			break;
		case AMINO_GLUTAMINE:
			output = "GLUTAMINE";
			break;
		case AMINO_ARGININE:
			output = "ARGININE";
			break;
		case AMINO_ISOLEUCINE:
			output = "ISOLEUCINE";
			break;
		case AMINO_METHIONINE:
			output = "METHIONINE";
			break;
		case AMINO_THREONINE:
			output = "THREONINE";
			break;
		case AMINO_ASPARAGINE:
			output = "ASPARAGINE";
			break;
		case AMINO_LYSINE:
			output = "LYSINE";
			break;
		case AMINO_VALINE:
			output = "VALINE";
			break;
		case AMINO_ALANINE:
			output = "ALANINE";
			break;
		case AMINO_ASPARTIC_ACID:
			output = "ASPARTIC_ACID";
			break;
		case AMINO_GLUTAMIC_ACID:
			output = "GLUTAMIC_ACID";
			break;
		case AMINO_GLYCINE:
			output = "GLYCINE";
			break;
		case UNDEFINED:
			output = "UNDEFINED";
			break;
	}

	TerminalColors::GreenPrint(output.c_str(), false);
}

}
