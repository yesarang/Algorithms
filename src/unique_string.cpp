// Implement an algorithm to determine if a string has all unique characters.
// What if you cannot use an additional data structures?
// Assume that ascii characters are allowed for simplicity
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

bool is_unique_string(const string& str) {
	unordered_map<char, bool> char_map;
	for (auto c : str) {
		if (char_map[c]) {
			return false;
		}
		else {
			char_map[c] = true;
		}
	};
	return true;
}

bool is_unique_string2(const string& str) {
	for (int i = 0; i < str.length() - 1; ++i) {
		for (int j = i + 1; j < str.length(); ++j) {
			if (str[i] == str[j]) {
				return false;
			}
		}
	}
	return true;
}

int main() {
	string s{ "zabcdeg" };
	assert(is_unique_string(s));
	cout << s << " is unique" << endl;
	assert(is_unique_string2(s));
	cout << s << " is unique" << endl;

	s = "abcdd";
	assert(!is_unique_string(s));
	cout << s << " is not unique" << endl;
	assert(!is_unique_string2(s));
	cout << s << " is not unique" << endl;

	return 0;
}
