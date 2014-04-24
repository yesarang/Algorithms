#include <iostream>
#include <vector>

using namespace std;

struct pos_t {
	int x;
	int y;
};

pos_t get_xy(int ncols, int lpos) {
	return pos_t{ lpos / ncols, lpos % ncols };
}

int get_lpos(int ncols, pos_t pos) {
	return pos.x * ncols + pos.y;
}

pos_t matrix_binary_search(const vector<vector<int>>& mat, int left, int right, int val) {
	if (left > right) {
		return { -1, -1 };
	}

	int mid = (left + right) / 2;
	pos_t mpos = get_xy(mat[0].size(), mid);
	if (val > mat[mpos.x][mpos.y]) {
		return matrix_binary_search(mat, mid + 1, right, val);
	}
	else if (val < mat[mpos.x][mpos.y]) {
		return matrix_binary_search(mat, left, mid - 1, val);
	}
	else {
		return mpos;
	}
}

pos_t matrix_search(const vector < vector<int>>& mat, pos_t start, pos_t end, int val) {
	return matrix_binary_search(mat, get_lpos(mat[0].size(), start), get_lpos(mat[0].size(), end), val);
}

ostream& operator<< (ostream& os, pos_t pos) {
	os << "(" << pos.x << "," << pos.y << ")";
	return os;
}

int main() {
	vector<vector<int>> mat{
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 }
	};

	pos_t pos = matrix_search(mat, { 0, 0 }, { 2, 2 }, 5);
	cout << pos << endl;

	pos = matrix_search(mat, { 0, 0 }, { 2, 2 }, 9);
	cout << pos << endl;

	pos = matrix_search(mat, { 0, 0 }, { 2, 2 }, 4);
	cout << pos << endl;

	pos = matrix_search(mat, { 0, 0 }, { 2, 2 }, 100);
	cout << pos << endl;

	return 0;
}

