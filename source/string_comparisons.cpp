#include <string_comparisons.h>
#include <cstring>

bool StringComparisons::StringIsNullOrEmpty(const char* string) {
	return (*string == '\0') || (string == NULL);
}

bool StringComparisons::StringIsNullOrEmpty(std::string& string) {
	return string.empty(); //References cannot be null. No null check required
}

bool StringComparisons::StringsAreEqual(const char* lhs, const char* rhs) {
	return strncmp(lhs, rhs, strlen(rhs)) == 0;
}
