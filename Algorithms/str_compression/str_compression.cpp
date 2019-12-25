#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string str_comp(const string& in) {
	auto output = [](string& r, char ch, int cnt) {
		r.push_back(ch);
		ostringstream strm;
		strm << cnt;
		r.append(strm.str());
	};

	string r;
	r.reserve(in.size());

	char ch = in[0];
	int cnt = 1;
	for (size_t i = 1; i < in.size(); ++i) {
		if (in[i] == ch) {
			++cnt;
		}
		else {
			output(r, ch, cnt);
			ch = in[i];
			cnt = 1;
		}
	}
	output(r, ch, cnt);

	return r.size() < in.size() ? r : in;
}

int main() {
	string s = "aaabcccccddd";
	cout << str_comp(s) << endl;

	s = "aaaaaaaaaaaabcdefggggg";
	cout << str_comp(s) << endl;

	s = "abcdef";
	cout << str_comp(s) << endl;
}
