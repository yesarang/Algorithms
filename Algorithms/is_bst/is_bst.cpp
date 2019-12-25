#include <iostream>
#include <tuple>
#include <functional>
#include <climits>
#include <cassert>
#include <algorithm>

using namespace std;

struct node {
	int v;
	node* l;
	node* r;
};

bool is_bst(node* t) {
	function<tuple<bool, int, int>(node*)> impl = [&](node* n) {
		if (!n) {
			return make_tuple(true, INT_MAX, INT_MIN);
		}

		auto[lt_bst, lmin, lmax] = impl(n->l);
		auto[rt_bst, rmin, rmax] = impl(n->r);
		auto is_bst = lt_bst && rt_bst && lmax <= n->v && n->v <= rmin;

		return make_tuple(is_bst, (is_bst ? min(n->v, lmin) : INT_MAX), (is_bst ? max(n->v, rmax) : INT_MIN));
	};

	auto[is_bst, _1, _2] = impl(t);
	return is_bst;
}

int main() {
	node* t =
		new node{ 10,
			new node{ 5,
				new node{ 2, nullptr, nullptr },
				new node{ 6, nullptr, nullptr }
			},
			new node{ 15,
				new node{ 12, nullptr, nullptr },
				new node{ 19, nullptr, nullptr }
			}
		};
	assert(is_bst(t));

	node* t2 =
		new node{ 16,
			new node{ 5,
				new node{ 2, nullptr, nullptr },
				new node{ 6, nullptr, nullptr }
			},
			new node{ 15,
				new node{ 12, nullptr, nullptr },
				new node{ 19, nullptr, nullptr }
			}
		};
	assert(!is_bst(t2));
}
