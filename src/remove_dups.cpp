#include <iostream>
#include <unordered_set>
#include <initializer_list>

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
};

}

void remove_dups(my_list::list& l) {
	unordered_set<int> s;
	my_list::node* cur = l.head_;
	my_list::node* prev = nullptr;
	while (cur) {
		if (s.find(cur->data_) == s.end()) {
			s.insert(cur->data_);
			prev = cur;
			cur = cur->next_;
		}
		else {
			l.remove(prev, cur);
			cur = prev->next_;
		}
	}
}

void remove_dups_no_buffer(my_list::list& l) {
	my_list::node* cur{ l.head_ };
	while (cur) {
		l.remove_all(cur, cur->data_);
		cur = cur->next_;
	}
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
	my_list::list l{ 1, 2, 2, 2, 3, 3, 3, 4, 5, 6, 7 };
	print(l);
	remove_dups(l);
	print(l);

	my_list::list l2;
	my_list::list l3{ 1 };
	print(l2);
	remove_dups(l2);
	print(l2);
	print(l3);
	remove_dups(l3);
	print(l3);

	my_list::list l4{ 1, 2, 2, 2, 3, 3, 3, 4, 5, 6, 7 };
	print(l4);
	remove_dups_no_buffer(l4);
	print(l4);
	remove_dups_no_buffer(l2);
	print(l2);
	remove_dups_no_buffer(l3);
	print(l3);


	return 0;
}