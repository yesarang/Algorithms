/*
Given an array of an element or a nested array, compute the depth sum.
The depth sum is defined as sum of all elements multiplied by its depth.

For example,
For, [8, 4, [2, [9], 6], 3], the depth sum will be
1 * (8 + 4 + 2 * (2 + 3 * (9) + 6) + 3)
*/

#include <iostream>
#include <vector>

using namespace std;

struct ArrayOrElem {
	bool is_array;
	union {
		int val;
		vector<ArrayOrElem>* array;
	} u;

	ArrayOrElem(int val)
		: is_array(false)
	{
		u.val = val;
	}

	ArrayOrElem(vector<ArrayOrElem>* a)
		: is_array(true)
	{
		u.array = a;
	}
};

int depth_sum_helper(const vector<ArrayOrElem>& data, int level)
{
	int sum = 0;
	for (size_t i = 0; i < data.size(); ++i) {
		sum += data[i].is_array ? depth_sum_helper(*data[i].u.array, level + 1) : data[i].u.val;
	}

	return sum * level;
}

int depth_sum(const vector<ArrayOrElem>& data)
{
	return depth_sum_helper(data, 1);
}

int main()
{
	vector<ArrayOrElem> lvl3;
	lvl3.emplace_back(9);

	vector<ArrayOrElem> lvl2;
	lvl2.emplace_back(2);
	lvl2.emplace_back(&lvl3);
	lvl2.emplace_back(6);

	vector<ArrayOrElem> lvl1;
	lvl1.emplace_back(8);
	lvl1.emplace_back(4);
	lvl1.emplace_back(&lvl2);
	lvl1.emplace_back(3);

	cout << depth_sum(lvl1) << endl;
}

