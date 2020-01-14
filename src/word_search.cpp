/*
Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell, where 'adjacent' cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.



Example:

Input:
board = {
  {'o','a','a','n'},
  {'e','t','a','e'},
  {'i','h','k','r'},
  {'i','f','l','v'}
}
words = {'oath','pea','eat','rain'}

Output: {'eat','oath'}



Note:

    All inputs are consist of lowercase letters a-z.
    The values of words are distinct.
*/

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <unordered_set>

using namespace std;

vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    vector<string> ret;

    int nwords = words.size();
    int nrows = board.size();
    int ncols = nrows > 0 ? board[0].size() : 0;

    if (nwords == 0 || nrows == 0 || ncols == 0) {
        return ret;
    }

    const vector<pair<int, int>> dir = {
        { -1,  0 },  // up
        {  0,  1 },  // right
        {  1,  0 },  // down
        {  0, -1 },  // left
    };

    function<bool(int, int, const string&, int, vector<vector<bool>>&)> find_helper =
        [&](int ri, int ci, const string& word, int i, vector<vector<bool>>& visited) {
        if (i == word.size()) {
            return true;
        }

        visited[ri][ci] = true;

        for (auto [dri, dci] : dir) {
            auto nri = ri + dri;
            auto nci = ci + dci;
            if (0 <= nri && nri < nrows &&
                0 <= nci && nci < ncols &&
                 !visited[nri][nci] &&
                board[nri][nci] == word[i]) {
                return find_helper(nri, nci, word, i + 1, visited);
            }
        }

        return false;
    };

    unordered_set<string> found_words;
    for (int ri = 0; ri < nrows; ++ri) {
        for (int ci = 0; ci < ncols; ++ci) {
            for (auto word : words) {
                if (found_words.find(word) != found_words.end()) {
                    continue;
                }

                vector<vector<bool>> visited(nrows, vector<bool>(ncols, false));

                if (board[ri][ci] == word[0] && find_helper(ri, ci, word, 1, visited)) {
                    found_words.insert(word);
                    ret.emplace_back(word);
                }
            }
        }
    }

    return ret;
}

template <typename T>
void print(const vector<T>& solution) {
    size_t n = solution.size();
    if (n == 0) {
        cout << "[]" << endl;
        return;
    }

    cout << "[" << solution[0];
    for (size_t i = 1; i < n; ++i) {
        cout << "," << solution[i];
    }
    cout << "]" << endl;
}

int main() {
    vector<vector<char>> board = {
        {'o','a','a','n'},
        {'e','t','a','e'},
        {'i','h','k','r'},
        {'i','f','l','v'},
    };

    vector<string> words = {
        "oath", "pea", "eat", "rain",
    };

    print(findWords(board, words));

    board = {
        {'b','b','a','a','b','a'},
        {'b','b','a','b','a','a'},
        {'b','b','b','b','b','b'},
        {'a','a','a','b','a','a'},
        {'a','b','a','a','b','b'}
    };
    words = { "abbbababaa" };

    print(findWords(board, words));
}
