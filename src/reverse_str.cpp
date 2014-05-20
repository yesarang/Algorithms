#include <iostream>

using namespace std;

void reverse(char* str, int s, int e) {
	if (s >= e) {
		return;
	}
	char t = str[s];
	str[s] = str[e];
	str[e] = t;
	reverse(str, ++s, --e);
}

void reverse(char* str) {
	reverse(str, 0, strlen(str) - 1);
}

void word_reverse(char* str) {
	reverse(str);
	int ws = 0;
	int we = 0;
	while (str[we] != '\0') {
		while (str[we] != ' ' && str[we] != '\0') ++we;
		if (str[we] == '\0')
			break;
		reverse(str, ws, we - 1);
		++we;
		ws = we;
	}
	reverse(str, ws, we - 1);
}

int main() {
	char str[] = "Welcome to LG";
	reverse(str);
	cout << str << endl;
	char str1[] = "Welcome to LG";
	word_reverse(str1);
	cout << str1 << endl;
	return 0;
}
