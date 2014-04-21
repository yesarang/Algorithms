#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void rotate_cell(vector<vector<int>>& mat, int i, int j) {
	const int N = mat.size() - 1;	// N means maximum index
	auto t = mat[i][j];
	mat[i][j] = mat[N - j][i];
	mat[N - j][i] = mat[N - i][N - j];
	mat[N - i][N - j] = mat[j][N - i];
	mat[j][N - i] = t;
}

void print_matrix(const vector<vector<int>>& mat) {
	for_each(mat.begin(), mat.end(), [](const vector<int>& v) {
		for (auto n : v) {
			printf("%02d ", n);
		}
		cout << endl;
	});
}

void rotate_matrix(vector<vector<int>>& mat) {
	if (mat.size() == 1)
		return;

	for (unsigned i = 0; i < mat.size() / 2; ++i) {
		for (unsigned j = i; j < mat.size() - i - 1; ++j) {
			rotate_cell(mat, i, j);
		}
	}
}

int main() {
	vector<vector<int>> mat1(2);
	int n = 0;
	mat1[0].push_back(n++);
	mat1[0].push_back(n++);
	mat1[1].push_back(n++);
	mat1[1].push_back(n);
	print_matrix(mat1);
	rotate_cell(mat1, 0, 0);
	print_matrix(mat1);
	rotate_matrix(mat1);
	print_matrix(mat1);

	n = 0;
	vector<vector<int>> mat2(3);
	for_each(mat2.begin(), mat2.end(), [&n](vector<int>& v) {
		v.push_back(n++);
		v.push_back(n++);
		v.push_back(n++);
	});
	print_matrix(mat2);
	rotate_matrix(mat2);
	print_matrix(mat2);

	n = 0;
	vector<vector<int>> mat3(4);
	for_each(mat3.begin(), mat3.end(), [&n](vector<int>& v) {
		v.push_back(n++);
		v.push_back(n++);
		v.push_back(n++);
		v.push_back(n++);
	});
	print_matrix(mat3);
	rotate_matrix(mat3);
	print_matrix(mat3);

	n = 0;
	vector<vector<int>> mat4(5);
	for_each(mat4.begin(), mat4.end(), [&n](vector<int>& v) {
		v.push_back(n++);
		v.push_back(n++);
		v.push_back(n++);
		v.push_back(n++);
		v.push_back(n++);
	});
	print_matrix(mat4);
	rotate_matrix(mat4);
	print_matrix(mat4);

	return 0;
}
