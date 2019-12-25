#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

using namespace std;

vector<string> generateLetterCombs(const string& digits) {
	vector<string> r;
	auto n = digits.size();
	if (n == 0) {
		return r;
	}

    unordered_map<char, string> noToCharMap = {
        { '2', "abc" },
        { '3', "def" },
        { '4', "ghi" },
        { '5', "jkl" },
        { '6', "mno" },
        { '7', "pqrs" },
        { '8', "tuv" },
        { '9', "wxyz" },
    };

    function<void (const string & comb, size_t digit_pos)> generate =
        [&](const string& comb, size_t digit_pos) {
            if (digit_pos == n) {
                r.push_back(comb);
                return;
            }

            auto digit = digits[digit_pos];
            auto chars = noToCharMap[digit];
            for (auto c : chars) {
                generate(comb + c, digit_pos + 1);
            }
        };

    generate("", 0);

    return r;
}

void print(const vector<string>& combs) {
    for (auto comb : combs) {
        cout << comb << endl;
    }
}

int main() {
    string digits = "23";

    print(generateLetterCombs(digits));

    return 0;
}