#include <iostream>
#include <cassert>

using namespace std;

int*
lower_bound(int* first, int* last, int val) {
	if (first == last) {
		return first;
	}
	int* middle = first + (last - first) / 2;
	if (val > *middle) {
		return lower_bound(middle + 1, last, val);
	}
	else {
		return lower_bound(first, middle, val);
	}
}

int main() {
	int arr[5] = { -23, -8, 16, 72, 104 };

	int* pos = lower_bound(arr, arr + 5, 13);
	if (pos != arr + 5) {
		cout << *pos << endl;
	}
	else {
		cout << "can't find lb for 13" << endl;
	}

	pos = lower_bound(arr, arr + 5, 1000);
	if (pos != arr + 5) {
		cout << *pos << endl;
	}
	else {
		cout << "can't find lb for 1000" << endl;
	}

	pos = lower_bound(arr, arr + 5, -100);
	if (pos != arr + 5) {
		cout << *pos << endl;
	}
	else {
		cout << "can't find lb for -100" << endl;
	}

	int arr1[10] = { 10,10,10,20,20,20,20,30,30,30 };
	pos = lower_bound(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]), 20);
	assert(pos == arr1 + 3);
	pos = lower_bound(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]), 10);
	assert(pos == arr1);
	pos = lower_bound(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]), 30);
	assert(pos == arr1 + 7);

	return 0;
}

