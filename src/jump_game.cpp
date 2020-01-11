#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool canJump(vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) {
        return true;
    }

    /* bottom-up dynamic programming
    vector<int> memo(n, -1);
    memo[n - 1] = 1;

    for (int i = n - 2; i >= 0; --i) {
        int njump = min(nums[i], n - 1 - i);
        for (int j = 1; j <= njump; ++j) {
            if (memo[i + j] == 1) {
                memo[i] = 1;
                break;
            }
        }
    }

    return memo[0] == 1;
    */

    vector<bool> memo(n, 0);
    int lkg = n - 1;

    for (int i = n - 2; i >= 0; --i) {
        if (i + nums[i] >= lkg) {
            lkg = i;
        }
    }

    return lkg == 0;
}

int main() {
    vector<int> nums{ 3,2,1,0,4 };

    cout << "can jump: " << canJump(nums) << endl;
}
