#include <iostream>
#include <functional>

using namespace std;

struct node {
	int v_;
	node* l_;
	node* r_;

	node(int v, node* l = nullptr, node* r = nullptr)
		: v_(v), l_(l), r_(r)
	{}
};

int path_of_sum(node* n, int s) {
	function <int(node*, int)> impl = [&](node* n, int rs) {
		if (!n) {
			return 0;
		}

		int c = 0;
		if (rs == n->v_) {
			++c;
			rs = s;
		}
		rs -= n->v_;
		return c + impl(n->l_, rs) + impl(n->r_, rs);
	};

	return impl(n, s);
}

int main() {
	node* tree =
		new node(7,
			new node(3, new node(7), new node(1)),
			new node(2, new node(1), new node(8))
		);

	cout << path_of_sum(tree, 10) << endl;
	cout << path_of_sum(tree, 3) << endl;
}
