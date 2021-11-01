#include <diagnostics.h>
#include <converter.h>

const char* Diagnostics::ConvertDNANucleotideToString(const unsigned char nucleotide) {
	switch(nucleotide) {
		case DNA_ADENINE:
			return "ADENINE";
		case DNA_CYTOSINE:
			return "CYTOSINE";
		case DNA_GUANINE:
			return "GUANINE";
		case DNA_THYMINE:
			return "THYMINE";
	}

	return "";
}

const char* Diagnostics::ConvertMRNANucleotideToString(const unsigned char nucleotide) {
	switch(nucleotide) {
		case MRNA_ADENINE:
			return "ADENINE";
		case MRNA_CYTOSINE:
			return "CYTOSINE";
		case MRNA_GUANINE:
			return "GUANINE";
		case MRNA_URACIL:
			return "URACIL";
	}

	return "";
}