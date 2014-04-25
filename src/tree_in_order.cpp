#include <iostream>
#include <stack>
#include <functional>
#include <utility>

using namespace std;

struct node {
	int val_;
	node* left_;
	node* right_;
	node(int val, node* left = nullptr, node* right = nullptr)
		: val_(val), left_(left), right_(right)
	{}
};

struct traverse_status {
	node* n_;
	bool left_complete_;
	bool right_complete_;
	traverse_status(node* n)
		: n_(n), left_complete_(false), right_complete_(false)
	{}
};

void in_order_traverse(node* root, function<void(node*)> op) {
	stack<node*> s;
	node* c = root;
	s.push(c);
	while (!s.empty()) {
		c = s.top();
		if (c->left_) {
			s.push(c->left_);
		}
		else {
			while (!s.empty()) {
				c = s.top();
				op(c);
				s.pop();
				if (c->right_) {
					s.push(c->right_);
					break;
				}
			}
		}
	}
}

void pre_order_traverse(node* root, function<void(node*)> op) {
	stack<node*> s;
	node* c = root;
	s.push(c);
	while (!s.empty()) {
		c = s.top();
		op(c);
		if (c->left_) {
			s.push(c->left_);
		}
		else {
			while (!s.empty()) {
				c = s.top();
				s.pop();
				if (c->right_) {
					s.push(c->right_);
					break;
				}
			}
		}
	}
}

void post_order_traverse(node* root, function<void(node*)> op) {
	// stack for traverse
	stack<traverse_status> s;
	node* c = root;
	s.push(c);
	while (!s.empty()) {
		traverse_status& st = s.top();
		c = st.n_;
		if (!st.left_complete_) {
			if (c->left_) {
				s.push(c->left_);
			}
			else {
				st.left_complete_ = true;
			}
		}
		else if (!st.right_complete_) {
			if (c->right_) {
				s.push(c->right_);
			}
			else {
				st.right_complete_ = true;
			}
		}
		else {
			op(c);
			s.pop();
			if (!s.empty()) {
				traverse_status& parent_status = s.top();
				if (!parent_status.left_complete_) {
					parent_status.left_complete_ = true;
				}
				else if (!parent_status.right_complete_) {
					parent_status.right_complete_ = true;
				}
			}
		}
	}
}

auto print = [](node* n) {
	cout << n->val_ << " ";
};

void print_in_order(node* root) {
	in_order_traverse(root, print);
	cout << endl;
}

void print_post_order(node* root) {
	post_order_traverse(root, print);
	cout << endl;
}

void print_pre_order(node* root) {
	pre_order_traverse(root, print);
	cout << endl;
}

int main() {
	node* tree = new node(1);
	// 1
	print_in_order(tree);
	// 1
	print_pre_order(tree);
	// 1
	print_post_order(tree);

	tree->left_ = new node(2);
	// 2 1
	print_in_order(tree);
	// 1 2
	print_pre_order(tree);
	// 2 1
	print_post_order(tree);

	tree->left_->left_ = new node(3);
	// 3 2 1
	print_in_order(tree);
	// 1 2 3
	print_pre_order(tree);
	// 3 2 1
	print_post_order(tree);

	tree->right_ = new node(4);
	// 3 2 1 4
	print_in_order(tree);
	// 1 2 3 4
	print_pre_order(tree);
	// 3 2 4 1
	print_post_order(tree);

	tree->right_->left_ = new node(5);
	tree->right_->right_ = new node(6, nullptr, new node(7, 0, new node(8)));
	// 3 2 1 5 4 6 7 8
	print_in_order(tree);
	// 1 2 3 4 5 6 7 8
	print_pre_order(tree);
	// 3 2 5 8 7 6 4 1
	print_post_order(tree);

	node* tree2 = new node(1,
		new node(2,
			new node(4),
			new node(5)
			),
		new node(3,
			new node(6),
			new node(7)
			)
		);
	// 4 5 2 6 7 3 1
	print_post_order(tree2);
	// 4 2 5 1 6 3 7
	print_in_order(tree2);

	return 0;
}
