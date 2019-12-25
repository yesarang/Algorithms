#include <string>
#include <cstring>
#include <cassert>

using namespace std;

bool is_substr(const char* substr, const char* str) {
	string s(str);
	return s.find(substr) != std::string::npos;
}

bool is_rotation(const char* o, const char* r) {
	bool found = false;
	const char* b = o;

	while (*o != '\0') {
		if (*o == *r) {
			found = true;
			break;
		}
		++o;
	}
	if (!found) {
		return false;
	}

	while (*o != '\0' && *o++ == *r++);
	if (*o != '\0') {
		return false;
	}

	return is_substr(r, b);
}

int main() {
	const char* o = "abcdef";
	const char* r = "defabc";
	assert(is_rotation(o, r));

	r = "defgabc";
	assert(!is_rotation(o, r));

	r = "abcdef";
	assert(is_rotation(o, r));

	r = "";
	assert(!is_rotation(o, r));
}
