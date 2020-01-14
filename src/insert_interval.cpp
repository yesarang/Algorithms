/*
Insert Interval

Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:

Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Example 2:

Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.
*/

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> ret;
    int n = intervals.size();
    if (n == 0) {
        ret.push_back(newInterval);
        return ret;
    }

    if (newInterval[1] < intervals[0][0]) {
        ret.push_back(newInterval);
        ret.insert(ret.end(), intervals.begin(), intervals.end());
        return ret;
    }

    function<int(int, int, int, int)> lb = [&](int s, int e, int is_or_ie, int t) {
        if (s == e) {
            return s;
        }

        int mid = (s + e) / 2;
        if (intervals[mid][is_or_ie] < t) {
            return lb(mid + 1, e, is_or_ie, t);
        }
        else {
            return lb(s, mid, is_or_ie, t);
        }
    };

    int is_or_ie = 0;   // compare interval start to newInterval's start.
    int from = lb(0, n, is_or_ie, newInterval[0]);
    if (from > 0 && newInterval[0] <= intervals[from - 1][1]) {
        --from;
    }
    ret.insert(ret.end(), intervals.begin(), intervals.begin() + from);

    is_or_ie = 1;       // compare interval end to newInterval's end.
    int to = lb(0, n, is_or_ie, newInterval[1]);
    if (to < n && newInterval[1] < intervals[to][0]) {
        --to;
    }
    
    int merged_interval_start = from == n
        ? newInterval[0]
        : min(newInterval[0], intervals[from][0]);

    int merged_interval_end = to == n
        ? newInterval[1]
        : max(newInterval[1], intervals[to][1]);

    ret.push_back({ merged_interval_start, merged_interval_end });

    if (to < n) {
        ret.insert(ret.end(), intervals.begin() + to + 1, intervals.end());
    }

    return ret;
}

template <typename T>
void print(T t) {
    cout << t;
}

template <typename T>
void print(const vector<T>& solution) {
    size_t n = solution.size();
    if (n == 0) {
        cout << "[]" << endl;
        return;
    }

    cout << "[";
    print(solution[0]);
    for (size_t i = 1; i < n; ++i) {
        cout << ",";
        print(solution[i]);
    }
    cout << "]";
}

int main() {
    vector<vector<int>> intervals{{1,3},{6,9}};
    vector<int> new_interval{2,5};

    print(insert(intervals, new_interval));
    cout << endl;

    intervals = { { 1,5 } };
    new_interval = { 2,3 };
    print(insert(intervals, new_interval));
    cout << endl;

    intervals = { { 1,5 } };
    new_interval = { 0,0 };
    print(insert(intervals, new_interval));
    cout << endl;
}
