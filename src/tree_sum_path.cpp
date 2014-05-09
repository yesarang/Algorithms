// 4.9 You are given a binary tree in which each node contains a value. Design an algorithm
// to print all paths which sum to a given value. The path does not need to
// start or end at the root or a leaf.
#include <iostream>
#include <vector>
#include <deque>
#include <memory>
#include <cassert>
#include <algorithm>
#include <utility>

using namespace std;

struct Node {
	typedef shared_ptr<Node> Ptr;
	int data_;
	Ptr left_;
	Ptr right_;

	Node(int data, Ptr left, Ptr right)
		: data_{ data }, left_{ left }, right_{ right }
	{}
	Node(int data) : Node{ data, nullptr, nullptr }
	{}
};

void print_path(const deque<Node::Ptr>& cp) {
	for (auto n : cp) {
		cout << n->data_ << " ";
	}
	cout << endl;
}

void print_all_paths_sum_to_impl(Node::Ptr root, int tgt, int sum, deque<Node::Ptr>& cp) {
	if (!root) {
		return;
	}

	sum += root->data_;
	cp.push_back(root);
	if (sum == tgt) {
		print_path(cp);
	}
	else if (sum < tgt) {
		print_all_paths_sum_to_impl(root->left_, tgt, sum, cp);
		print_all_paths_sum_to_impl(root->right_, tgt, sum, cp);
	}
	cp.pop_back();
}

void print_all_paths_sum_to(Node::Ptr root, int tgt) {
	deque<Node::Ptr>cp;
	print_all_paths_sum_to_impl(root, tgt, 0, cp);
}

int main() {
	auto tree = make_shared<Node>(1,
		make_shared<Node>(2,
			make_shared<Node>(4),
			make_shared<Node>(3)
			),
		make_shared<Node>(3,
			make_shared<Node>(2),
			make_shared<Node>(1)
			)
		);

	for (int i = 1; i < 10; ++i) {
		cout << "target : " << i << endl;
		print_all_paths_sum_to(tree, i);
		cout << "---" << endl;
	}

	return 0;
}
