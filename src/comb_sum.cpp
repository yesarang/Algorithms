#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> r;
    auto n = candidates.size();

    if (n == 0) {
        return r;
    }

    function<void(vector<int>&, size_t, int)> impl =
        [&](vector<int>& comb, size_t cur_pos, int target) {
        if (target == 0) {
            r.push_back(comb);
            return;
        }

        if (target < candidates[cur_pos]) {
            return;
        }

        for (size_t i = cur_pos; i < n; ++i) {
            auto cur_num = candidates[i];
            comb.push_back(cur_num);
            impl(comb, i, target - cur_num);
            comb.pop_back();
        }
    };

    sort(candidates.begin(), candidates.end());
    vector<int> comb;
    impl(comb, 0, target);

    return r;
}

void print(const vector<int>& comb) {
    cout << "[";
    for (size_t i = 0; i < comb.size(); ++i) {
        cout << comb[i];
        cout << (i < comb.size() - 1 ? "," : "]");
    }
}

void print(const vector<vector<int>>& combs) {
    for (size_t i = 0; i < combs.size(); ++i) {
        print(combs[i]);
        if (i < combs.size() - 1) {
            cout << ",";
        }
    }
}

int main() {
    auto candidates = vector<int>{ 2,3,6,7 };
    print(combinationSum(candidates, 7));
}
