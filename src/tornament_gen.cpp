#include <iostream>
#include <string>

using namespace std;

enum Direction {
	LEFT,
	RIGHT
};

struct Node {
	string name;
	Direction dir;
	Node* left;
	Node* right;
	Node(const string& nm, Node* l = 0, Node* r = 0)
		: name(nm), dir(LEFT), left(l), right(r)
	{}
};

bool isLeaf(Node* pNode) {
	return !pNode->left && !pNode->right;
}

void insert(Node*& pNode, const string& name) {
	// special case handling: there's no element in the tree
	if (pNode == 0) {
		pNode = new Node(name);
		return;
	}

	if (isLeaf(pNode)) {
		Node* pNewLeaf = new Node(name);
		Node* pNewNode = new Node("winner", pNode, pNewLeaf);
		pNode = pNewNode;
		return;
	}

	// toggling the direction
	if (pNode->dir == LEFT) {
		insert(pNode->left, name);
		pNode->dir = RIGHT;
	}
	else {
		insert(pNode->right, name);
		pNode->dir = LEFT;
	}
}

string spaces(int level) {
	string s;
	for (; level > 0; --level) {
		s += "  ";
	}
	return s;
}

void print_pre_order(Node* pNode, int level) {
	cout << spaces(level) << pNode->name << endl;

	if (pNode->left)
		print_pre_order(pNode->left, level + 1);
	if (pNode->right)
		print_pre_order(pNode->right, level + 1);
}

int main() {
	const char* names[] = {
		"kim",
		"chester",
		"jasmin",
		"suji",
		"john",
		"alvin",
		"jennifer",
		"ron",
		"justin",
		"clinton"
	};
	Node* root = 0;
	for (int i = 0; i < sizeof(names)/sizeof(char*); ++i) {
		insert(root, names[i]);
	}

	print_pre_order(root, 0);
}

