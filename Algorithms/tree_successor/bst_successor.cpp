#include <iostream>
#include <cassert>

using namespace std;

struct node {
	int v_;
	node* p_;
	node* l_;
	node* r_;
	node(int v, node* l = nullptr, node* r = nullptr)
		: v_(v), p_(nullptr), l_(l), r_(r)
	{
		if (l_)
			l_->p_ = this;
		if (r_)
			r_->p_ = this;
	}
};

node* get_first(node* n) {
	assert(n);

	while (n->l_) {
		n = n->l_;
	}
	return n;
}

node* get_next(node* n) {
	assert(n);

	if (n->r_) {
		return get_first(n->r_);
	}
	else {
		while (n->p_ && n != n->p_->l_) {
			n = n->p_;
		}
		return n->p_;
	}
}

int main() {
	auto tree =
		new node(4,
			new node(2,
				new node(1),
				new node(3)
			),
			new node(6,
				new node(5),
				nullptr
			)
		);

	auto node = get_first(tree);
	do {
		cout << node->v_ << " ";
		node = get_next(node);
	} while (node);
	cout << endl;
}