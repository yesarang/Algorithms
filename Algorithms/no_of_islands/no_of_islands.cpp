#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<pair<int, int>> neighbors(
    const vector<vector<char>>& grid,
    vector<vector<bool>>& visited,
    int i, int j)
{
    const pair<int, int> dirs[4] = {
        pair<int,int>(-1,  0), // up
        pair<int,int>( 0,  1), // right
        pair<int,int>( 1,  0), // down
        pair<int,int>( 0, -1), // left
    };

    const int m = grid.size();
    const int n = grid[0].size();

    vector<pair<int, int>> ret;
    for (auto dir : dirs) {
        auto ni = i + dir.first;
        auto nj = j + dir.second;
        if (0 <= ni && ni < m && 0 <= nj && nj < n && grid[ni][nj] == '1') {
            ret.push_back(make_pair(ni, nj));
        }
    }

    return ret;
}

void bfs(const vector<vector<char>>& grid, vector<vector<bool>>& visited, int i, int j) {
    queue<pair<int, int>> q;
    q.push(make_pair(i, j));
    visited[i][j] = true;

    while (!q.empty()) {
        auto [ni, nj] = q.front();
        q.pop();

        for (auto [xni, xnj] : neighbors(grid, visited, ni, nj)) {
            if (!visited[xni][xnj]) {
                q.push(make_pair(xni, xnj));
                visited[xni][xnj] = true;
            }
        }
    }
}

int numIslands(vector<vector<char>>& grid) {
    if (grid.size() == 0 || grid[0].size() == 0) {
        return 0;
    }

    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
    int nislands = 0;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (!visited[i][j] && grid[i][j] == '1') {
                bfs(grid, visited, i, j);
                ++nislands;
            }
        }
    }

    return nislands;
}

int main() {
    vector<vector<char>> grid{
        vector<char>{'1','1','1','1','0'},
        vector<char>{'1','1','0','1','0'},
        vector<char>{'1','1','0','0','0'},
        vector<char>{'0','0','0','0','0'},
    };

    cout << numIslands(grid) << endl;
}

