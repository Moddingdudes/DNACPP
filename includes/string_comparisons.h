#ifndef __STRING_COMPARISONS_H__
#define __STRING_COMPARISONS_H__

#include <string>

namespace StringComparisons {
	bool StringIsNullOrEmpty(const char* string);
	bool StringIsNullOrEmpty(std::string& string);
	bool StringsAreEqual(const char* lhs, const char* rhs);
}

#endif
