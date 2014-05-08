// Implement a function to check if a binary tree is a binary search tree.
#include <iostream>
#include <memory>
#include <algorithm>
#include <climits>
#include <cassert>
#include <tuple>

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

bool is_binary_search_tree(shared_ptr<Node> root, int& min, int& max) {
	if (!root) {
		return true;
	}

	int left_min = INT_MAX;
	int left_max = INT_MIN;
	bool left_flag = is_binary_search_tree(root->left_, left_min, left_max);
	int right_min = INT_MAX;
	int right_max = INT_MIN;
	bool right_flag = is_binary_search_tree(root->right_, right_min, right_max);

	min = std::min(std::min(left_min, root->data_), right_min);
	max = std::max(std::max(left_max, root->data_), right_max);

	return left_flag && right_flag &&
		left_max <= root->data_ &&
		root->data_ <= right_min;
}

// tuple: (FLAG, MIN, MAX) 
typedef tuple<bool, int, int> RetType;
enum Fields {
	FLAG = 0,
	MIN = 1,
	MAX = 2
};

RetType is_binary_search_tree2(shared_ptr<Node> root) {
	if (!root) {
		return make_tuple(true, INT_MAX, INT_MIN);
	}

	auto left_ret = is_binary_search_tree2(root->left_);
	auto right_ret = is_binary_search_tree2(root->right_);

	return make_tuple(
		get<Fields::FLAG>(left_ret) && get<Fields::FLAG>(right_ret) && get<Fields::MAX>(left_ret) <= root->data_ && root->data_ <= get<Fields::MIN>(right_ret),
		std::min(std::min(get<Fields::MIN>(left_ret), root->data_), get<Fields::MIN>(right_ret)),
		std::max(std::max(get<Fields::MAX>(left_ret), root->data_), get<Fields::MAX>(right_ret))
		);
}

int main() {
	shared_ptr<Node> tree{
		make_shared<Node>(13,
			nullptr,
			nullptr
			)
	};

	int min_val = 0;
	int max_val = 0;
	assert(is_binary_search_tree(tree, min_val, max_val));
	assert(min_val == 13 && max_val == 13);
	cout << "The tree is a binary search tree, min = " << min_val << " max = " << max_val << endl;

	bool flag;
	tie(flag, min_val, max_val) = is_binary_search_tree2(tree);
	assert(flag && min_val == 13 && max_val == 13);
	cout << "The tree is a binary search tree, min = " << min_val << " max = " << max_val << endl;

	tree->left_ = make_shared<Node>(6,
		make_shared<Node>(3),
		make_shared<Node>(8)
		);
	tree->right_ = make_shared<Node>(21,
		make_shared<Node>(15),
		make_shared<Node>(30)
		);
	min_val = 0;
	max_val = 0;
	assert(is_binary_search_tree(tree, min_val, max_val));
	assert(min_val == 3 && max_val == 30);
	cout << "The tree is a binary search tree, min = " << min_val << " max = " << max_val << endl;

	tie(flag, min_val, max_val) = is_binary_search_tree2(tree);
	assert(flag && min_val == 3 && max_val == 30);
	cout << "The tree is a binary search tree, min = " << min_val << " max = " << max_val << endl;

	tree->right_->right_->right_ = make_shared<Node>(1);	// attach (1) to 30;
	min_val = 0;
	max_val = 0;
	assert(!is_binary_search_tree(tree, min_val, max_val));
	assert(min_val == 1 && max_val == 30);
	cout << "The tree isn't a binary search tree, min = " << min_val << " max = " << max_val << endl;

	tie(flag, min_val, max_val) = is_binary_search_tree2(tree);
	assert(!flag && min_val == 1 && max_val == 30);
	cout << "The tree isn't a binary search tree, min = " << min_val << " max = " << max_val << endl;

	return 0;
}
