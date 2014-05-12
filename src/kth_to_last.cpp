// 2.2 Implement an algorithm to find the kth to last element of a singly linked list.
#include <iostream>
#include <unordered_set>
#include <initializer_list>
#include <cstdio>

using namespace std;

namespace my_list {

struct node {
	int data_;
	node* next_;
	node(int data) : data_{ data }, next_{ nullptr } {}
};

struct list {
	node* head_;
	node* tail_;
	list() : head_{ nullptr }, tail_{ nullptr } {}
	list(const initializer_list<int>& l) : list{}
	{
		for (auto i : l) {
			add_to_tail(i);
		}
	}

	void add_to_tail(int data) {
		node* new_node{ new node(data) };
		if (tail_) {
			tail_->next_ = new_node;
		}
		tail_ = new_node;
		if (!head_) {
			head_ = tail_;
		}
	}

	void remove(node* hint, node* to_be_removed) {
		if (!hint && to_be_removed == head_) {
			head_ = to_be_removed->next_;
		}
		else if (hint && hint->next_ == to_be_removed) {
			hint->next_ = to_be_removed->next_;
		}
		else {
			head_ = tail_ = nullptr;
		}
		delete to_be_removed;
	}

	void remove_all(node* prev, int data) {
		node* cur{ prev->next_ };
		while (cur) {
			if (cur->data_ == data) {
				remove(prev, cur);
				cur = prev->next_;
			}
			else {
				prev = cur;
				cur = cur->next_;
			}
		}
	}

	// k is 0-based
	node* get_kth_to_last(unsigned k) {
		if (k == 0) {
			return tail_;
		}
		node* fast{ head_ };
		while (k > 0 && fast != tail_) {
			fast = fast->next_;
			--k;
		}
		if (k > 0) {
			return nullptr;
		}
		node* slow{ head_ };
		while (fast != tail_) {
			fast = fast->next_;
			slow = slow->next_;
		}
		return slow;
	}
};

}

void print(const my_list::list& l) {
	my_list::node* cur = l.head_;
	while (cur) {
		cout << cur->data_ << " ";
		cur = cur->next_;
	}
	cout << endl;
}

int main() {
	my_list::list l{ 1, 2, 3, 4, 5, 6, 7 };
	print(l);

	my_list::node* pos1{ l.get_kth_to_last(0) };
	my_list::node* pos2{ l.get_kth_to_last(2) };
	my_list::node* pos3{ l.get_kth_to_last(4) };
	my_list::node* pos4{ l.get_kth_to_last(6) };
	my_list::node* pos5{ l.get_kth_to_last(7) };

	printf("%d, %d, %d, %d, %d\n",
		pos1 ? pos1->data_ : -1,
		pos2 ? pos2->data_ : -1, 
		pos3 ? pos3->data_ : -1, 
		pos4 ? pos4->data_ : -1, 
		pos5 ? pos5->data_ : -1
		);

	return 0;
}
