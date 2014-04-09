#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int>
bfs(const vector<vector<int> >& graph, int start) {
    vector<int> order;
    vector<bool> discovered(graph.size(), false);
    queue<int> q;
    
    q.push(start);
    discovered[start] = true;
    cout << "discovered " << start << endl;
    
    while (!q.empty()) {
        int here = q.front();
        cout << "visiting " << here << endl;
        q.pop();
        order.push_back(here);
        for (int i = 0; i < graph[here].size(); ++i) {
            if (graph[here][i] > 0) {
                int there = i;
                if (!discovered[there]) {
                    q.push(there);
                    discovered[there] = true;
                    cout << "discovered " << there << endl;
                }
            }
        }
    }
    
    return order;
}

int main()
{
    int a1[6][6] = {
        {0,1,1,0,0,0},
        {1,0,1,0,0,0},
        {1,1,0,1,0,1},
        {0,0,1,0,1,0},
        {0,0,0,1,0,1},
        {0,0,1,0,1,0}
    };

    vector<vector<int> > g1;
    for (int i = 0; i < 6; ++i) {
        g1.push_back(vector<int>(&a1[i][0], &a1[i][6]));
    }
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            cout << g1[i][j] << " ";
        }
        cout << endl;
    }
    
    vector<int> order = bfs(g1, 0);
    for (vector<int>::iterator i = order.begin(); i < order.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
    
    return 0;
}

