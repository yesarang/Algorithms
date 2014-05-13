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

	node* find(int data) {
		node* pos{ head_ };
		while (pos) {
			if (pos->data_ == data) {
				return pos;
			}
			pos = pos->next_;
		}
		return nullptr;
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

	void remove_node(node* to_be_removed) {
		if (!to_be_removed) {
			return;
		}
		if (!head_ && !tail_) {
			return;
		}
		if (head_ == tail_ && head_ == to_be_removed) {
			delete to_be_removed;
			head_ = tail_ = nullptr;
		}
		node* prev{ nullptr };
		node* cur{ head_ };
		while (cur) {
			if (cur == to_be_removed) {
				break;
			}
			prev = cur;
			cur = cur->next_;
		}
		if (prev) {
			prev->next_ = cur->next_;
			delete cur;
		}
		else {
			head_ = head_->next_;
			delete cur;
		}
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

void print(const list& l) {
	node* cur = l.head_;
	while (cur) {
		cout << cur->data_ << " ";
		cur = cur->next_;
	}
	cout << endl;
}

}

int main() {
	my_list::list l{ 1, 2, 3, 4, 5, 6, 7 };
	print(l);

	l.remove_node(l.find(1));
	print(l);
	l.remove_node(l.find(3));
	print(l);
	l.remove_node(l.find(7));
	print(l);
	l.remove_node(l.find(8));
	print(l);

	return 0;
}