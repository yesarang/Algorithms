#include <iostream>
#include <cassert>
#include <tuple>

using namespace std;

struct node {
	int v_;
	node* l_;
	node* r_;
	node(int v, node* l = nullptr, node* r = nullptr) : v_(v), l_(l), r_(r) {}
};

tuple<node*, bool, bool> contains(node* n, node* n1, node* n2) {
	if (!n) {
		return make_tuple(nullptr, false, false);
	}

	auto [ln, n1_found_left, n2_found_left] = contains(n->l_, n1, n2);
	if (ln) {
		return make_tuple(ln, true, true);
	}
	auto [rn, n1_found_right, n2_found_right] = contains(n->r_, n1, n2);
	if (rn) {
		return make_tuple(rn, true, true);
	}

	auto n1_found = n == n1 || n1_found_left || n1_found_right;
	auto n2_found = n == n2 || n2_found_left || n2_found_right;
	return make_tuple(n1_found && n2_found ? n : nullptr, n1_found, n2_found);
}

node* common_ancestor(node* root, node* n1, node* n2) {
	auto [n, _, _] = contains(root, n1, n2);
	return n;
}

int main() {
	auto node6 = new node(6);
	auto node3 = new node(3);
	auto node4 = new node(4, node6);
	auto node5 = new node(5);
	auto node2 = new node(2, node3, node4);
	auto tree = new node(1, node2, node5);

	auto ca = common_ancestor(tree, node6, node5);
	cout << ca->v_ << endl;

	ca = common_ancestor(tree, node3, node6);
	cout << ca->v_ << endl;

	ca = common_ancestor(tree, node3, tree);
	cout << ca->v_ << endl;
}
