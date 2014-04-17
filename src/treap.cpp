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
	root->calc_size();
}

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
			root->calc_size();
		}
		else if (node->val_ > root->val_) {
			root->right_ = insert(root->right_, node);
			root->calc_size();
		}
		return root;
	}

	// Now node should become a new root
	NodePair p = split(root, node->val_);
	node->left_ = p.first;
	node->right_ = p.second;
	node->calc_size();
	return node;
}

Node* kth(Node* root, int k) {
	int lsz = root->left_ ? root->left_->size_ : 0;
	if (k <= lsz)
		return kth(root->left_, k);
	else if (k == lsz + 1)
		return root;
	else
		return kth(root->right_, k - lsz - 1);
}

int count_less_than(Node* root, int k) {
	if (!root) {
		return 0;
	}
	if (k <= root->val_) {
		return count_less_than(root->left_, k);
	}
	else {
		int lsz = root->left_ ? root->left_->size_ : 0;
		return lsz + 1 + count_less_than(root->right_, k);
	}
}

int main() {
	srand(time(0));
	Node* tree = 0;

	for (auto v : {1,2,3,4,5,6,7,8,9,10,11,12,13,14}) {
		tree = insert(tree, new Node(v));
	}
	print_in_order(tree, 0);

	Node* n = kth(tree, 10);
	cout << "10th: " << n->val_ << endl;
	n = kth(tree, 7);
	cout << "7th: " << n->val_ << endl;
	n = kth(tree, 13);
	cout << "13th: " << n->val_ << endl;

	cout << "# of elements < 5: " << count_less_than(tree, 5) << endl;
	cout << "# of elements < 7: " << count_less_than(tree, 7) << endl;
	cout << "# of elements < 9: " << count_less_than(tree, 9) << endl;

	return 0;
}
