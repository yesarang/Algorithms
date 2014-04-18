// Example: A ransom note can be formed by cutting words out of a magazine to form a new
// sentence.How would you figure out if a ransom note(represented as a string) can be formed
// from a given magazine(string) ?

#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

void construct_word_map(const string& str, unordered_map<string, unsigned>& map) {
	stringstream strm(str);
	string token;
	while (strm >> token) {
		++map[token];
	}
}

bool is_possible(const string& ransom_note, const string& magazine) {
	unordered_map<string, unsigned> ransom_note_word_map;
	construct_word_map(ransom_note, ransom_note_word_map);
	unordered_map<string, unsigned> magazine_word_map;
	construct_word_map(magazine, magazine_word_map);

	for (auto p : ransom_note_word_map) {
		if (magazine_word_map[p.first] < p.second) {
			return false;
		}
	}
	return true;
}

string quote(const string& str) {
	return "\"" + str + "\"";
}

int main() {
	string n1 = "I love you";
	string m1 = "I love me and you";
	if (is_possible(n1, m1)) {
		cout << quote(n1) << " is composable from " << quote(m1) << endl;
	}
	else {
		cout << quote(n1) << " is not composable from " << quote(m1) << endl;
	}

	string n2 = "I love you";
	string m2 = "I love him";
	if (is_possible(n2, m2)) {
		cout << quote(n2) << " is composable from " << quote(m2) << endl;
	}
	else {
		cout << quote(n2) << " is not composable from " << quote(m2) << endl;
	}

	n2 = "";
	m2 = "";
	if (is_possible(n2, m2)) {
		cout << quote(n2) << " is composable from " << quote(m2) << endl;
	}
	else {
		cout << quote(n2) << " is not composable from " << quote(m2) << endl;
	}

	return 0;
}