#include <iostream>
#include <stack>
#include <functional>

using namespace std;

struct node {
	int val_;
	node* left_;
	node* right_;
	node(int val, node* left = nullptr, node* right = nullptr)
		: val_(val), left_(left), right_(right)
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
	stack<node*> s;
	// stack for operation
	stack<node*> p;
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
				s.pop();
				if (c->right_) {
					s.push(c->right_);
					p.push(c);
					break;
				}
				else {
					op(c);
				}
			}
		}
	}

	while (!p.empty()) {
		c = p.top();
		p.pop();
		op(c);
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

	return 0;
}
