#include <iostream>

using namespace std;

enum Direction {
	LEFT,
	RIGHT
};

struct Node {
	int data;
	Direction dir;
	Node* left;
	Node* right;
};

struct Tree {
	Node* root;
};

Tree t = { 0 };

bool isLeaf(Node* pNode) {
	return !pNode->left && !pNode->right;
}

void insert(Node*& pNode, int data) {
	// special case handling: there's no element in the tree
	if (pNode == 0) {
		pNode = new Node;
		pNode->data = data;
		pNode->dir = LEFT;
		pNode->left = 0;
		pNode->right = 0;
		return;
	}

	if (isLeaf(pNode)) {
		Node* pNewLeaf = new Node();
		pNewLeaf->data = data;
		pNewLeaf->dir = LEFT;
		pNewLeaf->left = 0;
		pNewLeaf->right = 0;
		Node* pNewNode = new Node();
		pNewNode->left = pNode;
		pNewNode->right = pNewLeaf;
		pNewNode->dir = LEFT;
		pNode = pNewNode;
		return;
	}

	// toggling the direction
	if (pNode->dir == LEFT) {
		insert(pNode->left, data);
		pNode->dir = RIGHT;
	}
	else {
		insert(pNode->right, data);
		pNode->dir = LEFT;
	}
}

void dfs(Node* pNode) {
	if (isLeaf(pNode)) {
		cout << pNode->data << endl;
		return;
	}

	dfs(pNode->left);
	dfs(pNode->right);
	cout << "winner" << endl;
}

int main() {
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	for (int i = 0; i < 10; ++i) {
		insert(t.root, arr[i]);
	}

	dfs(t.root);
}

