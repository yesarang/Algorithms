// 4.6 Write an algorithm to find the'next'node (i.e., in-order successor) of a given node
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

Node* get_left_most(Node* node) {
	if (!node) {
		return nullptr;
	}

	while (node->left_) {
		node = node->left_;
	}
	return node;
}

Node* get_next(Node* node) {
	if (!node) {
		return nullptr;
	}

	if (node->right_) {
		return get_left_most(node->right_);
	}
	else {
		Node* parent = node->parent_;
		while (parent && parent->left_ != node) {
			node = node->parent_;
			parent = parent->parent_;
		}
		return parent;
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
				new Node(6),
				nullptr
				)
			);

	do {
		cout << node->data_ << " ";
		node = get_next(node);
	} while (node);
	cout << endl;

	return 0;
}
