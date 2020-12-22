#include <iostream>
#include <tuple>

using namespace std;

struct node {
	int v_;
	node* l_;
	node* r_;
	node(int v, node* l = nullptr, node* r = nullptr) : v_(v), l_(l), r_(r) {}
};

tuple<int, int, int> contains(node* n, node* n1, node* n2) {
	if (!n) {
		return make_tuple(-1, -1, -1);
	}

	auto [ll, d1_l, d2_l] = contains(n->l_, n1, n2);
	if (ll >= 0) {
		return make_tuple(ll, -1, -1);
	}
	auto [rl, d1_r, d2_r] = contains(n->r_, n1, n2);
	if (rl >= 0) {
		return make_tuple(rl, -1, -1);
	}
	auto d1 = d1_l >= 0 ? d1_l : d1_r;
	if (d1 < 0 && n == n1) {
		d1 = 0;
	}
	auto d2 = d2_l >= 0 ? d2_l : d2_r;
	if (d2 < 0 && n == n2) {
		d2 = 0;
	}

	return make_tuple(d1 >= 0 && d2 >= 0 ? d1 + d2 : -1, d1 >= 0 ? d1 + 1 : -1, d2 >= 0 ? d2 + 1 : -1);
}

int get_path_length(node* root, node* n1, node* n2) {
	auto [l, _1, _2] = contains(root, n1, n2);
	return l;
}

int main() {
	auto node6 = new node(6);
	auto node3 = new node(3);
	auto node4 = new node(4, node6);
	auto node5 = new node(5);
	auto node2 = new node(2, node3, node4);
	auto tree = new node(1, node2, node5);

	cout << get_path_length(tree, node6, node5) << endl;
	cout << get_path_length(tree, node3, node6) << endl;
	cout << get_path_length(tree, node3, tree) << endl;
}
