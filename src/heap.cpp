#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void siftup_min_heap(vector<int>& heap, int index) {
	if (heap.size() == 1 || index == 0) {
		return;
	}

	int parentIndex = (index - 1) / 2;
	if (heap[parentIndex] > heap[index]) {
		swap(heap[parentIndex], heap[index]);
		siftup_min_heap(heap, parentIndex);
	}
}

void min_heap_insert(vector<int>& heap, int val) {
	heap.push_back(val);
	siftup_min_heap(heap, heap.size() - 1);
}

void siftdown_min_heap(vector<int>& heap, unsigned index) {
	unsigned left_child = 2 * index + 1;
	if (left_child > heap.size() - 1) {
		return;
	}
	unsigned min_index = heap.size();
	unsigned right_child = 2 * index + 2;
	if (right_child > heap.size() - 1) {
		min_index = left_child;
	}
	else {
		if (heap[left_child] < heap[right_child]) {
			min_index = left_child;
		}
		else {
			min_index = right_child;
		}
	}
	if (heap[min_index] < heap[index]) {
		swap(heap[index], heap[min_index]);
		siftdown_min_heap(heap, min_index);
	}
}

int min_heap_remove(vector<int>& heap) {
	if (heap.empty()) {
		return 0;
	}
	int ret = heap[0];
	if (heap.size() > 1) {
		heap[0] = heap[heap.size() - 1];
		heap.pop_back();
		siftdown_min_heap(heap, 0);
	}
	else {
		heap.pop_back();
	}
	return ret;
}

int main() {
	vector<int> heap;
	for (auto v : { 23, -4, 5, 78, -100, 27, 2, 8 }) {
		min_heap_insert(heap, v);
		for (auto v : heap) {
			cout << v << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < 8; ++i) {
		int min_val = min_heap_remove(heap);
		cout << "min = " << min_val << endl;
		for (auto v : heap) {
			cout << v << " ";
		}
		cout << endl;
	}
	return 0;
}