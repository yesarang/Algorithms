// 4.3 Given a sorted(increasing order) array with unique integer elements, write an
// algorithm to create a binary search tree with minimal height.
#include <iostream>
#include <vector>
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

shared_ptr<Node> make_binary_search_tree(int start, int end, const vector<int>& sorted_array) {
	if (start == end) {
		return make_shared<Node>(sorted_array[start]);
	}
	else if (start > end) {
		return nullptr;
	}

	int mid{ start + (end - start + 1) / 2 };
	return make_shared<Node>(
		sorted_array[mid],
		make_binary_search_tree(start, mid - 1, sorted_array),
		make_binary_search_tree(mid + 1, end, sorted_array)
	);
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
	vector<int> sorted_array{ 2, 6, 7, 9, 11, 16 };
	shared_ptr<Node> tree = make_binary_search_tree(0, sorted_array.size() - 1, sorted_array);
	cout << "sorted array: ";
	for (auto i : sorted_array) {
		cout << i << " ";
	}
	cout << endl;
	print_tree(tree);

	sorted_array.assign({ 2, 6, 7, 9, 11, 16, 21 });
	tree = make_binary_search_tree(0, sorted_array.size() - 1, sorted_array);
	cout << "sorted array: ";
	for (auto i : sorted_array) {
		cout << i << " ";
	}
	cout << endl;
	print_tree(tree);

	sorted_array.assign({ 2 });
	tree = make_binary_search_tree(0, sorted_array.size() - 1, sorted_array);
	cout << "sorted array: ";
	for (auto i : sorted_array) {
		cout << i << " ";
	}
	cout << endl;
	print_tree(tree);

	sorted_array.assign({});
	tree = make_binary_search_tree(0, sorted_array.size() - 1, sorted_array);
	cout << "sorted array: ";
	for (auto i : sorted_array) {
		cout << i << " ";
	}
	cout << endl;
	print_tree(tree);

	return 0;
}
