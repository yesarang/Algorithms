// 4.7 Design an algorithm and write code to find the first common ancestor of two
// nodes in a binary tree. Avoid storing additional nodes in a data structure. NOTE:
// This is not necessarily a binary search tree.
#include <iostream>
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

bool get_path(Node::Ptr root, Node::Ptr node, deque<Node::Ptr>& path) {
	if (!root) {
		return false;
	}

	path.push_back(root);
	if (node == root ||
		get_path(root->left_, node, path) ||
		get_path(root->right_, node, path)) {
		return true;
	}
	path.pop_back();
	return false;
}

Node::Ptr get_common_ancestor(Node::Ptr root, Node::Ptr node1, Node::Ptr node2) {
	deque<Node::Ptr> path1, path2;
	if (!get_path(root, node1, path1) || !get_path(root, node2, path2)) {
		return nullptr;
	}

	Node::Ptr ret;
	while (!path1.empty() && !path2.empty()) {
		if (path1.front() != path2.front()) {
			break;
		}
		ret = path1.front();
		path1.pop_front();
		path2.pop_front();
	}
	return ret;
}

bool contains(Node::Ptr root, Node::Ptr node) {
	if (!root) {
		return false;
	}
	
	if (root == node ||
		contains(root->left_, node) ||
		contains(root->right_, node)) {
		return true;
	}
	else {
		return false;
	}
}

// This algorithm assumes that node1 & nodes in the tree root
Node::Ptr get_common_ancestor_impl(Node::Ptr root, Node::Ptr node1, Node::Ptr node2) {
	if (!root) {
		return nullptr;
	}
	bool is_node1_left = contains(root->left_, node1);
	bool is_node2_left = contains(root->left_, node2);
	if (is_node1_left && is_node2_left) {			// both nodes are in the left tree
		return get_common_ancestor_impl(root->left_, node1, node2);
	}
	else if (is_node1_left != is_node2_left) {
		// node1 in left && node2 in right || node1 in right && node2 in left
		return root;
	}
	else {	// both nodes are in the right tree
		return get_common_ancestor_impl(root->right_, node1, node2);
	}
}

Node::Ptr get_common_ancestor2(Node::Ptr root, Node::Ptr node1, Node::Ptr node2) {
	if (!contains(root, node1) || !contains(root, node2)) {
		return nullptr;
	}
	return get_common_ancestor_impl(root, node1, node2);
}

int main() {
	auto node3 = make_shared<Node>(3);
	auto node4 = make_shared<Node>(4);
	auto tree = make_shared<Node>(1,
		make_shared<Node>(2, node3, node4),
		nullptr
		);

	deque<Node::Ptr> path;
	assert(get_path(tree, node3, path));
	while (!path.empty()) {
		cout << path.front()->data_ << " ";
		path.pop_front();
	}
	cout << endl;

	assert(get_path(tree, node4, path));
	while (!path.empty()) {
		cout << path.front()->data_ << " ";
		path.pop_front();
	}
	cout << endl;

	Node::Ptr ancestor = get_common_ancestor(tree, node3, node4);
	assert(ancestor && ancestor->data_ == 2);
	cout << "Common ancestor for 3 & 4: " << ancestor->data_ << endl;

	ancestor = get_common_ancestor2(tree, node3, node4);
	assert(ancestor && ancestor->data_ == 2);
	cout << "Common ancestor for 3 & 4: " << ancestor->data_ << endl;

	return 0;
}
