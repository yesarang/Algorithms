#include <iostream>
#include <string>
#include <functional>

using namespace std;

bool is_matched(const string& str, const string& pat) {
	auto advance_str = [&](size_t i, char upto) {
		while (i < str.size() && str[i] != upto) {
			++i;
		}

		return i == str.size() ? make_tuple(false, i) : make_tuple(true, i);
	};

	function<bool (size_t, size_t)> match_helper =
	[&](size_t i, size_t j) {
 		if (j == pat.size()) {
			return i == str.size();
		}

		// '*' is looked ahead. just need to check '.' or 'a' - 'z'
		if (pat[j] == '.') {
			if (j + 1 < pat.size() && pat[j + 1] == '*') {
				// pat: '.*'
				if (j + 2 == pat.size()) {
					// if no more patter chars are left after .*
					// any remaining chars in str can be matched.
					return true;
				}
				else {
					auto [found, ni] = advance_str(i, pat[j + 2]);
					return found && match_helper(ni, j + 2);
				}
			}
			else {
				// any character match
				return match_helper(i + 1, j + 1);
			}
		}
		else {
			// 'a' - 'z'
			if (j + 1 < pat.size() && pat[j + 1] == '*') { // a* - z*
				while (i < str.size() && str[i] == pat[j]) {
					++i;
				}
				return match_helper(i, j + 2);
			}
			else {
				// one character match
				return str[i] == pat[j] && match_helper(i + 1, j + 1);
			}
		}
	};

	return match_helper(0, 0);
}

int main() {
	string str = "aaa";
	string pat = "a*a";

	if (is_matched(str, pat)) {
		cout << str << " is matched to " << pat << endl;
	}
	else {
		cout << str << " is not matched to " << pat << endl;
	}

	str = "abbc";
	pat = "ab*c";
	if (is_matched(str, pat)) {
		cout << str << " is matched to " << pat << endl;
	}
	else {
		cout << str << " is not matched to " << pat << endl;
	}

	str = "ac";
	if (is_matched(str, pat)) {
		cout << str << " is matched to " << pat << endl;
	}
	else {
		cout << str << " is not matched to " << pat << endl;
	}

	str = "aa";
	pat = "a*";
	if (is_matched(str, pat)) {
		cout << str << " is matched to " << pat << endl;
	}
	else {
		cout << str << " is not matched to " << pat << endl;
	}

	str = "mississippi";
	pat = "mis*is*p*.";
	if (is_matched(str, pat)) {
		cout << str << " is matched to " << pat << endl;
	}
	else {
		cout << str << " is not matched to " << pat << endl;
	}

	str = "abd";
	pat = ".*c";
	if (is_matched(str, pat)) {
		cout << str << " is matched to " << pat << endl;
	}
	else {
		cout << str << " is not matched to " << pat << endl;
	}

	str = "abc";
	pat = ".*c";
	if (is_matched(str, pat)) {
		cout << str << " is matched to " << pat << endl;
	}
	else {
		cout << str << " is not matched to " << pat << endl;
	}

	str = "ab";
	pat = ".*";
	if (is_matched(str, pat)) {
		cout << str << " is matched to " << pat << endl;
	}
	else {
		cout << str << " is not matched to " << pat << endl;
	}

	str = "abx";
	pat = ".*.";
	if (is_matched(str, pat)) {
		cout << str << " is matched to " << pat << endl;
	}
	else {
		cout << str << " is not matched to " << pat << endl;
	}
}
