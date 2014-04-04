#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>

using namespace std;

void dfs(vector<vector<bool> >& puzzle, int here_x, int here_y) {
	printf("DFS visiting (%d, %d)\n", here_x, here_y);
	puzzle[here_y][here_x] = true;
	// dfs to right cell
	printf("testing right cell at (%d,%d)\n", here_x, here_y);
	if (here_x < puzzle[0].size() - 1 && !puzzle[here_y][here_x+1]) {
		printf("going right at (%d,%d)\n", here_x, here_y);
		dfs(puzzle, here_x+1, here_y);
	}
	else {
		printf("already visited or no right cell at (%d,%d)\n", here_x, here_y);
	}
	// dfs to lower cell
	printf("testing lower cell at (%d,%d)\n", here_x, here_y);
	if (here_y < puzzle.size() - 1 && !puzzle[here_y+1][here_x]) {
		printf("going down at (%d,%d)\n", here_x, here_y);
		dfs(puzzle, here_x, here_y+1);
	}
	else {
		printf("already visited or no lower cell at (%d,%d)\n", here_x, here_y);
	}
	// dfs to left cell
	printf("testing left cell at (%d,%d)\n", here_x, here_y);
	if (here_x > 0 && !puzzle[here_y][here_x-1]) {
		printf("going left at (%d,%d)\n", here_x, here_y);
		dfs(puzzle, here_x-1, here_y);
	}
	else {
		printf("already visited or no left cell at (%d,%d)\n", here_x, here_y);
	}
	// dfs to upper cell
	printf("testing upper cell at (%d,%d)\n", here_x, here_y);
	if (here_y > 0 && !puzzle[here_y-1][here_x]) {
		printf("going up at (%d,%d)\n", here_x, here_y);
		dfs(puzzle, here_x, here_y-1);
	}
	else {
		printf("already visited or no upper cell at (%d,%d)\n", here_x, here_y);
	}
	printf("returning from (%d,%d) cell\n", here_x, here_y);
}

pair<int,int> find_first_empty_cell(const vector<vector<bool> >& puzzle) {
	int x;
	int y;
	for (y = 0; y < puzzle.size(); ++y) {
		for (x = 0; x < puzzle[y].size(); ++x) {
			if (!puzzle[y][x]) {
				return make_pair(x,y);
			}
		}
	}
	return make_pair(-1,-1);
}

int main() {
	// case #1
	cout << "test case #1" << endl;
	// initialize the puzzle
	bool puzzle_array[5][5] = {
		{  true,  true, false, false, false },
		{ false, false, false,  true, false },
		{  true,  true, false,  true,  true },
		{ false,  true, false, false, false },
		{ false, false, false,  true,  true }
	}; 
	vector<vector<bool> > puzzle;
	for (int i = 0; i < 5; ++i) {
		puzzle.push_back(vector<bool>(puzzle_array[i], puzzle_array[i] + 5));
	}

	// find the first empty cell
	pair<int, int> empty_cell = find_first_empty_cell(puzzle);
	if (empty_cell.first == -1 && empty_cell.second == -1) {
		cout << "No empty cell in the puzzle" << endl;
		return 1;
	}

	// run dfs on it. This will traverse the whole graph
	dfs(puzzle, empty_cell.first, empty_cell.second);

	// check whether thers is any non-visited cell
	for (int y = 0; y < puzzle.size(); ++y) {
		for (int x = 0; x < puzzle[y].size(); ++x) {
			if (!puzzle[y][x]) {
				cout << "found non-visited cell at (" << x << "," << y << "). the puzzle is wrong" << endl;
				return 1;
			}
		}
	}
	
	cout << "the puzzle is correct" << endl << endl << endl;

	// case #2
	cout << "test case #2" << endl;
	// initialize the puzzle
	bool puzzle_array2[5][5] = {
		{  true,  true, false, false,  true },
		{ false, false, false,  true, false },
		{  true,  true, false,  true,  true },
		{ false,  true, false, false, false },
		{ false, false, false,  true,  true }
	}; 
	puzzle.clear();
	for (int i = 0; i < 5; ++i) {
		puzzle.push_back(vector<bool>(puzzle_array2[i], puzzle_array2[i] + 5));
	}

	// find the first empty cell
	empty_cell = find_first_empty_cell(puzzle);
	if (empty_cell.first == -1 && empty_cell.second == -1) {
		cout << "No empty cell in the puzzle" << endl;
		return 1;
	}

	// run dfs on it. This will traverse the whole graph
	dfs(puzzle, empty_cell.first, empty_cell.second);

	// check whether thers is any non-visited cell
	for (int y = 0; y < puzzle.size(); ++y) {
		for (int x = 0; x < puzzle[y].size(); ++x) {
			if (!puzzle[y][x]) {
				cout << "found non-visited cell at (" << x << "," << y << "). the puzzle is wrong" << endl;
				return 1;
			}
		}
	}
	cout << "the puzzle is correct" << endl;

	return 0;
}

