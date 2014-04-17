#include <iostream>
#include <utility>

using namespace std;

struct Node {
	int val_;
	Node* left_;
	Node* right_;
	Node(int val, Node* left = 0, Node* right = 0)
		: val_(val), left_(left), right_(right)
	{}
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

void print_in_order(Node* root) {
	if (!root) {
		return;
	}
	print_in_order(root->left_);
	cout << root->val_ << " ";
	print_in_order(root->right_);
}

Node* build_tree() {
	Node* node4 = new Node(40, new Node(30), 0);
	Node* node2 = new Node(20, new Node(10), node4);
	Node* node7 = new Node(70, new Node(60), 0);
	return new Node(50, node2, node7);
}

int main() {
	Node* tree = build_tree();
	cout << "original tree: " << endl;
	print_in_order(tree);
	cout << endl;

	cout << "splitting with 35" << endl;
	NodePair p = split(tree, 35);
	cout << "left tree:" << endl;
	print_in_order(p.first);
	cout << endl;
	cout << "right tree: " << endl;
	print_in_order(p.second);
	cout << endl;

	tree = build_tree();
	cout << "splitting with 50" << endl;
	p = split(tree, 50);
	cout << "left tree:" << endl;
	print_in_order(p.first);
	cout << endl;
	cout << "right tree: " << endl;
	print_in_order(p.second);
	cout << endl;

	tree = build_tree();
	cout << "splitting with 90" << endl;
	p = split(tree, 90);
	cout << "left tree:" << endl;
	print_in_order(p.first);
	cout << endl;
	cout << "right tree: " << endl;
	print_in_order(p.second);
	cout << endl;

	return 0;
}