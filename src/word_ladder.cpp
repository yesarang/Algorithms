/*
Word Ladder

Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:

    Only one letter can be changed at a time.
    Each transformed word must exist in the word list. Note that beginWord is not a transformed word.

Note:

    Return 0 if there is no such transformation sequence.
    All words have the same length.
    All words contain only lowercase alphabetic characters.
    You may assume no duplicates in the word list.
    You may assume beginWord and endWord are non-empty and are not the same.

Example 1:

Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output: 5

Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Example 2:

Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Output: 0

Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
*/

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int ladderLength(string begin_word, string end_word, vector<string>& word_list) {
    int n = begin_word.size();
    unordered_map<string, vector<string>> g;
    for (auto word : word_list) {
        for (int i = 0; i < n; ++i) {
            auto iword = word.substr(0, i) + "*" + word.substr(i + 1, n - i - 1);
            g[iword].push_back(word);
        }
    }

    queue<tuple<string, int>> q;
    unordered_set<string> visited;

    q.push(make_tuple(begin_word, 1));
    visited.insert(begin_word);

    while (!q.empty()) {
        auto [word, path_length] = q.front();
        q.pop();

        for (int i = 0; i < n; ++i) {
            auto iword = word.substr(0, i) + "*" + word.substr(i + 1, n - i - 1);
            for (auto adj_word : g[iword]) {
                if (adj_word == end_word) {
                    return path_length + 1;
                }

                if (visited.find(adj_word) == visited.end()) {
                    q.push(make_tuple(adj_word, path_length + 1));
                    visited.insert(adj_word);
                }
            }
        }
    }

    return 0;
}

int main() {
    string begin_word = "hit";
    string end_word = "cog";
    vector<string> word_list = { "hot", "dot", "dog", "lot", "log", "cog" };

    cout << ladderLength(begin_word, end_word, word_list) << endl;
}
