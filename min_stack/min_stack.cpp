#include <iostream>
#include <stack>
#include <cassert>
#include <climits>
#include <algorithm>

using namespace std;

class min_stack {
private:
	stack<int> s_;
	stack<int> mins_;

public:
	min_stack() : s_(), mins_() {}

	void push(int v) {
		s_.push(v);
		if (mins_.empty() || v < mins_.top()) {
			mins_.push(v);
		}
	}

	int top() const {
		return s_.top();
	}

	int min() const {
		return mins_.top();
	}

	void pop() {
		if (s_.top() == mins_.top()) {
			mins_.pop();
		}
		s_.pop();
	}
};

int main() {
	min_stack s;
	int min_val = INT_MAX;
	for (auto v : { 10, 3, 6, 2, 1 }) {
		s.push(v);
		min_val = min(min_val, v);
		assert(s.min() == min_val && s.top() == v);
	}

	// pop 1
	s.pop();
	assert(s.min() == 2);

	// pop 2
	s.pop();
	assert(s.min() == 3);

	// pop 6
	s.pop();
	assert(s.min() == 3);
}
