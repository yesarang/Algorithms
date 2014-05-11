// 9.2 Imagine a robot sitting on the upper left corner of an X by Y grid. The robot can
// only move in two directions : right and down. How many possible paths are there
// for the robot to go from(0, 0) to(X, Y) ?
// 9.2-1 Imagine certain spots are "off limits," such that the robot cannot step on them.
// Design an algorithm to find How may possible paths for the robot from the top left to the bottom
// right.
// 9.2-2 Imagine certain spots are "off limits," such that the robot cannot step on them.
// Design an algorithm to find a path for the robot from the top left to the bottom
// right.
#include <iostream>
#include <vector>
#include <cassert>
#include <deque>

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

struct Cell {
	int x;
	int y;
};

ostream& operator<<(ostream& os, const Cell& c) {
	cout << "(" << c.x << "," << c.y << ") ";
	return os;
}

bool get_path_with_obstacles(Cell s, const Cell& t, const vector<vector<bool>>& obstacles, deque<Cell>& path) {
	if (s.x == t.x && s.y == t.y) {
		path.push_back(s);
		return true;
	}
	else if (s.x == t.x && s.y < t.y) {
		if (obstacles[s.x][s.y + 1]) {
			return false;
		}
		else {
			path.push_back(s);
			if (get_path_with_obstacles({ s.x, s.y + 1 }, t, obstacles, path)) {
				return true;
			}
			else {
				path.pop_back();
				return false;
			}
		}
	}
	else if (s.x < t.x && s.y == t.y) {
		if (obstacles[s.x + 1][s.y]) {
			return false;
		}
		else {
			path.push_back(s);
			if (get_path_with_obstacles({ s.x + 1, s.y }, t, obstacles, path)) {
				return true;
			}
			else {
				path.pop_back();
				return false;
			}
		}
	}
	else {
		// Check downward path first
		if (!obstacles[s.x + 1][s.y]) {
			path.push_back(s);
			if (get_path_with_obstacles({ s.x + 1, s.y }, t, obstacles, path)) {
				return true;
			}
			else {
				path.pop_back();
			}
		}
		// Check right path second
		if (!obstacles[s.x][s.y + 1]) {
			path.push_back(s);
			if (get_path_with_obstacles({ s.x, s.y + 1 }, t, obstacles, path)) {
				return true;
			}
			else {
				path.pop_back();
				return false;
			}
		}
		else {
			return false;
		}
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

	obstacles.push_back({ false, false, false });
	obstacles.push_back({ false,  true, false });
	obstacles.push_back({ false, false,  true });
	obstacles.push_back({  true, false, false });
	deque<Cell> path;
	bool path_exist = get_path_with_obstacles({ 0, 0 }, { 3, 2 }, obstacles, path);
	for (auto c : path) {
		cout << c;
	}
	cout << endl;
	obstacles.clear();
	path.clear();

	obstacles.push_back({ false, false, false });
	obstacles.push_back({ false,  true, false });
	obstacles.push_back({ false,  true, false });
	obstacles.push_back({  true, false, false });
	path_exist = get_path_with_obstacles({ 0, 0 }, { 3, 2 }, obstacles, path);
	for (auto c : path) {
		cout << c;
	}
	cout << endl;
	obstacles.clear();
	path.clear();

	obstacles.push_back({ false,  true });
	obstacles.push_back({  true, false });
	path_exist = get_path_with_obstacles({ 0, 0 }, { 1, 1 }, obstacles, path);
	for (auto c : path) {
		cout << c;
	}
	cout << endl;
	obstacles.clear();
	path.clear();
	return 0;
}
