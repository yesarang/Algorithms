// Implement a function to check if a binary tree is balanced.For the purposes of
// this question, a balanced tree is defined to be a tree such that the heights of the
// two subtrees of any node never differ by more than one.
#include <iostream>
#include <memory>
#include <cstdlib>
#include <algorithm>
#include <cassert>

using namespace std;

struct Node {
	int val_;
	shared_ptr<Node> left_;
	shared_ptr<Node> right_;
	Node(int val, shared_ptr<Node> left, shared_ptr<Node> right)
		: val_{ val }, left_{ left }, right_{ right }
	{}
	Node(int val)
		: Node{ val, nullptr, nullptr }
	{}
	bool is_balanced(int& depth);
};

bool Node::is_balanced(int& depth) {
	int left_depth{ 0 };
	int right_depth{ 0 };

	bool left_balanced{ false };
	if (left_) {
		left_balanced = left_->is_balanced(left_depth);
		++left_depth;
	}
	else {
		left_balanced = true;
		left_depth = 0;
	}
	bool right_balanced{ false };
	if (right_) {
		right_balanced = right_->is_balanced(right_depth);
		++right_depth;
	}
	else {
		right_balanced = true;
		right_depth = 0;
	}
	depth = max(left_depth, right_depth);
	return  left_balanced && right_balanced && abs(left_depth - right_depth) <= 1;
}

int main() {
	shared_ptr<Node> tree1{ make_shared<Node>(1, make_shared<Node>(2, nullptr, nullptr), nullptr) };
	int depth = 0;
	assert(tree1->is_balanced(depth) && depth == 1);
	cout << "The tree is balanced and depth = " << depth << endl;

	shared_ptr<Node> tree2{
		make_shared<Node>(1,
			make_shared<Node>(2,
				make_shared<Node>(4),
				make_shared<Node>(5)
			),
			make_shared<Node>(3,
				make_shared<Node>(6),
				make_shared<Node>(7,
					nullptr,
					make_shared<Node>(8)
					)
			)
		)
	};
	depth = 0;
	assert(tree2->is_balanced(depth) && depth == 3);
	cout << "The tree is balanced and depth = " << depth << endl;

	shared_ptr<Node> tree3{
		make_shared<Node>(1,
			make_shared<Node>(2,
				make_shared<Node>(4),
				make_shared<Node>(5)
			),
			nullptr
		)
	};
	depth = 0;
	assert(!tree3->is_balanced(depth) && depth == 2);
	cout << "The tree is not balanced and depth = " << depth << endl;

	return 0;
}
