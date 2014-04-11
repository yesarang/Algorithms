#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int get_balanced_sum_pos1(const vector<int>& data) {
	const int dataSize = data.size();
	int leftPos = 0;
	int rightPos = dataSize - 1;
	int sumLeft = data[leftPos];
	int sumRight = data[rightPos];

	while (rightPos - leftPos > 2)
	{
		if (sumLeft < sumRight)
			sumLeft += data[++leftPos];
		else
			sumRight += data[--rightPos];
	}

	if (sumRight == sumLeft)
		return leftPos + 1;
	else
		return -1;
}

int get_balanced_sum_pos2(const vector<int>& data) {
	int lsum = 0, rsum = 0;
	int lindex = 0, rindex = data.size() - 1;

	lsum += data[lindex++];

	while (lsum != rsum || lindex < rindex) {
		if (lsum < rsum) {
			lsum += data[lindex++];
		} else {
			rsum += data[rindex--];
		}
	}

	if (lsum == rsum)
		return lindex;
	else
		return -1;
}

int get_balanced_sum_pos3(const vector<int>& data) {
	int sum = 0;
	for (int i = 0; i < data.size(); ++i) {
		sum += data[i];
	}
	int i = 0;
	int lsum = 0;
	for (; i < data.size() - 1; ++i) {
		lsum += data[i];
		if (lsum == (sum - data[i+1]) / 2) {
			break;
		}
	}

	if (i < data.size() - 1)
		return i + 1;
	else
		return -1;
}

int main() {
	int arr[] = {
		2,2,2,2,0,1,1,1,1,1,1,1,1
	};
	vector<int> vi(arr, arr + sizeof(arr) / sizeof(int));
	int pos = get_balanced_sum_pos1(vi);
	cout << "algorithm1 for arr: " << pos << endl;

	pos = get_balanced_sum_pos2(vi);
	cout << "algorithm2 for arr: " << pos << endl;

	pos = get_balanced_sum_pos3(vi);
	cout << "algorithm3 for arr: " << pos << endl;

	int arr2[] = {
		3,4,1,6,0,0,0
	};
	vi.clear();
	vi.assign(arr2, arr2 + sizeof(arr2) / sizeof(int));
	pos = get_balanced_sum_pos1(vi);
	cout << "algorithm1 for arr2: " << pos << endl;

	pos = get_balanced_sum_pos2(vi);
	cout << "algorithm2 for arr2: " << pos << endl;

	pos = get_balanced_sum_pos3(vi);
	cout << "algorithm3 for arr2: " << pos << endl;

	int arr3[] = {
		3,4,1,6,7,0,1
	};
	vi.clear();
	vi.assign(arr3, arr3 + sizeof(arr3) / sizeof(int));
	pos = get_balanced_sum_pos1(vi);
	cout << "algorithm1 for arr3: " << pos << endl;

	pos = get_balanced_sum_pos2(vi);
	cout << "algorithm2 for arr3: " << pos << endl;

	pos = get_balanced_sum_pos3(vi);
	cout << "algorithm3 for arr3: " << pos << endl;

	int arr4[] = {
		-2,-2,-2,-2,0,-1,-1,-1,-1,-1,-1,-1,-1
	};
	vi.clear();
	vi.assign(arr4, arr4 + sizeof(arr4) / sizeof(int));
	pos = get_balanced_sum_pos1(vi);
	cout << "algorithm1 for arr4: " << pos << endl;

//	pos = get_balanced_sum_pos2(vi);
//	cout << "algorithm2 for arr4: " << pos << endl;

	pos = get_balanced_sum_pos3(vi);
	cout << "algorithm3 for arr4: " << pos << endl;
}

