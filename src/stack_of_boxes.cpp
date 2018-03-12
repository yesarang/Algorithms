#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

struct box {
	int w_, d_, h_;

	box(int w, int d, int h) : w_(w), d_(d), h_(h) {}
	bool is_stackable_on(const box& other_box) const {
		return other_box.w_ > w_ && other_box.d_ > d_ && other_box.h_ > h_;
	}
};

int max_height_stack_of_boxes(const vector<box>& boxes) {
	vector<int> memo(boxes.size(), 0);
	function <int(int)> impl = [&](int box_id) {
		if (memo[box_id] != 0) {
			return memo[box_id];
		}

		int max_height = 0;
		for (size_t i = 0; i < boxes.size(); ++i) {
			if (i != box_id && boxes[i].is_stackable_on(boxes[box_id])) {
				max_height = max(max_height, impl(i));
			}
		}
		memo[box_id] = max_height + boxes[box_id].h_;
		return memo[box_id];
	};

	int max_height = 0;
	for (size_t i = 0; i < boxes.size(); ++i) {
		max_height = max(max_height, impl(i));
	}

	return max_height;
}

int main() {
	vector<box> boxes{
		box(6,6,6)
	};
	cout << max_height_stack_of_boxes(boxes) << endl;

	boxes.emplace_back(box(5, 5, 5));
	cout << max_height_stack_of_boxes(boxes) << endl;

	boxes.emplace_back(box(3, 3, 3));
	boxes.emplace_back(box(3, 4, 4));
	cout << max_height_stack_of_boxes(boxes) << endl;
}
