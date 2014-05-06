#include <iostream>
#include <vector>
#include <cassert>
#include <stdexcept>

using namespace std;

class Stack {
private:
	vector<int> data_stack_;
	vector<int> min_stack_;

public:
	int pop();
	void push(int data);
	int min();
};

int Stack::pop() {
	if (data_stack_.empty()) {
		throw underflow_error("Underflow");
	}
	int ret = data_stack_.back();
	data_stack_.pop_back();
	min_stack_.pop_back();
	return ret;
}

void Stack::push(int data) {
	data_stack_.push_back(data);
	if (min_stack_.empty() || data < min()) {
		min_stack_.push_back(data_stack_.size() - 1);
	}
	else {
		min_stack_.push_back(min_stack_.back());
	}
}

int Stack::min() {
	if (data_stack_.empty()) {
		throw underflow_error("Underflow");
	}
	return data_stack_[min_stack_.back()];
}

int main() {
	Stack s;
	s.push(7);
	cout << s.min() << endl;
	assert(s.min() == 7);
	s.push(5);
	cout << s.min() << endl;
	assert(s.min() == 5);
	s.push(9);
	cout << s.min() << endl;
	assert(s.min() == 5);
	s.push(-1);
	cout << s.min() << endl;
	assert(s.min() == -1);
	s.push(4);
	cout << s.min() << endl;
	assert(s.min() == -1);
	s.push(11);
	cout << s.min() << endl;
	assert(s.min() == -1);

	s.pop();
	cout << s.min() << endl;
	assert(s.min() == -1);
	s.pop();
	cout << s.min() << endl;
	assert(s.min() == -1);
	s.pop();
	cout << s.min() << endl;
	assert(s.min() == 5);
	s.pop();
	cout << s.min() << endl;
	assert(s.min() == 5);
	s.pop();
	cout << s.min() << endl;
	assert(s.min() == 7);

	try {
		s.pop();
		cout << s.min() << endl;
		assert(s.min() == -1);
	}
	catch (const underflow_error& ex) {
		cout << ex.what() << endl;
	}

	return 0;
}
