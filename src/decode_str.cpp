/*
Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].

Examples:

s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
*/

#include <iostream>
#include <string>

using namespace std;

bool is_number(char c) {
    return '1' <= c && c <= '9';
}

bool is_special(char c) {
    return is_number(c) || c == '[' || c == ']';
}

int compute_length(const string& s, int& i) {
    int len = 0;
    while (i < s.size()) {
        if (!is_special(s[i])) {
            ++len;
        }
        else if (is_number(s[i])) {
            char* end;
            int repeat = strtol(s.c_str() + i, &end, 10);
            i = end - s.c_str();
            ++i;

            len += repeat * compute_length(s, i);
        }
        else {
            // ']' case
            break;
        }

        ++i;
    }

    return len;
}

void decode(string& r, int& i, const string& s, int& j) {
    while (j < s.size()) {
        if (!is_special(s[j])) {
            r[i++] = s[j];
        }
        else if (is_number(s[j])) {
            char* end;
            int repeat = strtol(s.c_str() + j, &end, 10);
            j = end - s.c_str();
            ++j;

            int tj;
            while (repeat > 0) {
                tj = j;
                decode(r, i, s, tj);
                --repeat;
            }

            j = tj;
        }
        else {
            // ']' case
            break;
        }

        ++j;
    }
}

string decodeString(string s) {
    if (s.size() == 0) {
        return "";
    }

    int i = 0;
    string ret(compute_length(s, i), '0');

    i = 0;
    int j = 0;
    decode(ret, i, s, j);

    return ret;
}

int main() {
    cout << decodeString("3[a]2[bc]") << endl;

    cout << decodeString("3[a2[c]]") << endl;

    cout << decodeString("2[abc]3[cd]ef") << endl;
}
