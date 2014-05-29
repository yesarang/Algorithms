#include <iostream>

using namespace std;

struct Node {
	int data;
	Node* next;
	Node(int d, Node* n) : data(d), next(n) {}
};

Node* reverse_list(Node* cur) {
	if (!cur) {
		return cur;
	}

	Node* prev = nullptr;
	Node* next = cur->next;
	while (next) {
		cur->next = prev;
		prev = cur;
		cur = next;
		next = next->next;
	}
	cur->next = prev;
	return cur;
}

Node* reverse_list2_impl(Node* new_head, Node* cur) {
	if (!cur) {
		return new_head;
	}

	// Need to remember next node in advance because we are about to modify the next pointer.
	Node* next = cur->next;
	cur->next = new_head;
	// Now 'cur' became the new head
	return reverse_list2_impl(cur, next);
}

Node* reverse_list2(Node* head) {
	return reverse_list2_impl(nullptr, head);
}

void print_list(Node* head) {
	while (head) {
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
}

int main() {
	Node* head = new Node(1, new Node(2, new Node(3, nullptr)));
	print_list(head);
	print_list(head = reverse_list(head));
	print_list(head = reverse_list2(head));

	Node* list = new Node(4, nullptr);
	print_list(list = reverse_list2(list));
	return 0;
}
