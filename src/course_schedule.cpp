#include <iostream>
#include <vector>
#include <functional>

using namespace std;

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> g(numCourses);
    for (auto p : prerequisites) {
        auto post = p[0];
        auto pre = p[1];
        g[pre].push_back(post);
    }

    vector<int> ret(numCourses, 0);
    int ti = numCourses - 1;
    vector<bool> visited(numCourses, false);
    vector<bool> sorted(numCourses, false);

    function<bool(int)> dfs = [&](int cid) {
        visited[cid] = true;
        for (auto adj_cid : g[cid]) {
            if (visited[adj_cid] && !sorted[adj_cid]) {
                return false;
            }
            if (!visited[adj_cid] && !dfs(adj_cid)) {
                return false;
            }
        }

        ret[ti] = cid;
        --ti;
        sorted[cid] = true;

        return true;
    };

    bool cycle_detected = false;
    for (int cid = 0; cid < numCourses; ++cid) {
        if (!visited[cid] && !dfs(cid)) {
            cycle_detected = true;
            break;
        }
    }

    if (cycle_detected) {
        return vector<int>();
    }
    else {
        return ret;
    }
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
    vector<vector<int>> prereq = {
        { 1, 0 }
    };

    auto top_order = findOrder(2, prereq);
    print(top_order);
}
