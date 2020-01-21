/*
For a given string s, generate lexicographical permutations.
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void lexi_permute_helper(vector<string>& res, string s, int start)
{
	if (start == s.size() - 1) {
		res.push_back(s);
		return;
	}

	for (int i = start; i < s.size(); ++i) {
		if (i > start) {
			char x = s[i];
			s.erase(s.begin() + i);
			s.insert(s.begin() + start, x);
		}

		lexi_permute_helper(res, s, start + 1);

		if (i > start) {
			char x = s[i];
			s.erase(s.begin() + i);
			s.insert(s.begin() + start, x);
		}
	}
}

vector<string> lexi_permute(string s)
{
	vector<string> vs;
	lexi_permute_helper(vs, s, 0);

	return move(vs);
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& data)
{
	for (auto d : data) {
		cout << d << ",";
	}

	return os;
}

int main()
{
	string s = "123";

	cout << lexi_permute(s) << endl;

	s = "1234";

	cout << lexi_permute(s) << endl;

	s = "12345";

	cout << lexi_permute(s) << endl;
}
