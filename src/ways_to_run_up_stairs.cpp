#include <iostream>
#include <cassert>
#include <vector>
#include <functional>

using namespace std;

int ways_to_run_up(int nstairs) {
	vector<int> memo(nstairs, 0);
	function <int (int)> impl = [&](int n) -> int {
		switch (n) {
		case 1:
			return 1;
		case 2:
			return 2;
		case 3:
			return 4;
		default:
			if (memo[n - 1] == 0) {
				memo[n - 1] = impl(n - 1) + impl(n - 2) + impl(n - 3);
			}
			return memo[n - 1];
		}
	};

	return impl(nstairs);
}

int main() {
	assert(ways_to_run_up(4) == 7);
	cout << "4: " << ways_to_run_up(4) << endl;
	assert(ways_to_run_up(5) == 13);
	cout << "5: " << ways_to_run_up(5) << endl;
	assert(ways_to_run_up(6) == 24);
	cout << "6: " << ways_to_run_up(6) << endl;
	assert(ways_to_run_up(7) == 44);
	cout << "7: " << ways_to_run_up(7) << endl;
}
