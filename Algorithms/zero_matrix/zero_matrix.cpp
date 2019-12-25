#include <iostream>
#include <vector>

using namespace std;

void zero_matrix(vector<vector<int>>& m) {
	auto zero_row = [&](size_t i) {
		for (size_t j = 0; j < m[0].size(); ++j) {
			m[i][j] = 0;
		}
	};

	auto zero_col = [&](size_t j) {
		for (size_t i = 0; i < m.size(); ++i) {
			m[i][j] = 0;
		}
	};

	vector<bool> zero_rows(m.size());
	vector<bool> zero_cols(m[0].size());

	for (size_t i = 0; i < m.size(); ++i) {
		for (size_t j = 0; j < m[0].size(); ++j) {
			if (m[i][j] == 0) {
				zero_rows[i] = true;
				zero_cols[j] = true;
			}
		}
	}

	for (size_t i = 0; i < m.size(); ++i) {
		if (zero_rows[i]) {
			zero_row(i);
		}
	}

	for (size_t j = 0; j < m[0].size(); ++j) {
		if (zero_cols[j]) {
			zero_col(j);
		}
	}
}

ostream& operator <<(ostream& os, const vector<vector<int>>& m) {
	for (size_t i = 0; i < m.size(); ++i) {
		for (size_t j = 0; j < m[0].size(); ++j) {
			os << m[i][j] << " ";
		}
		os << endl;
	}

	return os;
}

int main() {
	vector<vector<int>> m = {
		vector<int>{ 1,1,1,1 },
		vector<int>{ 2,2,2,0 },
		vector<int>{ 3,0,3,3 },
		vector<int>{ 4,4,4,4 }
	};

	cout << m << endl;

	zero_matrix(m);
	cout << m << endl;
}
