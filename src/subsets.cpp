// 9.4 Write a method to return all subsets of a set
#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<int> convert_to_set(int n, const vector<int>& org_set) {
	vector<int> new_set;
	for (unsigned i = 0; i < org_set.size(); ++i) {
		if ((n >> i) & 0x01) {
			new_set.push_back(org_set[i]);
		}
	}

	return new_set;
}

vector<vector<int>> get_all_subsets(const vector<int>& org_set) {
	vector<vector<int>> vset;
	int max = 0x1 << org_set.size();
	for (int i = 0; i < max; ++i) {
		vset.push_back(convert_to_set(i, org_set));
	}
	return vset;
}

vector<set<int>> get_all_subsets2(set<int> org_set) {
	if (org_set.empty()) {
		return { {} };
	}
	int elem = *(org_set.begin());
	org_set.erase(org_set.begin());
	vector<set<int>> ret = get_all_subsets2(org_set);
	int sz = ret.size();
	for (int i = 0; i < sz; ++i) {
		set<int> ts(ret[i]);
		ts.insert(elem);
		ret.push_back(ts);
	}

	return ret;
}

void print_set(const vector<int>& set) {
	for (auto e : set) {
		cout << e << " ";
	}
	cout << endl;
}

void print_set(const set<int>& s) {
	for (auto e : s) {
		cout << e << " ";
	}
	cout << endl;
}

int main() {
	vector<int> s{ 1, 2, 3 };
	vector<vector<int>> vs = get_all_subsets(s);
	for (auto ss : vs) {
		print_set(ss);
	}

	set<int> s1{ 1, 2, 3, };
	vector<set<int>> vs2 = get_all_subsets2(s1);
	for (auto ss : vs2) {
		print_set(ss);
	}

	return 0;
}
