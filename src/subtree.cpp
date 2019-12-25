// You have two very large binary trees: Tl, with millions of nodes, and T2, with
// hundreds of nodes.Create an algorithm to decide if T2 is a subtree of Tl.
// A tree T2 is a subtree of Tl if there exists a node n in Tl such that the subtree of
// n is identical to T2.That is, if you cut off the tree at node n, the two trees would
// be identical.
#include <iostream>
#include <functional>
#include <cassert>

using namespace std;

struct node {
	int val_;
	node* left_;
	node* right_;
	node(int val, node* left = nullptr, node* right = nullptr)
		: val_(val), left_(left), right_(right)
	{}
};

bool tree_is_same(node* tree1, node* tree2) {
	if (!tree1 && !tree2) {
		return true;
	}
	else if (!tree1 || !tree2) {
		return false;
	}

	return tree1->val_ == tree2->val_ &&
		tree_is_same(tree1->left_, tree2->left_) &&
		tree_is_same(tree1->right_, tree2->right_);
}

bool tree_is_subtree(node* tree1, node* tree2) {
	if (tree_is_same(tree1, tree2)) {
		return true;
	}

	if (tree2) {
		if (tree2->left_ && tree_is_subtree(tree1, tree2->left_)) {
			return true;
		}
		else if (tree2->right_ && tree_is_subtree(tree1, tree2->right_)) {
			return true;
		}
	}
	return false;
}

bool pre_order_traverse(node* root, function<bool (node*)> predicate) {
	if (predicate(root)) {
		return true;
	}

	if (root) {
		if (root->left_ && pre_order_traverse(root->left_, predicate)) {
			return true;
		}
		else if (root->right_ && pre_order_traverse(root->right_, predicate)) {
			return true;
		}
	}
	return false;
}

bool tree_is_subtree_lambda(node* subtree, node* tree) {
	return pre_order_traverse(tree, [subtree](node* root) {
			   return tree_is_same(subtree, root);
		   });
}

int main() {
	node* tree2 = nullptr;
	node* tree3 = nullptr;
	node* tree1 = new node(1,
					  tree2 = new node(2,
						  new node(4),
						  new node(5)
						  ),
					  new node(3,
					      tree3 = new node(6),
						  new node(7)
						  )
					  );

	assert(tree_is_subtree(tree2, tree1));
	cout << "tree2 is a subtree of tree1" << endl;
	assert(tree_is_subtree(tree3, tree1));
	cout << "tree3 is a subtree of tree1" << endl;

	using std::placeholders::_1;

	assert(pre_order_traverse(tree1, bind(tree_is_same, tree2, _1)));
	cout << "tree2 is a subtree of tree1" << endl;
	assert(pre_order_traverse(tree1, bind(tree_is_same, tree3, _1)));
	cout << "tree3 is a subtree of tree1" << endl;

	assert(tree_is_subtree_lambda(tree2, tree1));
	cout << "tree2 is a subtree of tree1" << endl;
	assert(tree_is_subtree_lambda(tree3, tree1));
	cout << "tree3 is a subtree of tree1" << endl;

	return 0;
}
