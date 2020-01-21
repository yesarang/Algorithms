#include <vector>
#include <iostream>

using namespace std;

int find_peak_helper(const vector<int>& nums, int s, int e) {
    if (s == e) {
        return s;
    }

    int m = (s + e) / 2;

    return (nums[m] < nums[m + 1])
        ? find_peak_helper(nums, m + 1, e)
        : find_peak_helper(nums, s, m);
}

int findPeakElement(vector<int>& nums) {
    return find_peak_helper(nums, 0, nums.size() - 1);
}

int main()
{
    vector<int> nums1{ 1,2,3,4 };
    vector<int> nums2{ 1,2,1,3,5,6,4 };

    cout << findPeakElement(nums1) << endl;
    cout << findPeakElement(nums2) << endl;
}

