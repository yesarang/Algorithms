#pragma warning(disable:4996)

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <future>

using namespace std;

typedef unordered_map<string, int> WordMap;
typedef pair<string, int> Datum;

ostream& operator<<(ostream& os, const Datum& datum) {
	os << datum.first << ": " << datum.second;
	return os;
}

template <typename FwdIter>
void print_list(FwdIter b, FwdIter e) {
	for_each(b, e, [](const typename FwdIter::value_type& s) {
		cout << s << endl;
	});
}

vector<string>
get_freq_words(istream& strm, int nwords) {
	// 1st step
	WordMap word_map;
	string word;
	while (strm >> word) { // time complexity -> O(N), N : total # of words, space complexity -> O(M), M : total # of unique words
		++word_map[word];
	}
	vector<Datum> min_heap;
	// comparator for minimum heap
	auto comp = [](const Datum& p1, const Datum& p2) {
		return p1.second >= p2.second;
	};

	// 2nd step
	for (auto p : word_map) { // time complexity -> O(M log nwords), space complexity -> O(nwords)
		min_heap.push_back(p);
		push_heap(min_heap.begin(), min_heap.end(), comp);
		if (min_heap.size() > nwords) {
			pop_heap(min_heap.begin(), min_heap.end(), comp);
			min_heap.pop_back();
		}
	}
	// sort the heap by opposite order of comp --> actually descending order
	sort_heap(min_heap.begin(), min_heap.end(), comp);
	vector<string> ret;
	for (auto p : min_heap) {
		ret.push_back(p.first);
	}
	return ret;
}

int main() {
	stringstream is(
		"aaaa aaaa aaaa aaaa aaaa aaaa aaaa "
		"bbbb bbbb bbbb bbbb bbbb bbbb "
		"cccc cccc cccc cccc cccc "
		"dddd dddd dddd dddd "
		"eeee eeee eeee "
		"ffff ffff "
		"gggg"
		);
	const vector<string> words2 = {
		"aaaa", "bbbb"
	};
	auto r = get_freq_words(is, 2);
	assert(equal(words2.begin(), words2.end(), r.begin()));
	print_list(r.begin(), r.end());

	const vector<string> words3 = {
		"aaaa", "bbbb", "cccc"
	};
	stringstream is2(
		"aaaa aaaa aaaa aaaa aaaa aaaa aaaa "
		"bbbb bbbb bbbb bbbb bbbb bbbb "
		"cccc cccc cccc cccc cccc "
		"dddd dddd dddd dddd "
		"eeee eeee eeee "
		"ffff ffff "
		"gggg"
		);
	r = get_freq_words(is2, 3);
	assert(equal(words3.begin(), words3.end(), r.begin()));
	print_list(r.begin(), r.end());

	const vector<string> words4 = {
		"aaaa", "bbbb", "cccc", "dddd"
	};
	stringstream is3(
		"aaaa aaaa aaaa aaaa aaaa aaaa aaaa "
		"bbbb bbbb bbbb bbbb bbbb bbbb "
		"cccc cccc cccc cccc cccc "
		"dddd dddd dddd dddd "
		"eeee eeee eeee "
		"ffff ffff "
		"gggg"
		);
	r = get_freq_words(is3, 4);
	assert(equal(words4.begin(), words4.end(), r.begin()));
	print_list(r.begin(), r.end());

	stringstream is4(
		"eeee eeee eeee "
		"ffff ffff "
		"gggg"
		);
	const vector<string> words43 = {
		"eeee", "ffff", "gggg"
	};
	r = get_freq_words(is4, 4);
	assert(equal(words43.begin(), words43.end(), r.begin()));
	print_list(r.begin(), r.end());

	stringstream is5(
		"aaaa aaaa aaaa aaaa aaaa aaaa aaaa "
		"bbbb bbbb bbbb bbbb bbbb bbbb "
		"cccc cccc cccc cccc cccc "
		"dddd dddd dddd dddd "
		"eeee eeee eeee "
		"ffff ffff "
		"gggg"
		);

	auto h = async(get_freq_words, ref(is5), 4);
	r = h.get();
	assert(equal(words4.begin(), words4.end(), r.begin()));
	print_list(r.begin(), r.end());
}
