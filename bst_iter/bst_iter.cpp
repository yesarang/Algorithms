// bst_iter.cpp : design an algorithm that returns the next smallest item
// in a binary search tree
//

#include <iostream>
#include <stack>

using namespace std;

struct node {
	node* l;
	node* r;
	int v;
	node(int v, node* l = nullptr, node* r = nullptr) : v(v), l(l), r(r) {}
};

class bst_iter {
private:
	stack<node*> s;
	node* c;

	node* get_first(node* n) {
		while (n->l) {
			s.push(n);
			n = n->l;
		}
		return n;
	}

public:
	bst_iter(node* root) : s(), c(get_first(root)) {}
	node* next() {
		auto r = c;
		if (c && c->r) {
			c = get_first(c->r);
		}
		else if (!s.empty()) {
			c = s.top();
			s.pop();
		}
		else {
			c = nullptr;
		}
		return r;
	}
};

int main()
{
	node* tree =
		new node(10,
			new node(5, nullptr, new node(8)),
			new node(15, new node(12), new node(18))
		);

	bst_iter i(tree);
	cout << i.next()->v << endl;
	cout << i.next()->v << endl;
	cout << i.next()->v << endl;
	cout << i.next()->v << endl;
	cout << i.next()->v << endl;
	cout << i.next()->v << endl;

	return 0;
}
