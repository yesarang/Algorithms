// 9.6 Implement an algorithm to print all valid (e.g., properly opened and closed)
// combinations of n - pairs of parentheses.
// EXAMPLE
// Input : 3
// Output : ((())), (()()), (())(), ()(()), ()()()
#include <iostream>
#include <string>

using namespace std;

void print_all_valid_paren_impl(int nopen, int nclose, int nparen, string paren_str) {
	if (nclose == nparen) {
		cout << paren_str << endl;
		return;
	}

	if (nopen == nparen) {
		print_all_valid_paren_impl(nopen, nclose + 1, nparen, paren_str + ")");
	}
	else {
		print_all_valid_paren_impl(nopen + 1, nclose, nparen, paren_str + "(");
		if (nclose < nopen) {
			print_all_valid_paren_impl(nopen, nclose + 1, nparen, paren_str + ")");
		}
	}
}

void print_all_valid_paren(int nparen) {
	print_all_valid_paren_impl(1, 0, nparen, "(");
}

int main() {
	for (int i = 1; i < 5; ++i) {
		print_all_valid_paren(i);
	}

	return 0;
}
