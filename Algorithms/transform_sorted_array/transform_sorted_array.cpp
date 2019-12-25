#include <iostream>
#include <vector>
#include <functional>

using namespace std;

struct node {
	int v_;
	node* l_;
	node* r_;

	node(int v, node* l, node* r)
		: v_(v), l_(l), r_(r)
	{}
};

node* transform_sorted_array(const vector<int>& sorted) {
	function <node*(int, int)> impl = [&](int start, int end) {
		if (start > end) {
			return static_cast<node*>(nullptr);
		}
		auto mid = start + (end - start + 1) / 2;
		return new node(sorted[mid], impl(start, mid - 1), impl(mid + 1, end));
	};

	return impl(0, sorted.size() - 1);
}

void print_tree(node* n) {
	function <void(node*)> impl = [&](node* n) {
		if (!n) {
			return;
		}
		impl(n->l_);
		cout << n->v_ << " ";
		impl(n->r_);
	};

	impl(n);
	cout << endl;
}

int main() {
	vector<int> v({ 1,2,3,4,5,6,7,8,9 });

	auto r = transform_sorted_array(v);
	print_tree(r);
}
