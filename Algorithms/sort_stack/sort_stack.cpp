#include <iostream>
#include <stack>

using namespace std;

void sort_stack(stack<int>& s) {
	stack<int> t;

	while (!s.empty()) {
		if (t.empty() || s.top() >= t.top()) {
			t.push(s.top());
			s.pop();
		}
		else {
			auto c = s.top();
			s.pop();
			while (!t.empty() && c < t.top()) {
				s.push(t.top());
				t.pop();
			}
			t.push(c);
		}
	}

	while (!t.empty()) {
		s.push(t.top());
		t.pop();
	}
}

ostream& operator<<(ostream& os, const stack<int>& s) {
	stack<int> t(s);
	while (!t.empty()) {
		os << t.top() << " ";
		t.pop();
	}
	os << endl;

	return os;
}

int main() {
	stack<int> s({ 5,10,3,16,9 });
	sort_stack(s);
	cout << s << endl;
}
