/*
You may recall that an array A is a mountain array if and only if:
    • A.length >= 3
    • There exists some i with 0 < i < A.length - 1 such that:
        ○ A[0] < A[1] < ... A[i-1] < A[i]
        ○ A[i] > A[i+1] > ... > A[A.length - 1]
Given a mountain array mountainArr, return the minimum index such that mountainArr.get(index) == target.  If such an index doesn't exist, return -1.
You can't access the mountain array directly.  You may only access the array using a MountainArray interface:
    • MountainArray.get(k) returns the element of the array at index k (0-indexed).
    • MountainArray.length() returns the length of the array.
Submissions making more than 100 calls to MountainArray.get will be judged Wrong Answer.  Also, any solutions that attempt to circumvent the judge will result in disqualification.
 
Example 1:
Input: array = [1,2,3,4,5,3,1], target = 3
Output: 2
Explanation: 3 exists in the array, at index=2 and index=5. Return the minimum index, which is 2.
Example 2:
Input: array = [0,1,2,4,2,1], target = 3
Output: -1
Explanation: 3 does not exist in the array, so we return -1.
 
Constraints:
    1. 3 <= mountain_arr.length() <= 10000
    2. 0 <= target <= 10^9
    3. 0 <= mountain_arr.get(index) <= 10^9
*/

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
