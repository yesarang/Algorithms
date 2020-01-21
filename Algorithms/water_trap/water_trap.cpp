/*
leetcode: https://leetcode.com/problems/trapping-rain-water/

Given n non-negative integers representing an elevation map where the width of each bar is 1,
compute how much water it can trap after raining.

Example 1:
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1].
In this case, 6 units of rain water (blue section) are being trapped.

Example 2:
Input: height = [4,2,0,3,2,5]
Output: 9

*/

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

int trap_dp(vector<int>& height)
{
    vector<int> rmax_heights(height.size(), 0);
    int rmax_h = 0;
    for (int i = height.size() - 1; i >= 0; --i) {
        rmax_heights[i] = rmax_h = max(rmax_h, height[i]);
    }

    int trapped_water = 0;
    int lmax_h = 0;
    for (int i = 0; i < height.size(); ++i) {
        lmax_h = max(lmax_h, height[i]);
        trapped_water += min(lmax_h, rmax_heights[i]) - height[i];
    }

    return trapped_water;
}

int trap_stack(vector<int>& height)
{
    stack<int> s;

    int tw = 0;
    for (int i = 0; i < height.size(); ++i) {
        while (!s.empty() && height[i] > height[s.top()]) {
            auto bottom = s.top();
			s.pop();

            if (s.empty()) {
                break;
            }

            auto lh = height[s.top()];
            auto dist = i - s.top() - 1;
			tw += (min(lh, height[i]) - height[bottom]) * dist;
        }

        s.push(i);
    }

    return tw;
}

int main()
{
    vector<int> heights{ 0,1,0,2,1,0,1,3,2,1,2,1 };

    cout << trap_dp(heights) << endl;
    cout << trap_stack(heights) << endl;
}

