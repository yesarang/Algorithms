// check out whether this code works properly at http://ideone.com/4SnJQz
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
	vector<Node*> siblings_;
	int val_;
	Node(int val, const vector<Node*>& siblings = vector<Node*>())
		: val_(val), siblings_(siblings)
	{}
};

vector<int> get_path_to(Node* node, int target) {
	if (node->val_ == target) {
		return vector<int>(1, node->val_);
	}
	for (auto n : node->siblings_) {
		vector<int> path = get_path_to(n, target);
		if (!path.empty()) {
			path.push_back(node->val_);
			return path;
		}
	}
	return vector<int>();
}

vector<int> get_path_btwn(Node* node, int start, int end) {
	vector<int> path = get_path_to(node, start);
	vector<int> path2 = get_path_to(node, end);
	if (path.empty() || path2.empty()) {
		return vector<int>();
	}
	reverse(path2.begin(), path2.end());
	path.insert(path.end(), ++path2.begin(), path2.end());
	return path;
}

int main() {
	// handcraft a tree
	vector<Node*> siblings5(1, new Node(8));
	Node* node5 = new Node(5, siblings5);
	vector<Node*> siblings2(1, node5);
	siblings2.push_back(new Node(6));
	Node* node2 = new Node(2, siblings2);
	vector<Node*> siblings3(1, new Node(7));
	Node* node3 = new Node(3, siblings3);
	vector<Node*> siblings1(1, node2);
	siblings1.push_back(node3);
	siblings1.push_back(new Node(4));
	Node* node1 = new Node(1, siblings1);

	vector<int> path1 = get_path_to(node1, 8);
	auto f = [](int v) {
		cout << v << " ";
	};
	for_each(path1.begin(), path1.end(), f);
	cout << endl;

	vector<int> path2 = get_path_to(node1, 7);
	for_each(path2.begin(), path2.end(), f);
	cout << endl;

	vector<int> path3 = get_path_btwn(node1, 8, 7);
	for_each(path3.begin(), path3.end(), f);
	cout << endl;

	// negative test case
	vector<int> path4 = get_path_btwn(node1, 8, 9);
	if (path4.empty()) {
		printf("no path between %d and %d", 8, 9);
	}
	else {
		for_each(path4.begin(), path4.end(), f);
		cout << endl;
	}
	return 0;
}
