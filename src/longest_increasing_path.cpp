/*
Given an integer matrix, find the length of the longest increasing path.

From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:

Input: nums =
[
  [9,9,4],
  [6,6,8],
  [2,1,1]
]
Output: 4
Explanation: The longest increasing path is [1, 2, 6, 9].

Example 2:

Input: nums =
[
  [3,4,5],
  [3,2,6],
  [2,2,1]
]
Output: 4
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.

*/
#include <iostream>
#include <vector>
#include <functional>
#include <tuple>
#include <algorithm>

using namespace std;

int longestIncreasingPath(vector<vector<int>>& matrix) {
    int nrows = matrix.size();
    int ncols = nrows > 0 ? matrix[0].size() : 0;
    if (ncols == 0 || nrows == 0) {
        return 0;
    }

    function<vector<tuple<int, int>>(int, int, int)> get_moveable_set =
        [&](int ri, int ci, int cur_val) {
        vector<tuple<int, int>> moveable_set;

        // move east
        if (ci + 1 < ncols && matrix[ri][ci + 1] > cur_val) {
            moveable_set.push_back(make_tuple(ri, ci + 1));
        }

        // move west
        if (ci - 1 >= 0 && matrix[ri][ci - 1] > cur_val) {
            moveable_set.push_back(make_tuple(ri, ci - 1));
        }

        // move south
        if (ri + 1 < nrows && matrix[ri + 1][ci] > cur_val) {
            moveable_set.push_back(make_tuple(ri + 1, ci));
        }

        // move north
        if (ri - 1 >= 0 && matrix[ri - 1][ci] > cur_val) {
            moveable_set.push_back(make_tuple(ri - 1, ci));
        }

        return moveable_set;
    };

    vector<vector<int>> visited(nrows, vector<int>(ncols, 0));

    function<void(int, int)> dfs = [&](int ri, int ci) {
        if (visited[ri][ci] > 0) {
            return;
        }

        int max_length = 1;
        for (auto [nri, nci] : get_moveable_set(ri, ci, matrix[ri][ci])) {
            if (visited[nri][nci] == 0) {
                dfs(nri, nci);
            }
            max_length = max(max_length, visited[nri][nci] + 1);
        }

        visited[ri][ci] = max_length;
    };

    int max_length = 0;
    for (int ri = 0; ri < nrows; ++ri) {
        for (int ci = 0; ci < ncols; ++ci) {
            if (visited[ri][ci] == 0) {
                dfs(ri, ci);
            }
            max_length = max(max_length, visited[ri][ci]);
        }
    }

    return max_length;
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
    vector<vector<int>> m{
        {9,9,4},
        {6,6,8},
        {2,1,1},
    };

    cout << longestIncreasingPath(m) << endl;

    m = {};
    cout << longestIncreasingPath(m) << endl;
}