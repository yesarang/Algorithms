// Write an algorithm to check whether a matrix of characters can match a given character string consecutively
// in any path. Each character can be used only once.
#include <iostream>
#include <vector>

using namespace std;

bool is_matched_impl(const vector<vector<char>>& char_mat, int x, int y, const char* str, vector<vector<bool>>& visited) {
	if (char_mat[x][y] == *str) {
		if (*(str + 1) == '\0') {
			return true;
		}
		visited[x][y] = true;
		if (x > 0 && !visited[x - 1][y] && is_matched_impl(char_mat, x - 1, y, str + 1, visited)) {
			return true;
		}
		else if (x < char_mat.size() - 1 && !visited[x + 1][y] && is_matched_impl(char_mat, x + 1, y, str + 1, visited)) {
			return true;
		}
		else if (y > 0 && !visited[x][y - 1] && is_matched_impl(char_mat, x, y - 1, str + 1, visited)) {
			return true;
		}
		else if (y < char_mat[0].size() - 1 && !visited[x][y + 1] && is_matched_impl(char_mat, x, y + 1, str + 1, visited)) {
			return true;
		}
		visited[x][y] = false;
	}
	return false;
}

bool is_matched(const vector<vector<char>>& char_mat, const char* str) {
	vector<vector<bool>> visited(char_mat.size(), vector<bool>(char_mat[0].size(), false));
	for (int i = 0; i < char_mat.size(); ++i) {
		for (int j = 0; j < char_mat[0].size(); ++j) {
			if (char_mat[i][j] == *str && is_matched_impl(char_mat, i, j, str, visited)) {
				return true;
			}
		}
	}
	return false;
}

bool is_matched2_impl(const vector<vector<char>>& char_mat, int x, int y, const string& str) {
	vector<vector<bool>> visited(char_mat.size(), vector<bool>(char_mat[0].size()));
	visited[x][y] = true;
	for (int i = 1; i < str.length(); ++i) {
		if (x > 0 && !visited[x - 1][y] && str[i] == char_mat[x - 1][y]) {
			--x;
		}
		else if (x < char_mat.size() - 1 && !visited[x + 1][y] && str[i] == char_mat[x + 1][y]) {
			++x;
		}
		else if (y > 0 && !visited[x][y - 1] && str[i] == char_mat[x][y - 1]) {
			--y;
		}
		else if (y < char_mat[0].size() - 1 && !visited[x][y + 1] && str[i] == char_mat[x][y + 1]) {
			++y;
		}
		else {
			return false;
		}
		visited[x][y] = true;
	}
	return true;
}

bool is_matched2(const vector<vector<char>>& char_mat, const string& str) {
	for (int i = 0; i < char_mat.size(); ++i) {
		for (int j = 0; j < char_mat[0].size(); ++j) {
			if (char_mat[i][j] == str[0] && is_matched2_impl(char_mat, i, j, str)) {
				return true;
			}
		}
	}
	return false;
}

int main() {
	vector<vector<char>> char_mat;
	char_mat.push_back({ 'A', 'B', 'C' });
	char_mat.push_back({ 'D', 'E', 'F' });
	char_mat.push_back({ 'G', 'H', 'I' });

	if (is_matched(char_mat, "ABC")) {
		cout << "ABC matched" << endl;
	}

	if (is_matched(char_mat, "BEH")) {
		cout << "BEH matched" << endl;
	}

	if (is_matched(char_mat, "ABCFIHEDG")) {
		cout << "ABCFIHEDG matched" << endl;
	}

	if (is_matched(char_mat, "FIHEDA")) {
		cout << "FIHEDA matched" << endl;
	}

	if (!is_matched(char_mat, "FIHEDABCF")) {
		cout << "FIHEDABCF not matched" << endl;
	}

	if (is_matched2(char_mat, "FIHEDA")) {
		cout << "FIHEDA matched" << endl;
	}

	if (!is_matched2(char_mat, "FIHEDABCF")) {
		cout << "FIHEDABCF not matched" << endl;
	}

	if (is_matched2(char_mat, "ABCFIHEDG")) {
		cout << "ABCFIHEDG matched" << endl;
	}

	return 0;
}
