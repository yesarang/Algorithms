#include <iostream>
#include <string>
#include <cmath>
#include <cassert>
#include <functional>
#include <cstdlib>

using namespace std;

/*
bool is_one_edit_away(const string& a, const string& b) {
	auto is_same = [](const string& a, size_t ai, const string& b, size_t bi) {
		if ((a.size() - ai) != (b.size() - bi)) {
			return false;
		}

		while (ai < a.size()) {
			if (a[ai++] != b[bi++]) {
				return false;
			}
		}

		return true;
	};

	if (abs((int)a.size() - (int)b.size()) > 1) {
		return false;
	}

	size_t ai = 0, bi = 0;
	while (ai < a.size() && bi < b.size()) {
		if (a[ai] != b[bi]) {
			break;
		}
		++ai, ++bi;
	}

	return
		is_same(a, ai, b, bi + 1) ||		// insert
		is_same(a, ai + 1, b, bi) ||		// remove
		is_same(a, ai + 1, b, bi + 1);		// replace
}
*/

auto is_same_str = [](const char* a, const char* b) {
	return strcmp(a, b) == 0;
};

bool is_one_edit_away(const char* a, const char* b) {
	if (*a == '\0' || *b == '\0') {
		return abs((long)strlen(a) - (long)strlen(b)) <= 1;
	}

	if (*a == *b) {
		return is_one_edit_away(a + 1, b + 1);
	}
	else {
		return is_same_str(a, b + 1) ||		// insert
			is_same_str(a + 1, b) ||		// remove
			is_same_str(a + 1, b + 1);		// replace
	}
}

int main() {
	assert(is_one_edit_away("pale", "ple"));
	assert(is_one_edit_away("pales", "pale"));
	assert(is_one_edit_away("pale", "bale"));
	assert(!is_one_edit_away("pale", "bake"));
	assert(is_one_edit_away("", ""));
	assert(!is_one_edit_away("", "bb"));
}
