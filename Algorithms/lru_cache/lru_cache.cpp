/*
Leetcode: https://leetcode.com/problems/lru-cache/

146. LRU Cache
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
Follow up:
Could you do get and put in O(1) time complexity?

Example 1:

Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4
*/

#include <iostream>
#include <unordered_map>

using namespace std;

struct node {
    int val;
    int key;
    node* next;
    node* prev;
};

class LRUCache {
    unordered_map<int, node*> hash_map;
    node* head;
    node* tail;
    int nvals;

    const int cap_;

    void push_front(node* n)
    {
        n->prev = head;
        n->next = head->next;

        head->next->prev = n;
		head->next = n;
    }

    void remove_node(node* n)
    {
        n->prev->next = n->next;
        n->next->prev = n->prev;
    }

    void move_front(node* n)
    {
        remove_node(n);
        push_front(n);
    }

    node* push_front(int val, int key)
    {
        auto n = new node{ val, key, nullptr, nullptr };
        push_front(n);

        ++nvals;

        return n;
    }

    node* pop_back()
    {
        auto n = tail->prev;
		remove_node(n);
		--nvals;

        return n;
    }

public:
    LRUCache(int capacity)
        : hash_map()
        , head(new node{ -1, -1 })
        , tail(new node{ -1, -1 })
        , nvals(0)
        , cap_(capacity)
    {
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        auto i = hash_map.find(key);
        if (i != hash_map.end()) {
            move_front(i->second);

            return i->second->val;
        }
        else {
            return -1;
        }
    }

    void put(int key, int val) {
        auto i = hash_map.find(key);
        if (i == hash_map.end()) {
            auto n = push_front(val, key);
            hash_map.insert(make_pair(key, n));

            if (nvals > cap_) {
                auto dn = pop_back();
                hash_map.erase(dn->key);

                delete dn;
            }
        }
        else {
            i->second->val = val;
            move_front(i->second);
        }
    }
};

int main()
{
    LRUCache c(2);

    c.put(1, 1);
    c.put(2, 2);
    cout << c.get(1) << endl;
    c.put(3, 3);
    cout << c.get(2) << endl;
    c.put(4, 4);
    cout << c.get(1) << endl;
    cout << c.get(3) << endl;
    cout << c.get(4) << endl;
}

