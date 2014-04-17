#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <utility>

using namespace std;

struct Node {
	int val_;
	int priority_;
	int size_;
	Node* left_;
	Node* right_;
	Node(int val, Node* left = 0, Node* right = 0)
		: val_(val), priority_(rand() % 10), size_(1), left_(left), right_(right)
	{}
	void calc_size() {
		size_ = 1;
		if (left_) size_ += left_->size_;
		if (right_) size_ += right_->size_;
	}
};

typedef pair<Node*, Node*> NodePair;

NodePair split(Node* root, int val) {
	if (!root) {
		return NodePair(0, 0);
	}
	if (val > root->val_) {
		NodePair p = split(root->right_, val);
		root->right_ = p.first;
		return NodePair(root, p.second);
	}
	else {
		NodePair p = split(root->left_, val);
		root->left_ = p.second;
		return NodePair(p.first, root);
	}
}

/*
void print_in_order(Node* root) {
	if (!root) {
		return;
	}
	print_in_order(root->left_);
	cout << root->val_ << " ";
	print_in_order(root->right_);
}
*/

string spaces(int level) {
	string s;
	for (; level > 0; --level) {
		s += "  ";
	}
	return s;
}

void print_in_order(Node* node, int level) {
	if (node->left_)
		print_in_order(node->left_, level + 1);
	cout << spaces(level) << node->val_ << ": " << node->priority_ << endl;
	if (node->right_)
		print_in_order(node->right_, level + 1);
}

Node* insert(Node* root, Node* node) {
	if (!root) {
		return node;
	}
	if (node->priority_ <= root->priority_) {
		if (node->val_ < root->val_) {
			root->left_ = insert(root->left_, node);
		}
		else if (node->val_ > root->val_) {
			root->right_ = insert(root->right_, node);
		}
		return root;
	}

	// Now node should become a new root
	NodePair p = split(root, node->val_);
	node->left_ = p.first;
	node->right_ = p.second;
	return node;
}

int main() {
	srand(time(0));
	Node* tree = 0;

	for (auto v : {1,2,3,4,5,6,7,8,9,10,11,12,13,14}) {
		tree = insert(tree, new Node(v));
	}

	print_in_order(tree, 0);

	return 0;
}