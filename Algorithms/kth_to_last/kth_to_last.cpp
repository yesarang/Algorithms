#include <iostream>

using namespace std;

struct node {
	int v;
	node* next;
};

node* kth_to_last(node* n, int k) {
	node* front = n;
	node* back = n;

	for (; k > 0 && front; --k, front = front->next);
	if (k > 0) {
		return nullptr;
	}

	while (front) {
		front = front->next;
		back = back->next;
	}

	return back;
}

int main() {
	node* l = new node{ 1, new node{2, new node{3, new node{4, nullptr}}}};

	cout << kth_to_last(l, 1)->v << endl;
	cout << kth_to_last(l, 2)->v << endl;
	cout << kth_to_last(l, 3)->v << endl;
	cout << kth_to_last(l, 4)->v << endl;
}
