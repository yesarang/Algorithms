#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

struct person {
	int by;
	int dy;
};

int get_max_alive_year(const vector<person>& people) {
	int deltas[12];
	fill(begin(deltas), end(deltas), 0);

	for (auto& p : people) {
		++deltas[p.by];
		--deltas[p.dy + 1];
	}

	int ret_year = 0;
	int how_many = 0;
	int max_alive = 0;
	for (int i = 0; i < 12; ++i) {
		how_many += deltas[i];
		if (how_many > max_alive) {
			ret_year = i;
			max_alive = how_many;
		}
	}

	return ret_year;
}

int main() {
	vector<person> people{
		person{1,3},
		person{2,3},
		person{4,7},
		person{5,10},
		person{5,9},
		person{7,10},
		person{1,8},
		person{3,5}
	};

	assert(get_max_alive_year(people) == 5);
}