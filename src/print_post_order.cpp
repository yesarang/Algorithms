// check out whether this code works properly at http://ideone.com/SR6EVd
#include <iostream>
#include <vector>

using namespace std;

void print_v(const string& hdr, const vector<int>& v) {
	cout << hdr << ":" << endl;
	for(auto e : v) {
		cout << e << " ";
	}
	cout << endl;
}

void get_post_order(const vector<int>& pre_order, const vector<int>& in_order, vector<int>& post_order) {
	if (pre_order.size() == 0) {
		return;
	}
	else if (pre_order.size() == 1) {
		post_order.push_back(*pre_order.begin());
		return;
	}

	vector<int>::const_iterator pos1 = pre_order.begin(), pos2 = in_order.begin();
	int root = *pos1++;
	while (*pos1 < root) {
		++pos1;
	}
	vector<int> pre_order_left(++pre_order.begin(), pos1);
	vector<int> pre_order_right(pos1, pre_order.end());
	
	while (*pos2 != root) {
		++pos2;
	}
	vector<int> in_order_left(in_order.begin(), pos2);
	vector<int> in_order_right(++pos2, in_order.end());

	if (pre_order_left.size() > 0)
		get_post_order(pre_order_left, in_order_left, post_order);
	if (pre_order_right.size() > 0)
		get_post_order(pre_order_right, in_order_right, post_order);
	post_order.push_back(root);
}

int main() {
	vector<int> pre_order = {
		27,16, 9,12,54,36,72
	};
	vector<int> in_order = {
		9,12,16,27,36,54,72
	};
	print_v("For given pre order sequence", pre_order);
	print_v("and in order sequence", in_order);
	vector<int> post_order;
	get_post_order(pre_order, in_order, post_order);
	print_v("post order sequence is", post_order);
	return 0;
}
