// Design an algorithm to print all permutations of a string. For simplicity, assume all
// characters are unique

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> get_permutations(const string& str) {
	if (str.length() == 1) {
		return vector<string>(1, str);
	}
	else if (str.length() == 2) {
		vector<string> vs;
		vs.push_back(str);
		string t;
		t.push_back(str[1]);
		t.push_back(str[0]);
		vs.push_back(t);
		return vs;
	}

	char last_char = str[str.length() - 1];
	string t(str.begin(), --(str.end()));
	vector<string> perms = get_permutations(t);
	vector<string> ret_perms;
	for (auto s : perms) {
		for (int i = 0; i <= s.length(); ++i) {
			string temp(s);
			temp.insert(i, 1, last_char);
			ret_perms.push_back(temp);
		}
	}

	return ret_perms;
}

int main() {
	string str{ "abcd" };
	vector<string> perms = get_permutations(str);
	for (auto s : perms) {
		cout << s << endl;
	}

	return 0;
}