#include <iostream>
#include <cassert>

using namespace std;

int*
upper_bound(int* first, int* last, int val) {
	if (first == last) {
		return first;
	}
	int* middle = first + (last - first) / 2;
	if (val < *middle) {
		return upper_bound(first, middle, val);
	}
	else {
		return upper_bound(middle + 1, last, val);
	}
}

int main() {
	int arr[5] = { -23, -8, 13, 72, 104 };

	int* pos = upper_bound(arr, arr + 5, 13);
	if (pos != arr + 5) {
		cout << *pos << endl;
	}
	else {
		cout << "can't find ub for 13" << endl;
	}

	pos = upper_bound(arr, arr + 5, 1000);
	if (pos != arr + 5) {
		cout << *pos << endl;
	}
	else {
		cout << "can't find ub for 1000" << endl;
	}

	pos = upper_bound(arr, arr + 5, -100);
	if (pos != arr + 5) {
		cout << *pos << endl;
	}
	else {
		cout << "can't find ub for -100" << endl;
	}

	int arr1[10] = { 10,10,10,20,20,20,20,30,30,30 };
	pos = upper_bound(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]), 20);
	assert(pos == arr1 + 7);
	pos = upper_bound(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]), 10);
	assert(pos == arr1 + 3);
	pos = upper_bound(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]), 30);
	assert(pos == arr1 + 10);

	return 0;
}

