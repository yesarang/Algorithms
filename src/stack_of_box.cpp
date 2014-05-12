// 9.10 You have a stack of n boxes, with widths w, heights h and depths d. The boxes
// cannot be rotated and can only be stacked on top of one another if each box
// in the stack is strictly larger than the box above it in width, height, and depth.
// Implement a method to build the tallest stack possible, where the height of a
// stack is the sum of the heights of each box.
#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
#include <algorithm>
#include <climits>
#include <utility>

using namespace std;

struct Box {
	int w, d, h;
};

int get_max_height_impl(const vector<Box>& boxes, stack<Box>& stack_of_boxes) {
	int max_height = 0;
	for (auto b : boxes) {
		if (b.w < stack_of_boxes.top().w &&
			b.d < stack_of_boxes.top().d) {
			vector<Box> new_boxes(boxes);
			auto new_end = remove_if(new_boxes.begin(), new_boxes.end(), [b](const Box& nb) {
				return nb.w == b.w && nb.d == b.d && nb.h == b.h;
			});
			new_boxes.erase(new_end, new_boxes.end());
			stack_of_boxes.push(b);
			max_height = max(b.h + get_max_height_impl(new_boxes, stack_of_boxes), max_height);
			stack_of_boxes.pop();
		}
	}
	return max_height;
}

int get_max_height(const vector<Box>& boxes) {
	stack<Box> stack_of_boxes;
	stack_of_boxes.push({ INT_MAX, INT_MAX, 0 });
	return get_max_height_impl(boxes, stack_of_boxes);
}

pair<stack<Box>, int> get_tallest_stack_impl(const vector<Box>& boxes, stack<Box>& stack_of_boxes) {
	stack<Box> ret_stack = stack_of_boxes;
	int max_height = 0;
	for (auto b : boxes) {
		if (b.w < stack_of_boxes.top().w &&
			b.d < stack_of_boxes.top().d) {
			vector<Box> new_boxes(boxes);
			auto new_end = remove_if(new_boxes.begin(), new_boxes.end(), [b](const Box& nb) {
				return nb.w == b.w && nb.d == b.d && nb.h == b.h;
			});
			new_boxes.erase(new_end, new_boxes.end());
			stack_of_boxes.push(b);
			pair<stack<Box>, int> ret = get_tallest_stack_impl(new_boxes, stack_of_boxes);
			int height = b.h + ret.second;
			if (height > max_height) {
				max_height = height;
				ret_stack = ret.first;
			}
			stack_of_boxes.pop();
		}
	}
	return { ret_stack, max_height };
}

stack<Box> get_tallest_stack(const vector<Box>& boxes) {
	stack<Box> stack_of_boxes;
	stack_of_boxes.push({ INT_MAX, INT_MAX, 0 });
	pair<stack<Box>, int> ret = get_tallest_stack_impl(boxes, stack_of_boxes);
	stack<Box> temp;
	while (!ret.first.empty()) {
		if (ret.first.top().w != INT_MAX) {
			temp.push(ret.first.top());
		}
		ret.first.pop();
	}
	while (!temp.empty()) {
		ret.first.push(temp.top());
		temp.pop();
	}

	return ret.first;
}

ostream& operator<<(ostream& os, const Box& b) {
	os << "(" << b.w << "," << b.d << "," << b.h << ")";
	return os;
}

void print_stack(stack<Box> sb) {
	while (!sb.empty()) {
		cout << sb.top() << endl;
		sb.pop();
	}
}

int main() {
	vector<Box> boxes{
		{ 1, 1, 3 }
	};

	int max_height = get_max_height(boxes);
	cout << max_height << endl;
	print_stack(get_tallest_stack(boxes));
	assert(max_height == 3);

	boxes.push_back({ 2, 2, 1 });
	boxes.push_back({ 3, 3, 1 });
	max_height = get_max_height(boxes);
	cout << max_height << endl;
	print_stack(get_tallest_stack(boxes));
	assert(max_height == 5);

	boxes.push_back({ 1, 2, 5 });
	max_height = get_max_height(boxes);
	cout << max_height << endl;
	print_stack(get_tallest_stack(boxes));
	assert(max_height == 6);

	return 0;
}

