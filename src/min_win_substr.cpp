/*
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).
Example:
Input: S = "ADOBECODEBANC", T = "ABC"
Output: "BANC"
Note:
    • If there is no such window in S that covers all characters in T, return the empty string "".
If there is such window, you are guaranteed that there will always be only one unique minimum window in S.
*/
#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

string minWindow(string s, string t) {
    int n = s.size();
    int m = t.size();
    if (n == 0 || m == 0) {
        return "";
    }

    unordered_map<char, bool> need_contain;
    for (auto c : t) {
        need_contain[c] = true;
    }
    int cnt = need_contain.size();

    unordered_map<char, int> found_set;
    queue<tuple<char, int>> q;

    int i = 0;
    while (i < n && !need_contain[s[i]]) {
        ++i;
    }
    if (i == n) {
        return "";
    }

    int start = i;
    found_set.insert(make_pair(s[i], 1));
    q.push(make_tuple(s[i], i));

    int end = -1;
    int min_win = INT_MAX;
    int min_win_start = -1;
    int min_win_end = -1;

    while (i < n) {
        if (found_set.size() < cnt) {
            ++i;

            while (i < n && !need_contain[s[i]]) {
                ++i;
            }
            if (i == n) {
                break;
            }

            q.push(make_tuple(s[i], i));
            ++found_set[s[i]];
        }
        else {
            end = i;
            if (auto win = end - start + 1; win < min_win) {
                min_win = win;
                min_win_start = start;
                min_win_end = end;
            }

            if (min_win == cnt) {
                break;
            }

            if (auto c = get<0>(q.front()); --found_set[c] == 0) {
                found_set.erase(c);
            }
            q.pop();
            start = get<1>(q.front());
        }
    }

    return s.substr(min_win_start, min_win);
}

int main() {
    string s = "ADOBECODEBANC";
    string t = "ABC";

    cout << minWindow(s, t) << endl;

    s = "a";
    t = "a";
    cout << minWindow(s, t) << endl;

    s = "a";
    t = "aa";
    cout << minWindow(s, t) << endl;
}
