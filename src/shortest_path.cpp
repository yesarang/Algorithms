// Given a directed graph, design an algorithm to find out a shortest path
// between two nodes.
// This code should be compiled with c++11
// check out whether this code works properly at http://ideone.com/7vJ1HT
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int>
bfs2(const vector<vector<int> >& graph, int start) {
    vector<bool> discovered(graph.size(), false);
    vector<int> parent(graph.size(), -1);
    queue<int> q;
    
    q.push(start);
    discovered[start] = true;
	// start node's parent is itself
    parent[start] = start;
    cout << "discovered " << start << endl;
    
    while (!q.empty()) {
        int here = q.front();
        cout << "visiting " << here << endl;
        q.pop();
        for (vector<int>::const_iterator i = graph[here].begin(); i != graph[here].end(); ++i) {
            int there = *i;
            if (!discovered[there]) {
                q.push(there);
                discovered[there] = true;
                parent[there] = here;
                cout << "discovered " << there << endl;
            }
        }
    }
    
    return parent;
}

vector<int>
shortest_path_of(const vector<int>& parent, int target) {
    vector<int> path(1, target);
	// start node's parent is itself
    while (target != parent[target]) {    // from target to start
        target = parent[target];
        path.push_back(target);
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<int>
get_shortest_path(const vector<vector<int>>& graph, int start, int target) {
	vector<int> parent = bfs2(graph, start);
	return shortest_path_of(parent, target);
}

int main()
{
	vector<vector<int> > g1{
		vector<int>{1, 2},
		vector<int>{0, 2, 6},
		vector<int>{0, 1, 3, 5},
		vector<int>{2, 4},
		vector<int>{3, 5, 6},
		vector<int>{2, 4, 6},
		vector<int>{1, 4, 6}
	};

    vector<int> spath = get_shortest_path(g1, 0, 4);
    for (auto v : spath) {
        cout << v << " ";
    }
    cout << endl;

    spath = get_shortest_path(g1, 0, 5);
    for (auto v : spath) {
        cout << v << " ";
    }
    cout << endl;
   
    spath = get_shortest_path(g1, 1, 4);
    for (auto v : spath) {
        cout << v << " ";
    }
    cout << endl;
    
    return 0;
}
