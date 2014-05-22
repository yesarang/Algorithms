#include <iostream>

using namespace std;

struct Node {
	int digit;
	Node* next;
	Node(int d, Node* n) : digit(d), next(n) {}
};

Node* add_num_list(Node* l1, Node* l2) {
	int carry_up{0};
	int digit{0};
	Node* head{nullptr};
	Node* tail{nullptr};
	while (l1 && l2) {
		digit = (l1->digit + l2->digit + carry_up) % 10;
		carry_up = (l1->digit + l2->digit + carry_up) / 10;
		if (!head && !tail) {
			head = tail = new Node(digit, nullptr);
		}
		else {
			tail->next = new Node(digit, nullptr);
			tail = tail->next;
		}
		l1 = l1->next;
		l2 = l2->next;
	}
	
	Node* rn{l1 ? l1 : l2};
	while (rn) {
		digit = (rn->digit + carry_up) % 10;
		carry_up = (rn->digit + carry_up) / 10;
		if (!head && !tail) {
			head = tail = new Node(digit, nullptr);
		}
		else {
			tail->next = new Node(digit, nullptr);
			tail = tail->next;
		}
		rn = rn->next;
	}
	if (carry_up) {
		tail->next = new Node(carry_up, nullptr);
		tail = tail->next;
	}
	return head;
}

void print_num_list(Node* list) {
	while (list) {
		cout << list->digit << " ";
		list = list->next;
	}
	cout << endl;
}

int main() {
	Node* l1{new Node(0, new Node(1, nullptr))};
	print_num_list(l1);
	Node* l2{new Node(9, new Node(9, new Node(9, nullptr)))};
	print_num_list(l2);

	Node* r = add_num_list(l1, l2);
	print_num_list(r);

	return 0;
}

