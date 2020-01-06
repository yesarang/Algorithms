#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

vector<int> searchRange(vector<int>& nums, int target) {
    size_t n = nums.size();
    if (n == 0) {
        return { -1, -1 };
    }

    function<int(int, int)> lb = [&](int s, int e) {
        if (s == e) {
             return s;
        }

        auto mid = (s + e) / 2;
        if (nums[mid] < target) {
            return lb(mid + 1, e);
        }
        else {
            return lb(s, mid);
        }
    };

    function<int(int, int)> ub = [&](int s, int e) {
        if (s == e) {
            return s;
        }

        auto mid = (s + e) / 2;
        if (nums[mid] <= target) {
            return ub(mid + 1, e);
        }
        else {
            return ub(s, mid);
        }
    };

    auto start = lb(0, n);
    auto end = ub(0, n);

    return start < end ? vector<int>{ start, end - 1 } : vector<int>{ -1, -1 };
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
    vector<int> nums{ 5,7,7,8,8,10 };

    print(searchRange(nums, 8));

    print(searchRange(nums, 6));

    nums = { 1 };

    print(searchRange(nums, 1));

    print(searchRange(nums, 100));

    nums = { 2, 2 };

    print(searchRange(nums, 2));
}
