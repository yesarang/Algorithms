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

void print_in_order(node* root) {
	in_order_traverse(root, [](node* n) {
		cout << n->val_ << " ";
	});
	cout << endl;
}

int main() {
	node* tree = new node(1);
	// 1
	print_in_order(tree);

	tree->left_ = new node(2);
	// 2 1
	print_in_order(tree);

	tree->left_->left_ = new node(3);
	// 3 2 1
	print_in_order(tree);

	tree->right_ = new node(4);
	// 3 2 1 4
	print_in_order(tree);

	tree->right_->left_ = new node(5);
	tree->right_->right_ = new node(6, nullptr, new node(7, 0, new node(8)));
	// 3 2 1 5 4 6 7 8
	print_in_order(tree);

	return 0;
}
