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
	head = reverse_list(head);
	print_list(head);

	return 0;
}
