// Write an algorithm to find the'next'node (i.e., in-order successor) of a given node
// in a binary search tree. You may assume that each node has a link to its parent
#include <iostream>
#include <memory>
#include <cassert>

using namespace std;

struct Node {
	int data_;
	Node* left_;
	Node* right_;
	Node* parent_;

	Node(int data, Node* left, Node* right)
		: data_{ data }, left_{ left }, right_{ right }, parent_{ nullptr }
	{
		if (left_)
			left_->parent_ = this;
		if (right_)
			right->parent_ = this;
	}
	Node(int data) : Node{ data, nullptr, nullptr }
	{}
};

Node* get_next(Node* node) {
	if (!node) {
		return nullptr;
	}

	if (node->right_) {
		return node->right_;
	}
	else if (node->parent_ && node->parent_->left_ == node) {
		return node->parent_;
	}
	else {
		while (node->parent_ && node->parent_->right_ == node) {
			node = node->parent_;
		}
		return node->parent_;
	}
}

int main() {
	auto node = new Node(1);
	auto tree =
		new Node(4,
			new Node(2,
				node,
				new Node(3)
				),
			new Node(5,
				nullptr,
				new Node(6)
				)
			);

	do {
		cout << node->data_ << " ";
		node = get_next(node);
	} while (node);
	cout << endl;

	return 0;
}
