/*
Implement the StreamChecker class as follows:

    StreamChecker(words): Constructor, init the data structure with the given words.
    query(letter): returns true if and only if for some k >= 1, the last k characters queried (in order from oldest to newest, including this letter just queried) spell one of the words in the given list.



Example:

StreamChecker streamChecker = new StreamChecker(["cd","f","kl"]); // init the dictionary.
streamChecker.query('a');          // return false
streamChecker.query('b');          // return false
streamChecker.query('c');          // return false
streamChecker.query('d');          // return true, because 'cd' is in the wordlist
streamChecker.query('e');          // return false
streamChecker.query('f');          // return true, because 'f' is in the wordlist
streamChecker.query('g');          // return false
streamChecker.query('h');          // return false
streamChecker.query('i');          // return false
streamChecker.query('j');          // return false
streamChecker.query('k');          // return false
streamChecker.query('l');          // return true, because 'kl' is in the wordlist



Note:

    1 <= words.length <= 2000
    1 <= words[i].length <= 2000
    Words will only consist of lowercase English letters.
    Queries will only consist of lowercase English letters.
    The number of queries is at most 40000.

*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <list>

using namespace std;

class StreamChecker {
    struct node {
        char c;
        bool term;
        unordered_map<char, node*> children;

        node(char ch) : c(ch), term(false), children() {}
    };

    using dict_t = unordered_map<char, node*>;

    void add_word(const string& word) {
        node* pn = nullptr;
        dict_t* pd = &dict;
        for (auto c : word) {
            if (!(*pd)[c]) {
                (*pd)[c] = new node(c);
            }
            pn = (*pd)[c];
            pd = &((*pd)[c]->children);
        }

        pn->term = true;
    }

    node* search_letter(node* parent, char c) {
        if (!parent) {
            return dict[c];
        }
        else {
            return parent->children[c];
        }
    }

    dict_t dict;

    list<node*> wait_list;

public:
    StreamChecker(const vector<string>& words) {
        for (auto w : words) {
            add_word(w);
        }
    }

    bool query(char letter) {
        int nfound = 0;
        for (auto ni = wait_list.begin(); ni != wait_list.end();) {
            auto nn = search_letter(*ni, letter);
            if (!nn) {
                auto idel = ni;
                ++ni;
                wait_list.erase(idel);
            }
            else {
                if (nn->term) {
                    ++nfound;
                }
                *ni = nn;
                ++ni;
            }
        }

        auto nn = search_letter(nullptr, letter);
        if (nn) {
            wait_list.push_back(nn);
            if (nn->term) {
                ++nfound;
            }
        }

        return nfound > 0 ? true : false;
    }
};

int main() {
    StreamChecker checker({ "cd", "f", "kl" });
    cout << checker.query('a') << endl;
    cout << checker.query('b') << endl;
    cout << checker.query('c') << endl;
    cout << checker.query('d') << endl;
    cout << checker.query('e') << endl;
    cout << checker.query('f') << endl;
    cout << checker.query('g') << endl;
    cout << checker.query('h') << endl;
    cout << checker.query('i') << endl;
    cout << checker.query('j') << endl;
    cout << checker.query('k') << endl;
    cout << checker.query('l') << endl;

    StreamChecker checker2({ "ab","ba","aaab","abab","baa" });
    cout << checker2.query('a') << endl;
    cout << checker2.query('a') << endl;
    cout << checker2.query('a') << endl;
    cout << checker2.query('a') << endl;
    cout << checker2.query('a') << endl;
    cout << checker2.query('b') << endl;
    cout << checker2.query('a') << endl;
    cout << checker2.query('b') << endl;
    cout << checker2.query('a') << endl;
    cout << checker2.query('b') << endl;
    cout << checker2.query('b') << endl;
    cout << checker2.query('b') << endl;
    cout << checker2.query('a') << endl;
    cout << checker2.query('b') << endl;
    cout << checker2.query('a') << endl;
    cout << checker2.query('b') << endl;
    cout << checker2.query('b') << endl;
    cout << checker2.query('b') << endl;
    cout << checker2.query('b') << endl;
    cout << checker2.query('a') << endl;
    cout << checker2.query('b') << endl;
    cout << checker2.query('a') << endl;
    cout << checker2.query('b') << endl;
    cout << checker2.query('a') << endl;
    cout << checker2.query('a') << endl;
    cout << checker2.query('a') << endl;
    cout << checker2.query('b') << endl;
    cout << checker2.query('a') << endl;
    cout << checker2.query('a') << endl;
    cout << checker2.query('a') << endl;
}
