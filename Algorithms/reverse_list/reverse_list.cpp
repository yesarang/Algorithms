#include <iostream>

using namespace std;

struct node {
	int v;
	node* n;

	node(int v, node* n = nullptr) : v(v), n(n) {}
};

node* reverse_list(node* l)
{
	if (!l) {
		return l;
	}

	node* cur = l;
	node* next = l->n;
	node* nl = nullptr;

	while (true) {
		cur->n = nl;
		nl = cur;
		cur = next;
		if (next) {
			next = next->n;
		}
		else {
			break;
		}
	}

	return nl;
}

void print_list(node* l) {
	node* cur = l;
	cout << "[";
	while (cur) {
		cout << cur->v << " ";
		cur = cur->n;
	}
	cout << "]" << endl;
}

int main() {
	node* l = new node(1, new node(2, new node(3, new node(4))));

	print_list(l);
	auto nl = reverse_list(l);
	print_list(nl);

	l = nullptr;
	auto nl2 = reverse_list(l);
	print_list(nl2);

	l = new node(10);
	print_list(l);
	auto nl3 = reverse_list(l);
	print_list(nl3);
}

