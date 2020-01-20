#include <iostream>
#include <vector>
#include <functional>

using namespace std;

int findInMountainArray(int target, const vector<int>& mountainArr) {
    function<int(int, int)> peak_find_helper = [&](int s, int e) {
        if (s == e) {
            return s;
        }

        int mid = (s + e) / 2;
        // going up, choose right side
        if (mountainArr[mid] < mountainArr[mid + 1]) {
            return peak_find_helper(mid + 1, e);
        }
        // going down, choose left side
        else {
            return peak_find_helper(s, mid);
        }
    };

    function<int(int, int, bool)> target_find_helper = [&](int s, int e, bool is_going_up) {
        if (s > e) {
            return -1;
        }

        int mid = (s + e) / 2;
        int ch = mountainArr[mid];
        if (ch == target) {
            return mid;
        }

        if (is_going_up) {
            // we're already over target, so, choose left side
            if (ch > target) {
                return target_find_helper(s, mid - 1, is_going_up);
            }
            // we're not target yet, choose right side
            else {
                return target_find_helper(mid + 1, e, is_going_up);
            }
        }
        // going down, choose left side
        else {
            // we're below target, so, choose left side
            if (ch < target) {
                return target_find_helper(s, mid - 1, is_going_up);
            }
            // we're not there yet, so, choose right side
            else {
                return target_find_helper(mid + 1, e, is_going_up);
            }
        }
    };

    auto pi = peak_find_helper(0, mountainArr.size() - 1);
    auto ph = mountainArr[pi];
    if (ph == target) {
        return pi;
    }
    else if (ph < target) {
        return -1;
    }
    else {
        auto ti = target_find_helper(0, pi - 1, true);
        return ti >= 0 ? ti : target_find_helper(pi + 1, mountainArr.size() - 1, false);
    }
}

int main() {
    vector<int> m{ 1,2,3,4,5,3,1 };
    cout << findInMountainArray(3, m) << endl;

    m = { 1,5,2 };
    cout << findInMountainArray(0, m) << endl;

    cout << findInMountainArray(1, m) << endl;
}
