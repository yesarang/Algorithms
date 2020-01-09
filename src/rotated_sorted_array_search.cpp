#include <iostream>
#include <vector>
#include <functional>

using namespace std;

int search(vector<int>& nums, int target) {
    int n = nums.size();
    if (n == 0) {
        return -1;
    }

    function<int()> find_rotation_index = [&]() {
        int start = 0;
        int end = n - 1;

        if (nums[start] <= nums[end]) {
            return start;
        }

        while (start <= end) {
            int mid = (start + end) / 2;
            if (nums[mid] > nums[mid + 1]) {
                return mid + 1;
            }
            else {
                if (nums[start] > nums[mid]) {
                    end = mid - 1;
                }
                else {
                    start = mid + 1;
                }
            }
        }

        return 0;
    };

    function<int(int, int)> binary_search = [&](int start, int end) {
        if (start > end) {
            return -1;
        }

        int mid = (start + end) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        else if (nums[mid] < target) {
            return binary_search(mid + 1, end);
        }
        else {
            return binary_search(start, mid - 1);
        }
    };

    int ri = find_rotation_index();

    if (nums[ri] == target) {
        return ri;
    }
    else if (target <= nums[n - 1]) {
        return binary_search(ri + 1, n - 1);
    }
    else {
        return binary_search(0, ri - 1);
    }
}

int main() {
    vector<int> nums{ 1 };

    cout << search(nums, 0) << endl;

    nums = { 4, 5, 6, 7, 0, 1, 2 };

    cout << search(nums, 0) << endl;

    nums = { 3, 5, 1 };

    cout << search(nums, 3) << endl;

    nums = { 5, 1, 3 };

    cout << search(nums, 5) << endl;

    nums = { 4, 5, 6, 7, 8, 1, 2, 3 };

    cout << search(nums, 8) << endl;
}
