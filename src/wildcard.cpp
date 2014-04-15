// check out whether this code works properly at http://ideone.com/YUCdSl
#include <iostream>
#include <cassert>
#include <cstdio>

using namespace std;

bool is_matched(const char* str, const char* pat) {
	if (*str == '\0') {
		if (*pat == '\0') {
			return true;
		}
		else {
			return false;
		}
	}

	if (*pat == '?') {
		return is_matched(++str, ++pat);
	}
	else if (*pat == '*') {
		++pat;
		while (*str != *pat) {
			++str;
		}
		return is_matched(str, pat);
	}
	else if (*str == *pat) {
		++str;
		++pat;
		return is_matched(str, pat);
	}
	
	return false;
}

int main() {
	const char* s1 = "aaabc";
	const char* p1 = "a*b";
	const char* p2 = "*bc";
	const char* p3 = "?a?b*";

	assert(!is_matched(s1, p1));
	printf("%s not matched against %s\n", s1, p1);
	assert(is_matched(s1, p2));
	printf("%s matched against %s\n", s1, p2);
	assert(is_matched(s1, p3));
	printf("%s matched against %s\n", s1, p3);

	const char* s2 = "abcd.txt";
	const char* s3 = "aaaa.doc";
	const char* s4 = "bbb.pdf";
	const char* s5 = "ccc.zip";
	const char* p4 = "*.*";
	assert(is_matched(s2, p4));
	printf("%s matched against %s\n", s2, p4);
	assert(is_matched(s3, p4));
	printf("%s matched against %s\n", s3, p4);
	assert(is_matched(s4, p4));
	printf("%s matched against %s\n", s4, p4);
	assert(is_matched(s5, p4));
	printf("%s matched against %s\n", s5, p4);
	
	return 0;
}
