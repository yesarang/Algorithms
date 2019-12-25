#include <iostream>
#include <string>
#include <numeric>

using namespace std;

void urlify(string& in, size_t sz) {
	int nspace = 0;
	for (auto c : in) {
		if (c == ' ') {
			++nspace;
		}
	}
	int new_next = sz + nspace * 2 - 1;
	for (int next = sz - 1; next >= 0 && next < new_next; --next) {
		if (in[next] == ' ') {
			in[new_next--] = '0';
			in[new_next--] = '2';
			in[new_next--] = '%';
		}
		else {
			in[new_next--] = in[next];
		}
	}
}

int main() {
	string s = "Mr John Smith   ";
	auto sz = s.size();
	s.resize(sz + 10);
	urlify(s, sz);

	cout << s << endl;
}
