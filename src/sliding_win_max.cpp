/*
Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right.
You can only see the k numbers in the window. Each time the sliding window moves right by one position. Return the max sliding window.

Example:

Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
Output: [3,3,5,5,6,7]
Explanation:

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

Note:
You may assume k is always valid, 1 ≤ k ≤ input array's size for non-empty array.

Follow up:
Could you solve it in linear time?
*/

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
	vector<int> ret;
	int n = nums.size();
	if (n == 0) {
		return ret;
	}

	deque<int> d;
	for (int i = 0; i < k; ++i) {
		while (!d.empty() && nums[d.back()] < nums[i]) {
			d.pop_back();
		}
		d.push_back(i);
	}
	ret.push_back(nums[d.front()]);

	for (int i = k; i < n; ++i) {
		if (d.front() < i - k + 1) {
			d.pop_front();
		}
		while (!d.empty() && nums[d.back()] < nums[i]) {
			d.pop_back();
		}
		d.push_back(i);
		ret.push_back(nums[d.front()]);
	}

	return ret;
}

template <typename T>
void print(const vector<T>& solution) {
	size_t n = solution.size();
	if (n == 0) {
		cout << "[]" << endl;
		return;
	}

	cout << "[" << solution[0];
	for (size_t i = 1; i < n; ++i) {
		cout << "," << solution[i];
	}
	cout << "]" << endl;
}

int main() {
	vector<int> nums{ 1,3,-1,-3,5,3,6,7 };
	print(maxSlidingWindow(nums, 3));

	nums = { -7,-8,7,5,7,1,6,0 };
	print(maxSlidingWindow(nums, 4));
}

