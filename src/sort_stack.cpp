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

	return 0;
}
