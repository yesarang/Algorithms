#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

char* convert_space(char* s, int len, int sz) {
	int input_pos = len - 1;
	int output_pos = sz - 1;

	while (input_pos >= 0) {
		if (s[input_pos] != ' ') {
			s[output_pos--] = s[input_pos--];
		}
		else {
			s[output_pos--] = '0';
			s[output_pos--] = '2';
			s[output_pos--] = '%';
			--input_pos;
		}
	}

	return s;
}

int main() {
	char str[17]{"Kim Yoon Soo"};
	str[16] = '\0';
	char* converted = convert_space(str, strlen("Kim Yoon Soo"), sizeof(str) - 1);
	assert(strcmp(converted, "Kim%20Yoon%20Soo") == 0);
	cout << str << " --> " << converted << endl;

	return 0;
}
