#include <iostream>
#include <vector>
#include <numeric>
#include <climits>
#include <algorithm>

using namespace std;

vector<int> nway_merge_sort(const vector<vector<int>>& sorted_vectors) {
	auto nv = sorted_vectors.size();
	vector<size_t> indexes(nv, 0);
	size_t nr = accumulate(sorted_vectors.cbegin(), sorted_vectors.cend(), 0, [](size_t sum, const auto& v) {
		return sum + v.size();
	});
	vector<int> ret(nr);

	size_t ri = 0;
	size_t nsorted = 0;
	while (nsorted < nr) {
		int imin = -1;
		int min = INT_MAX;
		for (size_t i = 0; i < nv; ++i) {
			if (indexes[i] < sorted_vectors[i].size()) {
				auto val = sorted_vectors[i][indexes[i]];
				if (imin < 0) {
					imin = i;
					min = val;
				}
				else if (val < min) {
					imin = i;
					min = val;
				}
			}
		}
		cout << "picked " << min << " from " << imin << endl;
		++(indexes[imin]);
		ret[ri++] = min;
		++nsorted;
	}

	return move(ret);
}

int main() {
	vector<vector<int>> sv{
		vector<int>{1,4,7,8,9,12,999},
		vector<int>{2,5,8,13,20},
		vector<int>{3,6,9,10,10,10,15}
	};

	auto r = nway_merge_sort(sv);
	cout << "[ ";
	for_each(r.begin(), r.end(), [](auto v) {
		cout << v << " ";
	});
	cout << "]" << endl;
}
