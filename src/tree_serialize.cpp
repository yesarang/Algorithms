// check out whether this code works properly at http://ideone.com/H7nOu6
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cassert>
#include <arpa/inet.h>

using namespace std;

typedef unsigned char uchar;

struct Node {
	string name;
	Node* pLeft;
	Node* pRight;
	Node(const string& n) : name(n), pLeft(0), pRight(0) {}
	Node(const string& n, Node* l, Node* r) : name(n), pLeft(l), pRight(r) {}
};

void print_pre_order(Node* pTree) {
	cout << pTree->name << endl;
	if (pTree->pLeft) {
		print_pre_order(pTree->pLeft);
	}
	if (pTree->pRight) {
		print_pre_order(pTree->pRight);
	}
}

bool is_same_tree(Node* pTree1, Node* pTree2) {
	if (pTree1->name != pTree2->name) {
		return false;
	}
	if (pTree1->pLeft && pTree2->pLeft && !is_same_tree(pTree1->pLeft, pTree2->pLeft)) {
		return false;
	}
	if (pTree1->pRight && pTree2->pRight && !is_same_tree(pTree1->pRight, pTree2->pRight)) {
		return false;
	}
	return true;
}

void int_serialize(int data, vector<uchar>& buf) {
	uint32_t nl_data = htonl(data);
	uchar* pData = (uchar*)&nl_data;
	for (int i = 0; i < sizeof(uint32_t); ++i) {
		buf.push_back(pData[i]);
	}
}

void str_serialize(const string& str, vector<uchar>& buf) {
	for (int i = 0; i < str.length(); ++i) {
		buf.push_back(str[i]);
	}
}

void tree_serialize(Node* pTree, vector<uchar>& buf) {
	// pre-order traversal
	// serialize first data of this node
	int_serialize(pTree->name.length(), buf);
	str_serialize(pTree->name, buf);

	// serialize left sub-tree
	if (pTree->pLeft) {
		buf.push_back(1);
		tree_serialize(pTree->pLeft, buf);
	}
	else {
		buf.push_back(0);
	}

	// serialize right sub-tree
	if (pTree->pRight) {
		buf.push_back(1);
		tree_serialize(pTree->pRight, buf);
	}
	else {
		buf.push_back(0);
	}
}

int int_deserialize(vector<uchar>::iterator& pos) {
	uint32_t nl_data = 0;
	uchar* pData = (uchar*)&nl_data;
	for (int i = 0; i < sizeof(uint32_t); ++i) {
		*pData++ = *pos++;
	}
	return ntohl(nl_data);
}

string str_deserialize(int len, vector<uchar>::iterator& pos) {
	string s;
	for (int i = 0; i < len; ++i) {
		s.push_back(*pos++);
	}
	return s;
}

void tree_deserialize(Node*& pTree, vector<uchar>::iterator& pos) {
	int len = int_deserialize(pos);
	string s = str_deserialize(len, pos);
	pTree = new Node(s);
	if (*pos++) {
		tree_deserialize(pTree->pLeft, pos);
	}
	if (*pos++) {
		tree_deserialize(pTree->pRight, pos);
	}
}

int main() {
	// handcraft a binary tree case #1
	Node* left = new Node("yoon");
	Node* right = new Node("soo");
	Node* tree = new Node("kim", left, right);
	cout << "before serialization & deserialization of case #1" << endl;
	print_pre_order(tree);

	// serialize it
	vector<uchar> buf;
	tree_serialize(tree, buf);

	// deserialize it
	Node* newTree = 0;
	vector<uchar>::iterator pos = buf.begin();
	tree_deserialize(newTree, pos);
	cout << "after serialization & deserialization of case #1" << endl;
	print_pre_order(newTree);

	assert(is_same_tree(tree, newTree));

	// prepare a binary tree case #2
	left->pLeft = new Node("jung");
	left->pRight = new Node("kyun");
	cout << "before serialization & deserialization of case #2" << endl;
	print_pre_order(tree);

	// serialize it
	buf.clear();
	tree_serialize(tree, buf);

	// deserialize it
	newTree = 0;
	pos = buf.begin();
	tree_deserialize(newTree, pos);
	cout << "after serialization & deserialization of case #2" << endl;
	print_pre_order(newTree);

	assert(is_same_tree(tree, newTree));
}

