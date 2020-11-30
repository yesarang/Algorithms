/*
Leetcode: https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/

381. Insert Delete GetRandom O(1) - Duplicates allowed

Design a data structure that supports all following operations in average O(1) time.

Note: Duplicate elements are allowed.
insert(val): Inserts an item val to the collection.
remove(val): Removes an item val from the collection if present.
getRandom: Returns a random element from current collection of elements.
The probability of each element being returned is linearly related to the number of same value the collection contains.

Example:

// Init an empty collection.
RandomizedCollection collection = new RandomizedCollection();

// Inserts 1 to the collection. Returns true as the collection did not contain 1.
collection.insert(1);

// Inserts another 1 to the collection. Returns false as the collection contained 1. Collection now contains [1,1].
collection.insert(1);

// Inserts 2 to the collection, returns true. Collection now contains [1,1,2].
collection.insert(2);

// getRandom should return 1 with the probability 2/3, and returns 2 with the probability 1/3.
collection.getRandom();

// Removes 1 from the collection, returns true. Collection now contains [1,2].
collection.remove(1);

// getRandom should return 1 and 2 both equally likely.
collection.getRandom();
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>
#include <ctime>

using namespace std;

class RandomizedCollection {
    unordered_map<int, unordered_set<int>> val2idx;
    vector<int> vals;

public:
    /** Initialize your data structure here. */
    RandomizedCollection()
        : val2idx(), vals()
    {
        std::srand(std::time(nullptr));
    }

    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        bool not_contain = val2idx.find(val) == val2idx.end();

        vals.push_back(val);
        val2idx[val].insert(vals.size() - 1);

        return not_contain;
    }

    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        bool contained = val2idx[val].size() > 0;
        if (contained) {
            int nvi = *(val2idx[val].begin());
            val2idx[val].erase(nvi);

            int rvi = vals.size() - 1;
            vals[nvi] = vals[rvi];

            if (nvi < vals.size() - 1) {
                val2idx[vals[nvi]].erase(rvi);
                val2idx[vals[nvi]].insert(nvi);
            }

            vals.pop_back();
        }

        return contained;
    }

    /** Get a random element from the collection. */
    int getRandom() {
        return vals[rand() % vals.size()];
    }
};

int main()
{
    RandomizedCollection rc;

    rc.insert(10);
    rc.insert(10);
    rc.insert(20);
    rc.insert(20);
    rc.insert(30);
    rc.insert(30);

    rc.remove(10);
    rc.remove(20);
    rc.remove(20);
    rc.remove(10);
    rc.remove(30);

    rc.insert(40);

    rc.remove(30);
    rc.remove(30);

    for (int i = 0; i < 10; ++i) {
        cout << rc.getRandom() << endl;
    }
}
