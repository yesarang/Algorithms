// 9.2 Imagine a robot sitting on the upper left corner of an X by Y grid. The robot can
// only move in two directions : right and down.How many possible paths are there
// for the robot to go from(0, 0) to(X, Y) ?
#include <iostream>
#include <unordered_map>
#include <climits>

using namespace std;

int count_ways(int sx, int sy, int tx, int ty) {
	if (sx == tx && sy < ty) {
		return 1;
	}
	else if (sx < tx && sy == ty) {
		return 1;
	}
	else {
		return count_ways(sx + 1, sy, tx, ty) +
			   count_ways(sx, sy + 1, tx, ty);
	}
}

int main() {
	for (int i = 1; i < 10; ++i) {
		cout << i << ": " << count_ways(0, 0, i, i) << endl;;
	}

	return 0;
}
