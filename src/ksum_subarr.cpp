#include <iostream>
#include <vector>

using namespace std;

int subarraySum(vector<int>& nums, int k) {
    int n = nums.size();
    if (n == 0 || k == 0) {
        return 0;
    }

    int narr = 0;
    int left = 0, right = 0;
    int sum = nums[0];
    while (right < n) {
        if (sum <= k) {
            if (sum == k) {
                ++narr;
            }
            sum += nums[++right];
        }
        else {
            sum -= nums[left++];
        }
    }

    return narr;
}

int main() {
    vector<int> nums{ 1, 2, 3 };
    cout << subarraySum(nums, 3) << endl;
}
