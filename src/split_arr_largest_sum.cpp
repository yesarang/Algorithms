/*
Given an array which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays. Write an algorithm to minimize the largest sum among these m subarrays.
Note:
If n is the length of array, assume the following constraints are satisfied:
    • 1 ≤ n ≤ 1000
    • 1 ≤ m ≤ min(50, n)
Examples:
Input:
nums = [7,2,5,10,8]
m = 2
Output:
18
Explanation:
There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int splitArray(vector<int>& nums, int m) {
    int n = nums.size();

    vector<vector<int>> f(n + 1, vector<int>(m + 1, INT_MAX));
    vector<int> sub(n + 1, 0);

    for (int i = 0; i < n; i++) {
        sub[i + 1] = sub[i] + nums[i];
    }

    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < i; k++) {
                f[i][j] = min(f[i][j], max(f[k][j - 1], sub[i] - sub[k]));
            }
        }
    }

    return f[n][m];
}

int main() {
    auto nums = vector<int>{ 7,2,5,10,8 };

    cout << splitArray(nums, 2) << endl;
}
