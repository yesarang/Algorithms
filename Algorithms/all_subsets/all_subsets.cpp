// Write a method to return all subsets of a set
#include <iostream>
#include <cassert>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

using vs = vector<int>;

vector<vs> generate_all_subsets(const vs& s) {
	vector<vs> memo;

	function <void(size_t)> impl = [&](size_t nelem) {
		if (nelem == 0) {
			memo.push_back(vs());
			return;
		}

		impl(nelem - 1);
		// To avoid iter invalidation while pushing back additional elements.
		memo.reserve(memo.size() * 2);
		for_each(memo.cbegin(), memo.cend(), [&](const auto& gs) {
			vs ns(gs);
			ns.push_back(s[nelem - 1]);
			memo.push_back(ns);
		});
	};

	impl(s.size());
	return move(memo);
}

int main() {
	auto print_set = [](const vs& s) {
		cout << "[";
		if (s.size() > 0) {
			cout << *s.cbegin();
			for_each(++s.cbegin(), s.cend(), [](auto e) {
				cout << " " << e;
			});
		}
		cout << "]" << endl;
	};

	auto r = generate_all_subsets(vs({ 1,2,3 }));
	for_each(r.cbegin(), r.cend(), [print_set](const auto& s) {
		print_set(s);
	});

	r = generate_all_subsets(vs({ 1,2,3,4,5 }));
	for_each(r.cbegin(), r.cend(), [print_set](const auto& s) {
		print_set(s);
	});
}
