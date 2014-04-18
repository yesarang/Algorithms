// This algorithm find out the mininum element in an array of which elements are sorted but rotated
// ex: 6,7,1,2,3,4,5
// You may assume that every element is unique in this array

#include <iostream>
#include <cassert>

using namespace std;

// the range is half open [start, end)
int* min_element(int* start, int* end) {
	// error check
	if (!start || !end || end < start) {
		return 0;
	}
	// termination condition: 
	// 1. we found that the range is completly sorted
	// 2. only one element in the range
	if (*start < *(end - 1) || start == (end - 1)) {
		return start;
	}

	int* mpos = start + (end - start) / 2;
	if (*start > *(mpos - 1)) {
		return min_element(start, mpos);
	}
	else {
		return min_element(mpos, end);
	}
}

int main() {
	int a1[] = { 6, 7, 1, 2, 3, 4, 5 };
	cout << "min in { 6, 7, 1, 2, 3, 4, 5 }: " << *(min_element(a1, a1 + sizeof(a1) / sizeof(int))) << endl;

	int a2[] = { 3, 4, 5, 6, 7, 1, 2 };
	cout << "min in { 3, 4, 5, 6, 7, 1, 2 }: " << *(min_element(a2, a2 + sizeof(a2) / sizeof(int))) << endl;

	int a3[] = { 1, 2, 3, 4, 5, 6, 7 };
	cout << "min in { 1, 2, 3, 4, 5, 6, 7 }: " << *(min_element(a3, a3 + sizeof(a3) / sizeof(int))) << endl;

	cout << "min in {6}: " << *(min_element(a1, a1 + 1)) << endl;

	assert(min_element(0, 0) == 0);
	assert(min_element(a1 + sizeof(a1) / sizeof(int), a1) == 0);

	return 0;
}
