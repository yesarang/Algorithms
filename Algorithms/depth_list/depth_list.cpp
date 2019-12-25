#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

struct node {
	int v;
	node* l;
	node* r;
};

ostream& operator<<(ostream& os, const list<node*>& l) {
	for_each(l.begin(), l.end(), [&os](auto& e) {
		os << e->v << " ";
	});
	return os;
}

vector<list<node*>> depth_list(node* t) {
	function<void(vector<list<node*>>&, node*, int)> impl = [&](vector<list<node*>>& dl, node* n, int d) {
		if (!n) {
			return;
		}
		if (dl.size() < d + 1) {
			dl.emplace_back(list<node*>());
		}
		dl[d].push_back(n);
		impl(dl, n->l, d + 1);
		impl(dl, n->r, d + 1);
	};

	vector<list<node*>> dl;
	impl(dl, t, 0);

	return move(dl);
}

int main() {
	node* t =
		new node{ 1,
			new node{ 2,
				new node{ 4, nullptr, nullptr },
				new node{ 5, nullptr, nullptr }
			},
			new node{ 3,
				new node{ 6, nullptr, nullptr },
				new node{ 7, nullptr, nullptr }
			}
		};

	auto dl = depth_list(t);
	for_each(dl.begin(), dl.end(), [](auto& l) {
		cout << l << endl;
	});
}
