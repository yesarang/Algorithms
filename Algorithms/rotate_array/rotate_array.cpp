#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void rotate_array(vector<int>& v, int k) {
	int sz = v.size();
	int nrotated = 0;
	for (int s = 0; nrotated < sz; ++s) {
		int t1 = v[s];
		int ni = (s + k) % sz;
		int t2 = v[ni];
		do {
			v[ni] = t1;
			++nrotated;
			ni = (ni + k) % sz;
			t1 = t2;
			t2 = v[ni];
		} while (s != ni);
		v[s] = t1;
		++nrotated;
	}
}

int main() {
	vector<int> v{ 1,2,3,4,5,6,7,8 };
	rotate_array(v, 3);
	for_each(v.begin(), v.end(), [](auto v) {
		cout << v << " ";
	});
	cout << endl;

	v = { 1,2,3,4,5,6,7,8 };
	rotate_array(v,1);
	for_each(v.begin(), v.end(), [](auto v) {
		cout << v << " ";
	});
	cout << endl;

	v = { 1,2,3,4,5,6,7,8 };
	rotate_array(v, 2);
	for_each(v.begin(), v.end(), [](auto v) {
		cout << v << " ";
	});
	cout << endl;

	v = { 1,2,3,4,5,6,7,8,9,10 };
	rotate_array(v, 3);
	for_each(v.begin(), v.end(), [](auto v) {
		cout << v << " ";
	});
	cout << endl;
}
