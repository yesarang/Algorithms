// check out whether this code works properly at http://ideone.com/NUrwAM
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

struct Node {
	vector<Node*> siblings_;
	int val_;
	Node(int val, const vector<Node*>& siblings = vector<Node*>())
		: val_(val), siblings_(siblings)
	{}
};

int get_depth(Node* node) {
	if (node->siblings_.empty()) {
		return 0;
	}
	int depth = 0;
	for (auto n : node->siblings_) {
		depth = max(depth, get_depth(n));
	}
	return depth + 1;
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
	Node* node4 = new Node(4);
	siblings1.push_back(node4);
	Node* node1 = new Node(1, siblings1);

	printf("Total tree depth is %d\n", get_depth(node1));
	printf("Left tree depth is %d\n", get_depth(node2));
	printf("Middle tree depth is %d\n", get_depth(node3));
	printf("Right tree depth is %d\n", get_depth(node4));

	return 0;
}
