#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

using namespace std;

int longestValidParentheses(string s) {
    size_t n = s.size();
    if (n < 2) {
        return 0;
    }

    size_t i = 0;
    vector<bool> valid(n, false);

    function<bool (int)> mark_valid_paren_helper = [&](int depth) {
        if (i >= n) {
            return false;
        }

        if (depth == 0) {
            while (i < n && s[i] == ')') {
                ++i;
            }
        }

        if (depth > 0 && s[i] == ')') {
            valid[i] = true;
            ++i;
            return true;
        }
        else {
            size_t start = i;
            ++i;
            auto found_valid_range = mark_valid_paren_helper(depth + 1);
            if (found_valid_range) {
                valid[start] = true;
            }

            mark_valid_paren_helper(depth);
        }
    };

    mark_valid_paren_helper(0);

    int max_len = 0;
    for (size_t j = 0; j < n;) {
        int len = 0;
        while (j < n && valid[j++]) {
            ++len;
        }

        max_len = max(max_len, len);
    }

    return max_len;
}

int main() {
    string s = "()";
    cout << "longest for " << s << ": " << longestValidParentheses(s) << endl;

    s = ")()())()()(";
    cout << "longest for " << s << ": " << longestValidParentheses(s) << endl;

    s = "())";
    cout << "longest for " << s << ": " << longestValidParentheses(s) << endl;

    s = "(()";
    cout << "longest for " << s << ": " << longestValidParentheses(s) << endl;

    s = ")(((())";
    cout << "longest for " << s << ": " << longestValidParentheses(s) << endl;

    s = ")()())";
    cout << "longest for " << s << ": " << longestValidParentheses(s) << endl;

    s = "(((()()())";
    cout << "longest for " << s << ": " << longestValidParentheses(s) << endl;

    s = "()(()()())";
    cout << "longest for " << s << ": " << longestValidParentheses(s) << endl;

    s = "(())(()";
    cout << "longest for " << s << ": " << longestValidParentheses(s) << endl;
}
