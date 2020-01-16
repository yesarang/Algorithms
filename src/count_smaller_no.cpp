/*
Count of Smaller Numbers After Self

You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Example:

Input: [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
*/

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

struct val_cnt {
	int val;
	int i;
	int cnt;
};

vector<int> countSmaller(const vector<int>& nums) {
	int n = nums.size();
	vector<int> ret(n);
	if (n == 0) {
		return ret;
	}

	function<vector<val_cnt>(const vector<val_cnt>&, const vector<val_cnt>&)> merge =
	[&](const vector<val_cnt>& sorted1, const vector<val_cnt>& sorted2) {
		int e1 = sorted1.size();
		int e2 = sorted2.size();

		vector<val_cnt> out(e1 + e2);

		int oi = 0, s1 = 0, s2 = 0;
		while (s1 < e1 && s2 < e2) {
			if (sorted1[s1].val > sorted2[s2].val) {
				out[oi] = sorted1[s1++];
				out[oi].cnt += e2 - s2;
				++oi;
			}
			else {
				out[oi++] = sorted2[s2++];
			}
		}

		while (s1 < e1) {
			out[oi++] = sorted1[s1++];
		}

		while (s2 < e2) {
			out[oi++] = sorted2[s2++];
		}

		return out;
	};

	function<vector<val_cnt>(vector<val_cnt>&, int, int)> merge_sort =
	[&](vector<val_cnt>& in, int s, int e) {
		if (s == e) {
			return vector<val_cnt>{ { in[s].val, s, 0 } };
		}

		int mid = (s + e) / 2;

		return merge(merge_sort(in, s, mid), merge_sort(in, mid + 1, e));
	};

	vector<val_cnt> data(n);
	for (int i = 0; i < n; ++i) {
		data[i] = { nums[i], i, 0 };
	}

	auto sorted = merge_sort(data, 0, n - 1);
	for (auto d : sorted) {
		ret[d.i] = d.cnt;
	}

	return ret;
}

template <typename T>
void print(T t) {
	cout << t;
}

template <typename T>
void print(const vector<T>& solution) {
	size_t n = solution.size();
	if (n == 0) {
		cout << "[]" << endl;
		return;
	}

	cout << "[";
	print(solution[0]);
	for (size_t i = 1; i < n; ++i) {
		cout << ",";
		print(solution[i]);
	}
	cout << "]";
}

int main() {
	vector<int> nums{ 5, 2, 6, 1 };

	print(countSmaller(nums));
	cout << endl;

	print(countSmaller({ 0, 1, 2 }));
	cout << endl;
}
