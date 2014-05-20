#include <iostream>

using namespace std;

struct Node {
	int data;
	Node* next;
	Node(int d, Node* n) : data(d), next(n) {}
};

Node* reverse_list(Node* head) {
	if (!head) {
		return head;
	}

	Node* cur = nullptr;
	Node* next;
	while (head->next) {
		next = head->next;
		head->next = cur;
		cur = head;
		head = next;
	}
	head->next = cur;
	return head;
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
	print_list(head = reverse_list(head));
	return 0;
}
