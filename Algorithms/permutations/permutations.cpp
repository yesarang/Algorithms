#include <iostream>
#include <vector>
#include <string>

using namespace std;

void insert_char(string s, char c, vector<string>& vs) {
	for (size_t i = 0; i <= s.size(); ++i) {
		if (i > 0 && s[i - 1] == c) {
			continue;
		}
		string ts(s.substr(0, i));
		ts.push_back(c);
		ts.append(s.substr(i));
		vs.push_back(ts);
	}
}

vector<string> permutations(string s) {
	vector<string> vs;
	if (s.size() == 1) {
		vs.push_back(s);
		return move(vs);
	}

	auto lc = s[s.size() - 1];
	s.pop_back();
	for (auto& ps : permutations(s)) {
		insert_char(ps, lc, vs);
	}

	return move(vs);
}

int main() {
	string s = "abbb";
	for (auto& str : permutations(s)) {
		cout << str << endl;;
	}
}
