#include <iostream>
#include <cassert>
#include <vector>
#include <functional>

using namespace std;

int nways_robot_move(int ex, int ey, const vector<vector<bool>>& off_limits) {
	vector<vector<int>> memo(ex + 1, vector<int>(ey + 1, -1));

	function <int(int, int)> impl = [&](int x, int y) {
		if (x == ex && y == ey) {
			return 1;
		}

		int right_ways = 0;
		if (x < ex) {
			if (memo[x + 1][y] == -1 && !off_limits[x + 1][y]) {
				memo[x + 1][y] = impl(x + 1, y);
			}
			right_ways = memo[x + 1][y] > 0 ? memo[x + 1][y] : 0;
		}

		int down_ways = 0;
		if (y < ey) {
			if (memo[x][y + 1] == -1 && !off_limits[x][y + 1]) {
				memo[x][y + 1] = impl(x, y + 1);
			}
			down_ways = memo[x][y + 1] > 0 ? memo[x][y + 1] : 0;
		}

		return right_ways + down_ways;
	};

	return impl(0, 0);
}

int main() {
	vector<vector<bool>> off_limits2x2(2, vector<bool>(2, false));
	assert(nways_robot_move(1, 1, off_limits2x2) == 2);
	cout << "2x2: " << nways_robot_move(1, 1, off_limits2x2) << endl;

	off_limits2x2[1][0] = true;
	assert(nways_robot_move(1, 1, off_limits2x2) == 1);
	cout << "2x2: " << nways_robot_move(1, 1, off_limits2x2) << endl;

	vector<vector<bool>> off_limits3x3(3, vector<bool>(3, false));
	assert(nways_robot_move(2, 2, off_limits3x3) == 6);
	cout << "3x3: " << nways_robot_move(2, 2, off_limits3x3) << endl;

	off_limits3x3[1][1] = true;
	assert(nways_robot_move(2, 2, off_limits3x3) == 2);
	cout << "3x3: " << nways_robot_move(2, 2, off_limits3x3) << endl;

	off_limits3x3[2][1] = true;
	off_limits3x3[1][1] = false;
	assert(nways_robot_move(2, 2, off_limits3x3) == 3);
	cout << "3x3: " << nways_robot_move(2, 2, off_limits3x3) << endl;

	vector<vector<bool>> off_limits4x4(4, vector<bool>(4, false));
	assert(nways_robot_move(3, 3, off_limits4x4) == 20);
	cout << "4x4: " << nways_robot_move(3, 3, off_limits4x4) << endl;

	off_limits4x4[3][3] = true;
	assert(nways_robot_move(3, 3, off_limits4x4) == 0);
	cout << "4x4: " << nways_robot_move(3, 3, off_limits4x4) << endl;
}
