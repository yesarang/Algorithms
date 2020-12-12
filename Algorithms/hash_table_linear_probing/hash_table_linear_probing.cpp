/*
Implement a linear probing hash table.
Linear probing means that in case of a collision, you put the value to the closest next empty bucket and each bucket can only have at most 1 value.
You don't need to worry about resize and you can assume that there's hash function for string.
int hash(const string& s);
class HashTable {
  public:
    HashTable(int capacity)
    {
        // TODO
    }
    void put(string key, string value) {
        // TODO
    }
    const string* get(string key) const {
        // TODO
    }
};
*/

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

class hash_table {
    struct kv_pair {
        const string* key = nullptr;
        string* val = nullptr;
    };

    int cap;
    vector<kv_pair> vals;
    const hash<string> hash;

    tuple<size_t, size_t> find_key_idx(const string& key) const
    {
        auto h = hash(key);
        auto oidx = h % cap;
        auto i = oidx;

        while (vals[i].key && *(vals[i].key) != key) {
            ++i;
            i %= cap;

            if (i == oidx) {
                return make_tuple(oidx, cap + 1);
            }
        }

        return make_tuple(oidx, i);
    }

public:
    hash_table(int capacity)
        : cap(capacity)
        , vals(capacity, kv_pair{})
        , hash()
    {}

    bool put(const string& key, const string& value)
    {
        auto [oidx, i] = find_key_idx(key);

		if (i > cap) {
			cout << "hash table is full" << endl;
			return false;
		}

	    if (i != oidx) {
            cout << "conflict! org pos = " << oidx << " new pos = " << i << endl;
        }

        if (!vals[i].key) {
            cout << "inserting " << key << "=" << value << endl;
            vals[i].key = new string(key);
        }
        else {
            cout << "updating " << key << "=" << value << endl;
            delete vals[i].val;
        }

        vals[i].val = new string(value);

        return true;
    }

    const string* get(const string& key) const
    {
        auto [oidx, i] = find_key_idx(key);

        if (i > cap || !vals[i].key) {
            return nullptr;
        }
        else {
            return vals[i].val;
        }
    }
};

string safe_get(const hash_table& ht, const string& key)
{
    auto val = ht.get(key);
    return val ? *val : "null";
}

int main()
{
    hash_table ht(10);

    ht.put("A", "1");
    ht.put("B", "2");
    ht.put("C", "3");
    ht.put("D", "4");
    ht.put("E", "5");
    ht.put("F", "6");
    ht.put("G", "7");
    ht.put("H", "8");
    ht.put("I", "9");
    ht.put("J", "10");
    ht.put("K", "11");
    ht.put("A", "12");
    ht.put("J", "13");

    cout << safe_get(ht, "A") << endl;
    cout << safe_get(ht, "B") << endl;
    cout << safe_get(ht, "C") << endl;
    cout << safe_get(ht, "D") << endl;
    cout << safe_get(ht, "E") << endl;
    cout << safe_get(ht, "F") << endl;
    cout << safe_get(ht, "G") << endl;
    cout << safe_get(ht, "H") << endl;
    cout << safe_get(ht, "I") << endl;
    cout << safe_get(ht, "J") << endl;
    cout << safe_get(ht, "K") << endl;
}

