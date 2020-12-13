// bst_iter.cpp : design an algorithm that returns the next smallest item
// in a binary search tree
//

#include <iostream>
#include <stack>

using namespace std;

struct Node {
	int val;
	Node* left;
	Node* right;
	Node(int v, Node* l = nullptr, Node* r = nullptr) : val(v), left(l), right(r) {}
};

class BstIter {
private:
	stack<Node*> s_;

	void traverse(Node* n) {
		while (n) {
			s_.push(n);
			n = n->left;
		}
	}

public:
	BstIter(Node* root, int start) : s_() {
		traverse(root); 
		while (!s_.empty() && s_.top()->val < start) {
			next();
		}
	}

	bool has_next() const {
		return !s_.empty();
	}

	Node* next() {
		if (s_.empty()) {
			return nullptr;
		}

		auto ret = s_.top();
		s_.pop();

		traverse(ret->right);

		return ret;
	}
};

int main()
{
	Node* t1 =
		new Node(10,
			new Node(5, nullptr, new Node(8)),
			new Node(15, new Node(12), new Node(18))
		);

	BstIter i(t1, 1);
	cout << "t1:" << endl;
	while (i.has_next()) {
		cout << i.next()->val << endl;
	}

	/*
            6
          /   \
         3    15
        / \   /
       1   5 9
	*/
	Node* t2 =
		new Node(6,
			new Node(3, new Node(1), new Node(5)),
			new Node(15, new Node(9))
		);

	BstIter i2(t2, 5);
	cout << "t2:" << endl;
	while (i2.has_next()) {
		cout << i2.next()->val << endl;
	}

	Node* t3 = nullptr;
	BstIter i3(t3, INT_MIN);
	cout << "t3:" << endl;
	while (i3.has_next()) {
		cout << i3.next()->val << endl;
	}

	return 0;
}

