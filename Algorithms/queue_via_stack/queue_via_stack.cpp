#include <iostream>
#include <stack>
#include <tuple>

using namespace std;

class MyQueue {
private:
	stack<int> in_stack_;
	stack<int> out_stack_;

	int dequeue_internal() {
		if (!out_stack_.empty()) {
			auto r = out_stack_.top();
			out_stack_.pop();
			return r;
		}
		else {
			throw "no element";
		}
	}

	void move_elem() {
		if (out_stack_.empty()) {
			while (!in_stack_.empty()) {
				out_stack_.push(in_stack_.top());
				in_stack_.pop();
			}
		}
	}

public:
	MyQueue() : in_stack_(), out_stack_() {}

	void enqueue(int v) {
		in_stack_.push(v);
	}

	int dequeue() {
		move_elem();
		return dequeue_internal();
	}
};

int main() {
	MyQueue q;

	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);

	cout << q.dequeue() << endl;
	cout << q.dequeue() << endl;

	q.enqueue(4);
	q.enqueue(5);

	cout << q.dequeue() << endl;
	cout << q.dequeue() << endl;
	cout << q.dequeue() << endl;

	try {
		cout << q.dequeue() << endl;
	}
	catch (const char* ex) {
		cout << "exception: " << ex << endl;
	}
}
