#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double findMedianSortedArrays(const vector<int>& nums1, const vector<int>& nums2) {
    const int n = nums1.size();
    const int m = nums2.size();

    if (n > m) {
        return findMedianSortedArrays(nums2, nums1);
    }

    const int tn = n + m;
    int s = 0;
    int e = n;

    while (s <= e) {
        auto px = (s + e) / 2;
        auto py = (tn + 1) / 2 - px;

        auto max_lx = px == 0 ? INT_MIN : nums1[px - 1];
        auto max_ly = py == 0 ? INT_MIN : nums2[py - 1];
        auto min_rx = px == n ? INT_MAX : nums1[px];
        auto min_ry = py == m ? INT_MAX : nums2[py];

        auto max_l = max(max_lx, max_ly);
        auto min_r = min(min_rx, min_ry);

        if (max_l <= min_r) {
            if (tn % 2) {
                return max_l;
            }
            else {
                return (max_l + min_r) / 2.0;
            }
        }
        else if (min_rx < max_ly) {
            s = px + 1;
        }
        else {
            e = px - 1;
        }
    }

    return 0.0;
}

int main() {
    cout << findMedianSortedArrays({ 1, 3, 5, 7 }, { 2, 4, 6, 8 }) << endl;

    cout << findMedianSortedArrays({ 1, 2, 3 }, { 4, 5, 6 }) << endl;

    cout << findMedianSortedArrays({ 1, 2 }, { 4, 5, 6 }) << endl;
}
