#include <iostream>

using namespace std;

struct Node {
	int digit;
	Node* next;
	Node(int d, Node* n) : digit(d), next(n) {}
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

Node* add_reverse_num_list(Node* l1, Node* l2) {
	Node* rl1 = reverse_list(l1);
	Node* rl2 = reverse_list(l2);

	Node* r = add_num_list(rl1, rl2);
	reverse_list(rl1);
	reverse_list(rl2);
	return reverse_list(r);
}

Node* add_reverse_num_list2_impl(Node* longer, Node* shorter, int diff, int& carry_up) {
	if (!longer && !shorter) {
		carry_up = 0;
		return nullptr;
	}

	Node* r = new Node(0, nullptr);
	if (diff <= 0) {
		r->next = add_reverse_num_list2_impl(longer->next, shorter->next, diff - 1, carry_up);
		r->digit = (longer->digit + shorter->digit + carry_up) % 10;
		carry_up = (longer->digit + shorter->digit + carry_up) / 10;
	}
	else {
		r->next = add_reverse_num_list2_impl(longer->next, shorter, diff - 1, carry_up);
		r->digit = (longer->digit + carry_up) % 10;
		carry_up = (longer->digit + carry_up) / 10;
	}

	return r;
}

int get_length(Node* list) {
	int l = 0;
	while (list) {
		++l;
		list = list->next;
	}
	return l;
}

Node* add_reverse_num_list2(Node* l1, Node* l2) {
	int len1 = get_length(l1);
	int len2 = get_length(l2);
	int carry_up = 0;

	Node* r = len1 > len2 ? add_reverse_num_list2_impl(l1, l2, len1 - len2, carry_up) :
							add_reverse_num_list2_impl(l2, l1, len2 - len1, carry_up);
	if (carry_up) {
		r = new Node(carry_up, r);
	}

	return r;
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

	Node* l3{new Node(1, new Node(0, nullptr))};
	print_num_list(l1);
	print_num_list(l2);

	r = add_reverse_num_list(l3, l2);
	print_num_list(r);
	print_num_list(l3);
	print_num_list(l2);

	r = add_reverse_num_list2(l3, l2);
	print_num_list(r);

	return 0;
}

