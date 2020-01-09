#include <iostream>
#include <string>

using namespace std;

int to_num(char digit) {
    return digit - '0';
}

char to_char(int digit) {
    return static_cast<char>(digit + '0');
}

void mult_by_digit(string& res, const string& num, char digit, int nzero) {
    int i = res.size() - 1;
    for (; nzero > 0; --nzero, --i) {
        res[i] = to_char(0);
    }

    int carry_over = 0;
    int multiplier = to_num(digit);
    for (int j = num.size() - 1; j >= 0; --j, --i) {
        int ir = to_num(num[j]) * multiplier + carry_over;
        res[i] = to_char(ir % 10);
        carry_over = ir / 10;
    }
    res[i] = to_char(carry_over);
}

void add(string& num1, const string& num2, int nzero) {
    int carry_over = 0;
    int i = num1.size() - nzero - 1;
    for (; i >= 0; --i) {
        int ir = to_num(num1[i]) + to_num(num2[i]) + carry_over;
        num1[i] = to_char(ir % 10);
        carry_over = ir / 10;
    }
}

string multiply(string num1, string num2) {
    int n1 = num1.size();
    int n2 = num2.size();
    if (n1 == 0 || n2 == 0 ||
        num1 == "0" || num2 == "0") {
        return "0";
    }

    string ret(n1 + n2, to_char(0));
    string ir(n1 + n2, to_char(0));
    int nzero = 0;
    for (int i = n2 - 1; i >= 0; --i) {
        mult_by_digit(ir, num1, num2[i], nzero);
        add(ret, ir, nzero);
        ++nzero;
    }

    auto start = ret.find_first_not_of("0");
    return ret.substr(start, ret.size() - start);;
}

int main() {
    string num1("2");
    string num2("3");

    cout << multiply(num1, num2) << endl;

    num1 = "9";
    num2 = "9";

    cout << multiply(num1, num2) << endl;
}
