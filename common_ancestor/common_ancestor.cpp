#include <iostream>
#include <functional>
#include <tuple>

using namespace std;

struct node {
	int v;
	node* l;
	node* r;
};

node* common_ancestor(node* t, node* n1, node* n2) {
	function<tuple<node*, bool, bool>(node*, node*, node*)> impl = [&](node* n, node* n1, node* n2) -> tuple<node*, bool, bool> {
		if (!n) {
			return make_tuple(nullptr, false, false);
		}

		auto is_n1_found = n == n1;
		auto is_n2_found = n == n2;
		if (is_n1_found && is_n2_found) {
			return make_tuple(n, true, true);
		}

		auto[cal, is_n1_left, is_n2_left] = impl(n->l, n1, n2);
		if (is_n1_left && is_n2_left) {
			return make_tuple(cal, true, true);
		}

		auto[car, is_n1_right, is_n2_right] = impl(n->r, n1, n2);
		if (is_n1_right && is_n2_right) {
			return make_tuple(car, true, true);
		}

		auto is_n1_contained = is_n1_found || is_n1_left || is_n1_right;
		auto is_n2_contained = is_n2_found || is_n2_left || is_n2_right;

		return is_n1_contained && is_n2_contained ?
			make_tuple(n, true, true) :
			make_tuple(nullptr, is_n1_contained, is_n2_contained);
	};

	auto[ca, is_n1_contained, is_n2_contained] = impl(t, n1, n2);
	return ca;
}

void print_result(node* ca, node* n1, node* n2) {
	cout << "common ancestor of " << n1->v << " & " << n2->v << ": ";
	if (ca) {
		cout << ca->v << endl;
	}
	else {
		cout << "not found" << endl;
	}
}

int main() {
	node* n2 = new node{ 2, nullptr, nullptr };
	node* n6 = new node{ 6, nullptr, nullptr };
	node* n12 = new node{ 12, nullptr, nullptr };
	node* n19 = new node{ 19, nullptr, nullptr };
	node* n5 = new node{ 5, n2, n6 };
	node* n15 = new node{ 15, n12, n19 };
	node* n10 = new node{ 10, n5, n15 };
	node* t = n10;

	auto ca = common_ancestor(t, n2, n6);
	print_result(ca, n2, n6);

	ca = common_ancestor(t, n6, n19);
	print_result(ca, n12, n19);

	ca = common_ancestor(t, n10, n12);
	print_result(ca, n10, n12);

	ca = common_ancestor(t, n19, n19);
	print_result(ca, n19, n19);

	node* n20 = new node{ 20, nullptr, nullptr };
	ca = common_ancestor(t, n19, n20);
	print_result(ca, n19, n20);
}
