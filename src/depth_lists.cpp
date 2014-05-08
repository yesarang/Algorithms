// Given a binary tree, design an algorithm which creates a linked list of all the
// nodes at each depth(e.g., if you have a tree with depth D, you'll have D linked
// lists).
#include <iostream>
#include <stack>
#include <vector>
#include <list>
#include <unordered_map>
#include <memory>

using namespace std;

struct Node {
	int data_;
	shared_ptr<Node> left_;
	shared_ptr<Node> right_;

	Node(int data, shared_ptr<Node> left, shared_ptr<Node> right)
		: data_{ data }, left_{ left }, right_{ right }
	{}
	Node(int data) : Node{ data, nullptr, nullptr }
	{}
};

void make_depth_lists(shared_ptr<Node> root, int depth, unordered_map<int, list<shared_ptr<Node>>>& depth_lists) {
	if (!root) {
		return;
	}

	depth_lists[depth].push_back(root);
	make_depth_lists(root->left_, depth + 1, depth_lists);
	make_depth_lists(root->right_, depth + 1, depth_lists);
}

void make_depth_lists2(shared_ptr<Node> root, int depth, vector<list<shared_ptr<Node>>>& depth_lists) {
	if (!root) {
		return;
	}

	if (depth_lists.size() < static_cast<unsigned>(depth + 1)) {
		depth_lists.resize(depth + 1);
	}
	depth_lists[depth].push_back(root);
	make_depth_lists2(root->left_, depth + 1, depth_lists);
	make_depth_lists2(root->right_, depth + 1, depth_lists);
}

void print_in_order(shared_ptr<Node> root) {
	if (!root)
		return;
	print_in_order(root->left_);
	cout << root->data_ << " ";
	print_in_order(root->right_);
}

void print_tree(shared_ptr<Node> root) {
	cout << "tree: ";
	print_in_order(root);
	cout << endl;
}

int main() {
	shared_ptr<Node> tree{
		make_shared<Node>(1,
			make_shared<Node>(2,
				make_shared<Node>(4),
				make_shared<Node>(5)
				),
			make_shared<Node>(3,
				make_shared<Node>(6),
				make_shared<Node>(7)
				)
			)
		};

	unordered_map<int, list<shared_ptr<Node>>> depth_lists;
	make_depth_lists(tree, 0, depth_lists);
	for (const auto& p : depth_lists) {
		cout << "level " << p.first << ": ";
		for (const auto& n : p.second) {
			cout << n->data_ << " ";
		}
		cout << endl;
	}

	vector<list<shared_ptr<Node>>> depth_lists2;
	make_depth_lists2(tree, 0, depth_lists2);
	int i = 0;
	for (const auto& l : depth_lists2) {
		cout << "level " << i++ << ": ";
		for (const auto& n : l) {
			cout << n->data_ << " ";
		}
		cout << endl;
	}

	return 0;
}
