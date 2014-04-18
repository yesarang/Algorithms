// Numbers are coming very fast to a list. How would you keep track of the median in real-time
// so that it can be retrieved in O(1), independently of how many numbers is in the list?

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cassert>

using namespace std;

class rt_median {
public:
	void insert(int val);
	int get_median() const;

private:
	vector<int> th_;
	vector<int> bh_;
};

void rt_median::insert(int val) {
	if (bh_.empty()) {
		bh_.push_back(val);
	}
	else if (bh_.front() >= val) {
		bh_.push_back(val);
		push_heap(bh_.begin(), bh_.end());
	}
	else {
		th_.push_back(val);
		push_heap(th_.begin(), th_.end(), greater<int>());
	}

	if (bh_.size() > th_.size() + 1) {
		pop_heap(bh_.begin(), bh_.end());
		th_.push_back(*(--bh_.end()));
		push_heap(th_.begin(), th_.end(), greater<int>());
		bh_.pop_back();
	}
	else if (bh_.size() < th_.size()) {
		pop_heap(th_.begin(), th_.end(), greater<int>());
		bh_.push_back(*(--th_.end()));
		push_heap(bh_.begin(), bh_.end());
		th_.pop_back();
	}
}

int rt_median::get_median() const {
	if (bh_.empty()) {
		return 0;
	}
	if (bh_.size() == th_.size()) {
		return (bh_.front() + th_.front()) / 2;
	}
	return bh_.front();
}

int main() {
	rt_median med;
	for (auto v : { 10, 20, 30, 40, 50, 60, 70, 80 }) {
		med.insert(v);
	}
	cout << "after inserting { 10, 20, 30, 40, 50, 60, 70, 80 }, median: " << med.get_median() << endl;
	assert(med.get_median() == 45);
	med.insert(66);
	cout << "after inserting { 10, 20, 30, 40, 50, 60, 66, 70, 80 }, median: " << med.get_median() << endl;
	assert(med.get_median() == 50);
	med.insert(44);
	cout << "after inserting { 10, 20, 30, 40, 44, 50, 60, 66, 70, 80 }, median: " << med.get_median() << endl;
	assert(med.get_median() == 47);

	return 0;
}