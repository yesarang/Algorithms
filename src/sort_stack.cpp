// Write a program to sort a stack in ascending order(with biggest items on top).
// You may use at most one additional stack to hold items, but you may not copy the
// elements into any other data structure(such as an array).The stack supports the
// following operations : push, pop, peek, and isEmpty.
#include <iostream>
#include <stack>

using namespace std;

void sort_stack(stack<int>& s) {
	int nstack = s.size();
	int nsorted = 0;
	stack<int> ts;
	while (nsorted < nstack) {
		int min = s.top();
		s.pop();
		for (int i = 0; i < nstack - nsorted - 1; ++i) {
			if (s.top() < min) {
				ts.push(min);
				min = s.top();
			}
			else {
				ts.push(s.top());
			}
			s.pop();
		}
		s.push(min);
		for (int i = 0; i < nstack - nsorted - 1; ++i) {
			s.push(ts.top());
			ts.pop();
		}
		++nsorted;
	}
}

void sort_stack2(stack<int>& s) {
	stack<int> ts;
	ts.push(s.top());
	s.pop();
	while (!s.empty()) {
		int need_pop = 0;
		int temp = s.top();
		s.pop();
		while (!ts.empty() && temp > ts.top()) {
			s.push(ts.top());
			ts.pop();
			++need_pop;
		}
		ts.push(temp);
		while (need_pop > 0) {
			ts.push(s.top());
			s.pop();
			--need_pop;
		}
	}
	while (!ts.empty()) {
		s.push(ts.top());
		ts.pop();
	}
}

int main() {
	stack<int> s;
	for (auto i : { 7, 4, 5, -1, 9, 11 }) {
		s.push(i);
	}

	sort_stack(s);
	while (!s.empty()) {
		cout << s.top() << endl;
		s.pop();
	}

	for (auto i : { 7, 4, 5, -1, 9, 11 }) {
		s.push(i);
	}
	sort_stack2(s);
	while (!s.empty()) {
		cout << s.top() << endl;
		s.pop();
	}

	return 0;
}
