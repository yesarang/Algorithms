#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> ret;
    size_t n = nums.size();
    if (n < 4) {
        return ret;
    }

    sort(nums.begin(), nums.end());
    int cur_num = 0;
    for (size_t i = 0; i < n - 3;) {
        for (size_t j = i + 1; j < n - 2;) {
            size_t l = j + 1;
            size_t r = n - 1;

            while (l < r) {
                int sum = nums[i] + nums[j] + nums[l] + nums[r];
                if (sum < target) {
                    ++l;
                }
                else if (sum > target) {
                    --r;
                }
                else {
                    ret.push_back(vector<int>{nums[i], nums[j], nums[l], nums[r]});

                    cur_num = nums[l];
                    while (l < r && nums[l] == cur_num) {
                        ++l;
                    }

                    cur_num = nums[r];
                    while (l < r && nums[r] == cur_num) {
                        --r;
                    }
                }
            }

            cur_num = nums[j];
            while (j < n - 2 && nums[j] == cur_num) {
                ++j;
            }
        }

        cur_num = nums[i];
        while (i < n - 3 && nums[i] == cur_num) {
            ++i;
        }
    }

    return ret;
}

void print(const vector<int>& quadruple) {
    cout << "[" << quadruple[0]
        << "," << quadruple[1]
        << "," << quadruple[2]
        << "," << quadruple[3]
        << "]";
}

void print(const vector<vector<int>>& quadruples) {
    for (auto quadruple : quadruples) {
        print(quadruple);
    }
}

int main() {
    auto nums = vector<int>{ 1, 0, -1, 0, -2, 2 };
    auto quadruples = fourSum(nums, 0);
    print(quadruples);
}
