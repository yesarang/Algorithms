#include <iostream>
#include <algorithm>

using namespace std;

struct Building {
	int start;
	int height;
	int end;
};

struct Node {
	int s;
	int e;
	int h;
	Node* l;
	Node* r;
	Node(const Building& b);
	void add(const Building& b);
	void print_in_order(Node*& last);
};

Node::Node(const Building& b)
	: s(b.start), e(b.end), h(b.height), l(0), r(0)
{}

void Node::add(const Building& b) {
	if (b.end <= this->s) {
		if (l)
			l->add(b);
		else
			l = new Node(b);
	}
	else if (b.start >= this->e) {
		if (r)
			r->add(b);
		else
			r = new Node(b);
	}
	else {
		if (b.start < this->s) {
			Building nb = { b.start, b.height, this->s };
			if (l)
				l->add(nb);
			else
				l = new Node(nb);
		}
		if (b.end > this->e) {
			Building nb = { this->e, b.height, b.end };
			if (r)
				r->add(nb);
			else
				r = new Node(nb);
		}
	}
}

void Node::print_in_order(Node*& last) {
	if (l)
		l->print_in_order(last);
	if (last && last->e != this->s)
		printf("%d,0,", last->e);
	printf("%d,%d,", this->s, this->h);
	last = this;
	if (r)
		r->print_in_order(last);
}

struct SkylineTree {
	Node* root;
	SkylineTree() : root(0) {}
	void add(const Building& b);
	void print();
};

void SkylineTree::add(const Building& b) {
	if (!root) {
		root = new Node(b);
	}
	else {
		root->add(b);
	}
}

void SkylineTree::print() {
	Node* last = 0;
	root->print_in_order(last);
	if (last)
		printf("%d,0\n", last->e);
}

int main() {
	Building input[] = {
		{1,11,5}, {2,6,7}, {3,13,9}, {12,7,16}, {14,3,25}, {19,18,22}, {23,13,29}, {24,4,28}
	};

	printf("org: ");
	for_each(
		input, input + sizeof(input) / sizeof(Building),
		[] (const Building& b) {
			printf("{%d,%d,%d}, ", b.start, b.height, b.end);
		});
	printf("\n");
			
	sort(
		input, input + sizeof(input) / sizeof(Building), 
		[] (const Building& lb, const Building& rb) {
			return lb.height > rb.height;
		});
	printf("sorted: ");
	for (Building b : input) {
		printf("{%d,%d,%d}, ", b.start, b.height, b.end);
	}
	printf("\n");

	SkylineTree skyLine;
	for (Building b : input) {
		skyLine.add(b);
	}
	skyLine.print();
	return 0;
}

