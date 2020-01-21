#include <iostream>
#include <utility>
#include <cassert>

using namespace std;

pair<int, int> is_same_upto(const string& s, const string& t, int i, int j) {
    while (i < (int)s.size() && j < (int)t.size() && s[i] == t[j]) {
        ++i, ++j;
    }

    return make_pair(i, j);
}

bool isOneEditDistance(string s, string t) {
    if (s.size() > t.size()) {
        swap(s, t);
    }

    auto [i, j] = is_same_upto(s, t, 0, 0);
    if (i == s.size() && j == t.size()) {
        return false;
    }

    auto [k, l] = is_same_upto(s, t, i, j + 1);     // delete or insert
    if (k == s.size() && l == t.size()) {
        return true;
    }

    auto [m, n] = is_same_upto(s, t, i + 1, j + 1); // replace
    return m == s.size() && n == t.size();
}

int main()
{
    assert(isOneEditDistance("a", "A"));
}

