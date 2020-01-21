#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

vector<pair<int, int>> neighbors(const vector<vector<int>>& grid, int i, int j) {
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
        if (0 <= ni && ni < m && 0 <= nj && nj < n && grid[ni][nj] == 0) {
            ret.push_back(make_pair(ni, nj));
        }
    }

    return ret;
}

void bfs(
    const vector<vector<int>>& grid,
    int i, int j,
    vector<vector<int>>& nreached_buildings,
    vector<vector<int>>& sum_dist)
{
    queue<tuple<int /*i*/, int /*j*/, int /*dist*/>> q;
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

    q.push(make_tuple(i, j, 0));
    visited[i][j] = true;

    while (!q.empty()) {
        auto [ni, nj, dist] = q.front();
        q.pop();

        for (auto [xni, xnj] : neighbors(grid, ni, nj)) {
            if (!visited[xni][xnj]) {
                q.push(make_tuple(xni, xnj, dist + 1));
                visited[xni][xnj] = true;
                nreached_buildings[xni][xnj]++;
                sum_dist[xni][xnj] += (dist + 1);
            }
        }
    }
}

int shortestDistance(vector<vector<int>>& grid)
{
    if (grid.size() == 0 || grid[0].size() == 0) {
        return -1;
    }

    vector<vector<int>> nreached_buildings(grid.size(), vector<int>(grid[0].size(), 0));
    vector<vector<int>> sum_dist(grid.size(), vector<int>(grid[0].size(), 0));

    int nbuildings = 0;
    bool found = false;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == 1) {
                ++nbuildings;
                bfs(grid, i, j, nreached_buildings, sum_dist);
            }
        }
    }

    int min_dist = INT_MAX;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == 0 && nreached_buildings[i][j] == nbuildings) {
                found = true;
                min_dist = min(min_dist, sum_dist[i][j]);
            }
        }
    }

    return found ? min_dist : -1;
}

int main()
{
    vector<vector<int>> grid{ {1, 0, 2, 0, 1}, {0, 0, 0, 0, 0}, {0, 0, 1, 0, 0} };

    cout << shortestDistance(grid) << endl;
}
