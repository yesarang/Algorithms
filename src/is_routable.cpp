// Given a directed graph, design an algorithm to find out whether there is a route
// between two nodes.
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

bool is_routable(int start, int dest, const vector<vector<int>>& graph) {
	vector<bool> visited(graph.size(), false);
	queue<int> q;
	q.push(start);
	while (!q.empty()) {
		int node = q.front();
		if (node == dest) {
			return true;
		}
		q.pop();
		visited[node] = true;
		for (auto n : graph[node]) {
			if (!visited[n]) {
				q.push(n);
			}
		}
	}
	return false;
}

int main() {
	vector<vector<int>> graph;
	graph.push_back({ 1 });			// 0
	graph.push_back({ 2, 3, 4 });	// 1
	graph.push_back({});			// 2
	graph.push_back({ 2, 5 });		// 3
	graph.push_back({ 6 });			// 4
	graph.push_back({});			// 5
	graph.push_back({ 1, 7 });		// 6
	graph.push_back({});			// 7

	assert(is_routable(1, 5, graph));
	cout << "1 -> 5 is routable" << endl;

	assert(is_routable(0, 7, graph));
	cout << "0 -> 7 is routable" << endl;

	assert(!is_routable(3, 7, graph));
	cout << "3 -> 7 is not routable" << endl;

	assert(is_routable(2, 2, graph));
	cout << "2 -> 2 is routable" << endl;

	assert(is_routable(6, 5, graph));
	cout << "6 -> 5 is routable" << endl;

	assert(!is_routable(7, 5, graph));
	cout << "7 -> 5 is not routable" << endl;

	return 0;
}
