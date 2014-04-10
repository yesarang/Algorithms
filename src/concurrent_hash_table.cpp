#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <cassert>
#include <mutex>

using namespace std;

const int HASH_TBL_SZ = 4095;

typedef pair<int,int> key_value_pair_t;
typedef list<key_value_pair_t>::iterator key_value_pair_pos_t;
typedef pair<mutex,list<key_value_pair_t> > locked_list_t;

vector<locked_list_t> hash_table(HASH_TBL_SZ);

unsigned hash(int key) {
	return static_cast<unsigned>(key) % HASH_TBL_SZ;
}

bool hash_table_is_key_exist(int key) {
	unsigned hash_val = hash(key);
	{
		lock_guard lck(hash_table[hash_val].first);
		return hash_table_is_key_exist_impl(hash_table[hash_val].second);
	}
}

bool hash_table_is_key_exist_impl(const list<key_value_pair_t>& list, int key) {
	for (key_value_pair_pos_t pos = list.begin(); pos != list.end(); ++pos) {
		if (pos->first == key) {
			return true;
		}
	}
	return false;
}

bool hash_table_insert(int key, int val) {
	unsigned hash_val = hash(key);
	{
		lock_guard lck(hash_table[hash_val].first;
		// first check whether the key is already present
		if (hash_table_is_key_exist_impl(hash_table[hash_val].second, key)) {
			return false;
		}

		hash_table[hash_val].second.push_back(make_pair(key, val));
		return true;
	}
}

pair<bool,int> hash_table_get(int key) {
	unsigned hash_val = hash(key);
	{
		lock_guard lck(hash_table[hash_val].first;
		for (key_value_pair_pos_t pos = hash_table[hash_val].second.begin();
			 pos != hash_table[hash_val].second.end(); ++pos) {
			if (pos->first == key) {
				return make_pair(true, pos->second);
			}
		}
		return make_pair(false,0);
	}
}

int main() {
	assert(hash_table_insert(1,10));
	cout << "(1,10) inserted" << endl;
	assert(hash_table_is_key_exist(1));
	cout << "key 1 present" << endl;
	assert(!hash_table_is_key_exist(2));
	cout << "key 2 absent" << endl;
	pair<bool,int> ret = hash_table_get(1);
	assert(ret.first && ret.second == 10);
	cout << "key 1 --> " << ret.second << endl;

	assert(hash_table_insert(2,20));
	assert(hash_table_insert(3,30));
	assert(hash_table_is_key_exist(2));
	assert(hash_table_is_key_exist(3));
	ret = hash_table_get(2);
	assert(ret.first && ret.second == 20);
	ret = hash_table_get(3);
	assert(ret.first && ret.second == 30);
}

