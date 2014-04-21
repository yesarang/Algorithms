#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cassert>

using namespace std;

string compress_string(const string& str) {
	if (str.empty())  {
		return str;
	}

	string new_str;
	char current_char = str[0];
	int cnt = 1;
	char buf[20];

	for (unsigned i = 1; i < str.length(); ++i) {
		if (current_char == str[i]) {
			++cnt;
		}
		else {
			sprintf_s(buf, "%d", cnt);
			if (new_str.length() + 1 + strlen(buf) > str.length()) {
				return str;
			}
			new_str.push_back(current_char);
			new_str += buf;
			current_char = str[i];
			cnt = 1;
		}
	}
	sprintf_s(buf, "%d", cnt);
	if (new_str.length() + 1 + strlen(buf) > str.length()) {
		return str;
	}
	new_str.push_back(current_char);
	new_str += buf;

	return new_str;
}

string quote(const string& s) {
	return "\"" + s + "\"";
}

int main() {
	string s1{ "" };
	string s2{ "a" };
	string s3{ "aa" };
	string s4{ "abbc" };
	string s5{ "aaaabbbbcccd" };

	assert(compress_string(s1) == s1);
	cout << quote(s1) << " --> " << quote(compress_string(s1)) << endl;

	assert(compress_string(s2) == s2);
	cout << quote(s2) << " --> " << quote(compress_string(s2)) << endl;

	assert(compress_string(s3) == "a2");
	cout << quote(s3) << " --> " << quote(compress_string(s3)) << endl;

	assert(compress_string(s4) == s4);
	cout << quote(s4) << " --> " << quote(compress_string(s4)) << endl;

	assert(compress_string(s5) == "a4b4c3d1");
	cout << quote(s5) << " --> " << quote(compress_string(s5)) << endl;

	return 0;
}
