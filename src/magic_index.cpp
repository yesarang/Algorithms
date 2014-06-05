// 9.3 A magic index in an array A[l...n - l] is defined to be an index such that A[i] = i.
// Given a sorted array of distinct integers, write a method to find a magic index, if
// one exists, in array A.
// FOLLOW UP
// What if the values are not distinct ?
#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

int find_magic_index(int a[], int start, int end) {
	if (start > end) {
		return -1;
	}

	int mid = start + (end - start) / 2;
	if (a[mid] > mid) {
		return find_magic_index(a, start, mid - 1);
	}
	else if (a[mid] < mid) {
		return find_magic_index(a, mid + 1, end);
	}
	else {
		return mid;
	}
}

int find_magic_index_duplist(int a[], int start, int end) {
	if (start > end) {
		return -1;
	}

	int mid = start + (end - start) / 2;
	if (a[mid] == mid) {
		return mid;
	}

	int ri = find_magic_index_duplist(a, start, min(mid - 1, a[mid]));
	if (ri >= 0) {
		return ri;
	}

	ri = find_magic_index_duplist(a, max(mid + 1, a[mid]), end);
	return ri;
}

int main() {
	int a1[] = { 0, 2, 5, 6 };
	int mi = find_magic_index(a1, 0, sizeof(a1) / sizeof(int) - 1);
	assert(mi == 0);
	cout << mi << endl;

	int a2[] = { -2, -1, 1, 3 };
	mi = find_magic_index(a2, 0, sizeof(a2) / sizeof(int) - 1);
	assert(mi == 3);
	cout << mi << endl;

	int a3[] = { 0, 0, 0, 0 };
	mi = find_magic_index_duplist(a3, 0, sizeof(a3) / sizeof(int) - 1);
	assert(mi == 0);
	cout << mi << endl;

	int a4[] = { 3, 3, 3, 3 };
	mi = find_magic_index_duplist(a4, 0, sizeof(a4) / sizeof(int) - 1);
	assert(mi == 3);
	cout << mi << endl;

	int a5[] = { -25, -10, -2, 5, 5, 8, 8, 8, 8, 25, 100 };
	mi = find_magic_index_duplist(a5, 0, sizeof(a5) / sizeof(int) - 1);
	assert(mi == 8);
	cout << mi << endl;

	return 0;
}
