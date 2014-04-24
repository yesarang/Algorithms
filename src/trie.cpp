#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cassert>

using namespace std;

class trie_node {
private:
	trie_node* children[26];
	bool terminal;

public:
	trie_node() : terminal(false) {
		memset(children, 0, sizeof(children));
	}

	void insert(const char* key) {
		if (*key == '\0') {
			terminal = true;
			return;
		}

		int index = *key - 'A';
		if (!children[index]) {
			children[index] = new trie_node();
		}
		children[index]->insert(++key);
	}

	trie_node* find(const char* key) {
		if (*key == '\0') {
			return this;
		}

		int index = *key - 'A';
		if (!children[index]) {
			return 0;
		}
		else {
			return children[index]->find(++key);
		}
	}

	trie_node* find_terminal(const char* key) {
		trie_node* n = find(key);
		if (!n) {
			return 0;
		}
		else if (n->terminal) {
			return n;
		}
		else {
			return 0;
		}
	}

	void pre_order_traverse(const string& prefix, vector<string>& ret) {
		if (terminal) {
			ret.push_back(prefix);
		}
		for (int i = 0; i < 26; ++i) {
			if (children[i]) {
				string new_prefix{ prefix };
				new_prefix += (i + 'A');
				children[i]->pre_order_traverse(new_prefix, ret);
			}
		}
	}

	vector<string> get_strs(const char* prefix) {
		trie_node* n = find(prefix);
		vector<string> ret;
		n->pre_order_traverse(prefix, ret);
		return ret;
	}
};

int main() {
	trie_node* root{ new trie_node() };
	root->insert("BE");
	root->insert("BEAT");
	root->insert("BUS");
	root->insert("BUT");

	assert(root->find_terminal("BE"));
	assert(root->find_terminal("BEAT"));
	assert(root->find_terminal("BUS"));
	assert(root->find_terminal("BUT"));
	assert(!root->find_terminal("BU"));

	for (const auto& s : root->get_strs("BE")) {
		cout << s << endl;
	}

	for (const auto& s : root->get_strs("BU")) {
		cout << s << endl;
	}

	return 0;
}
