#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <unordered_set>

using namespace std;

vector<vector<int>> permuteUnique(vector<int>& nums) {
    size_t n = nums.size();
    vector<vector<int>> ret;
    if (n == 0) {
        return ret;
    }

    function<void (size_t)> backtrack = [&](size_t start) {
        if (start == n - 1) {
            ret.push_back(nums);
            return;
        }

        unordered_set<int> used;
        for (size_t i = start; i < n; ++i) {
            if (used.count(nums[i]) > 0) {
                continue;
            }
            used.insert(nums[i]);

            swap(nums[i], nums[start]);
            backtrack(start + 1);
            swap(nums[i], nums[start]);
        }
    };

    sort(nums.begin(), nums.end());
    backtrack(0);

    return ret;
}

void print(const vector<int>& solution) {
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

void print(const vector<vector<int>>& solutions) {
    for (auto solution : solutions) {
        print(solution);
    }
}

int main() {
    vector<int> nums1 = { 1, 1, 2 };
    vector<int> nums2 = { 0, 1, 0, 0, 9 };
    vector<int> nums3 = { 1, 2, 3 };

    print(permuteUnique(nums1));
    print(permuteUnique(nums2));
    print(permuteUnique(nums3));
}
