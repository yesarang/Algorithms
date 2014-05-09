// 9.1 A child is running up a staircase with n steps, and can hop either 1 step, 2 steps,
// or 3 steps at a time.Implement a method to count how many possible ways the
// child can run up the stairs.
#include <iostream>
#include <unordered_map>

using namespace std;

unsigned count_ways(int n, unordered_map<int, unsigned>& map) {
	if (n < 0) {
		return 0;
	}
	else if (n == 0) {
		return 1;
	}
	else if (map[n] > 0) {
		return map[n];
	}
	else {
		map[n] = count_ways(n - 1, map) + count_ways(n - 2, map) + count_ways(n - 3, map);
		return map[n];
	}
}

int main() {
	unordered_map<int, unsigned> map;
	for (int i = 1; i < 30; ++i) {
		cout << count_ways(i, map) << endl;
	}

	return 0;
}
