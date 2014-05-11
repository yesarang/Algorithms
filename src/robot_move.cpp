// 9.2 Imagine a robot sitting on the upper left corner of an X by Y grid. The robot can
// only move in two directions : right and down. How many possible paths are there
// for the robot to go from(0, 0) to(X, Y) ?
// Imagine certain spots are "off limits," such that the robot cannot step on them.
// Design an algorithm to find How may possible paths for the robot from the top left to the bottom
// right.
#include <iostream>
#include <vector>
#include <cassert>

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

int count_ways_with_obstacles(int sx, int sy, int tx, int ty, const vector<vector<bool>>& obstacles) {
	if (sx == tx && sy == ty) {
		return 1;
	}
	else if (sx == tx && sy < ty) {
		return (obstacles[sx][sy + 1] ? 0 : count_ways_with_obstacles(sx, sy + 1, tx, ty, obstacles));
	}
	else if (sx < tx && sy == ty) {
		return (obstacles[sx + 1][sy] ? 0 : count_ways_with_obstacles(sx + 1, sy, tx, ty, obstacles));
	}
	else {
		return (obstacles[sx + 1][sy] ? 0 : count_ways_with_obstacles(sx + 1, sy, tx, ty, obstacles)) +
			(obstacles[sx][sy + 1] ? 0 : count_ways_with_obstacles(sx, sy + 1, tx, ty, obstacles));
	}
}

int main() {
	for (int i = 1; i < 10; ++i) {
		cout << i << ": " << count_ways(0, 0, i, i) << endl;;
	}

	vector<vector<bool>> obstacles{
		{ false, true },
		{ false, false }
	};
	int ways = count_ways_with_obstacles(0, 0, 1, 1, obstacles);
	assert(ways == 1);
	cout << ways << endl;
	obstacles.clear();

	obstacles.push_back({ false,  true });
	obstacles.push_back({ false, false });
	obstacles.push_back({ false, false });
	ways = count_ways_with_obstacles(0, 0, 2, 1, obstacles);
	assert(ways == 2);
	cout << ways << endl;
	obstacles.clear();

	obstacles.push_back({ false, false, false });
	obstacles.push_back({ false,  true, false });
	obstacles.push_back({ false, false, false });
	ways = count_ways_with_obstacles(0, 0, 2, 2, obstacles);
	assert(ways == 2);
	cout << ways << endl;
	obstacles.clear();

	obstacles.push_back({ false, false, false });
	obstacles.push_back({ false,  true,  true });
	obstacles.push_back({ false, false, false });
	ways = count_ways_with_obstacles(0, 0, 2, 2, obstacles);
	assert(ways == 1);
	cout << ways << endl;
	obstacles.clear();

	obstacles.push_back({ false, false, false });
	obstacles.push_back({ false,  true, false });
	obstacles.push_back({ false, false,  true });
	obstacles.push_back({ false, false, false });
	ways = count_ways_with_obstacles(0, 0, 3, 2, obstacles);
	assert(ways == 2);
	cout << ways << endl;
	obstacles.clear();

	return 0;
}
