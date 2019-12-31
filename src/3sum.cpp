#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> ret;

    size_t n = nums.size();
    for (size_t i = 0; i < n - 2;) {
        size_t l = i + 1;
        size_t r = n - 1;
        int target = -nums[i];

        while (l < r) {
            int sum = nums[l] + nums[r];
            if (sum < target) {
                ++l;
            }
            else if (sum > target) {
                --r;
            }
            else {
                vector<int> triple{ nums[i], nums[l], nums[r] };
                ret.push_back(triple);
                while (l < r && nums[l] == triple[1]) {
                    ++l;
                }
                while (l < r && nums[r] == triple[2]) {
                    --r;
                }
            }
        }

        int num = nums[i];
        while (i < n - 2 && nums[i] == num) {
            ++i;
        }
    }

    return ret;
}

void print(const vector<int>& triple) {
    cout << "[" << triple[0]
        << "," << triple[1]
        << "," << triple[2]
        << "]";  
}

void print(const vector<vector<int>>& triples) {
    for (auto triple : triples) {
        print(triple);
    }
}

int main() {
    auto nums = vector<int>{ -1, 0, 1, 2, -1, 4 };
    auto triples = threeSum(nums);
    print(triples);
}
