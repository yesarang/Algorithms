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
#include <cassert>

using namespace std;

struct match_info {
    // target count
    int tcount;
    // remaining count
    int rcount;
    // Will maintain # of elems up to tcount
    // It's excessive matches if it's over tcount
    // So, pops up the front for excessive matches
    queue<int> matched_idx;
};

string minWindow(string s, string t) {
    unordered_map<char, match_info> match_map;
    for (auto c : t) {
        if (match_map.find(c) == match_map.end()) {
            match_map[c].tcount = 1;
            match_map[c].rcount = 1;
        }
        else {
            match_map[c].tcount++;
            match_map[c].rcount++;
        }
    }

    int lo = -1, hi = -1;
    int min_len = min(INT_MAX, (int)s.size() + 1);
    int max_lo = lo;
    int nrchars = t.size();

    while (hi < (int)s.size()) {
        if (nrchars == 0) {
            // If we matched all chars in t, reduce the maching windows
            // this is, advance lo up to the point where we no longer match all chars in t
            // and we update min_len along the way to see if we have
            // a shorter matching substring.
            do {
                ++lo;
                if (match_map.find(s[lo]) != match_map.end()) {
                    if (match_map[s[lo]].matched_idx.front() == lo) {
                        // This means that the current matched char at the index lo
                        // has contributed to matching t, and so we need to pops up the front and
                        // the char must go to remaining chars
                        ++nrchars;
                        match_map[s[lo]].matched_idx.pop();
                        match_map[s[lo]].rcount++;
                    }
                }

                if (nrchars == 0 && hi - lo < min_len) {
                    // This means that the current char at the index lo
                    // has not really contributed to matching t, and so
                    // we can reduce the min_len
                    max_lo = lo;
                    min_len = hi - max_lo;
                }

            } while (nrchars == 0);
        }
        else if (nrchars > 0) {
            // This means that there are still remaining chars to match,
            // and so, extend the matching window.
            do {
                ++hi;
                if (hi >= s.size()) {
                    break;
                }
                if (match_map.find(s[hi]) != match_map.end()) {
                    // This means that we find a matching char and so,
                    // we push the hi index to matched_idx queue and
                    // decrement remaining char count if it's not redundant.
                    match_map[s[hi]].matched_idx.push(hi);

                    if (match_map[s[hi]].rcount > 0) {
                        // This means that the current matching char is not
                        // redundant.
                        --nrchars;
                        match_map[s[hi]].rcount--;
                    }

                    if (match_map[s[hi]].matched_idx.size() > match_map[s[hi]].tcount) {
                        // This means that the current matching char is redundant.
                        // And so, don't forget to maintain the max # of elems
                        // for the matched_idx queue up to tcount.
                        match_map[s[hi]].matched_idx.pop();
                    }
                }
            } while (nrchars > 0);

            if (nrchars == 0 && hi - lo < min_len) {
                max_lo = lo;
                min_len = hi - max_lo;
            }
        }
        else {
            assert(!"This must not happen!!");
        }
    }

    return min_len <= (int)s.size() ? s.substr(max_lo + 1, min_len) : "";
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

    s = "cabwefgewcwaefgcf";
    t = "cae";
    cout << minWindow(s, t) << endl;
}
