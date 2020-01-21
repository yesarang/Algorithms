/*
https://leetcode.com/problems/next-permutation/

Next Permutation
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
If such an arrangement is not possible, it must rearrange it as the lowest possible order (i.e., sorted in ascending order).
The replacement must be in place and use only constant extra memory.

Example 1:

Input: nums = [1,2,3]
Output: [1,3,2]
Example 2:

Input: nums = [3,2,1]
Output: [1,2,3]
Example 3:

Input: nums = [1,1,5]
Output: [1,5,1]
Example 4:

Input: nums = [1]
Output: [1]

Constraints:
1 <= nums.length <= 100
0 <= nums[i] <= 100
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool nextPermutation(vector<int>& nums)
{
    int l = nums.size() - 2;

    // backward search for decreasing number
    while (l >= 0 && nums[l] >= nums[l + 1]) {
        --l;
    }

    bool keep_going = true;
    if (l >= 0) {
        // Now, elements from l + 1, nums.size() - 1 are reverse sorted.
        // So, if we find the first element which < nums[l], then
        // that's the place where we put nums[l], maintaining
        // reverse sorted order. And then, we can reverse those
        // reverse sorted range to get the next permutation.
        int r = nums.size() - 1;
        while (r >= 0 && nums[r] <= nums[l]) {
            --r;
        }

        swap(nums[l], nums[r]);
    }
    else {
        keep_going = false;
    }

    ++l;
    reverse(nums.begin() + l, nums.end());

    return keep_going;
}

ostream& operator<<(ostream& os, const vector<int>& nums)
{
    for (auto n : nums) {
        os << n << ", ";
    }

    return os;
}

int main()
{
    vector<int> nums{ 1, 2, 3 };

    do {
        cout << nums << endl;
    } while (nextPermutation(nums));

    cout << nums << endl;

    nums = { 1, 2, 3, 3 };
    do {
        cout << nums << endl;
    } while (nextPermutation(nums));

    cout << nums << endl;
}

