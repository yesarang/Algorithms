/*
Maximum Product Subarray

Given an integer array nums, find the contiguous subarray within an array (containing at least one number) which has the largest product.

Example 1:

Input: [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.

Example 2:

Input: [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxProduct(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) {
        return 0;
    }

    int prev_max_prod = 1;
    int prev_min_prod = 1;
    int max_prod = INT_MIN;

    for (auto v : nums) {
        auto cur_max_prod = max({ prev_max_prod * v, prev_min_prod * v, v });
        auto cur_min_prod = min({ prev_max_prod * v, prev_min_prod * v, v });

        max_prod = max(max_prod, cur_max_prod);

        prev_max_prod = cur_max_prod;
        prev_min_prod = cur_min_prod;
    }

    return max_prod;
}

int main() {
    auto nums = vector<int>{ -4, -3, -2 };

    cout << maxProduct(nums) << endl;
}
