#include <iostream>

using namespace std;

struct node {
	int v;
	node* next;
};

node* partition_list(node* n, int pv) {
	node* head = n;
	node* tail = n;

	while (n) {
		node* next = n->next;
		if (n->v < pv) {
			n->next = head;
			head = n;
		}
		else {
			tail->next = n;
			tail = n;
		}
		n = next;
	}
	tail->next = nullptr;

	return head;
}

ostream& operator<<(ostream& os, node* l) {
	while (l) {
		cout << l->v << " ";
		l = l->next;
	}
	cout << endl;

	return os;
}

int main() {
	node* l = new node{ 5, new node{ 4, new node{ 3, new node{ 2, new node{ 1, nullptr} } } } };
	l = partition_list(l, 3);
	cout << l << endl;
}
