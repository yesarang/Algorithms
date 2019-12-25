// Given a directed graph, design an algorithm to find out whether there is a route
// between two nodes.
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

bool is_routable(int start, int dest, const vector<vector<int>>& g)
{
	vector<bool> visited(g.size(), false);
	queue<int> q;

	q.push(start);
	visited[start] = true;

	while (!q.empty()) {
		auto n = q.front();
		q.pop();
		if (n == dest) {
			return true;
		}

		for (auto nn : g[n]) {
			if (!visited[nn]) {
				q.push(nn);
				visited[nn] = true;
			}
		}
	}

	return false;
}

int main()
{
	vector<vector<int>> g;
	g.emplace_back(vector<int>{1});
	g.emplace_back(vector<int>{2, 3});
	g.emplace_back(vector<int>{3});
	g.emplace_back(vector<int>{2, 5});
	g.emplace_back(vector<int>{6});
	g.emplace_back(vector<int>{6});
	g.emplace_back(vector<int>{});

	assert(is_routable(1, 6, g));
}