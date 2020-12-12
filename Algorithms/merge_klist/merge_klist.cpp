/*
Leetcode: https://leetcode.com/problems/merge-k-sorted-lists/

23. Merge k Sorted Lists
You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
Merge all the linked-lists into one sorted linked-list and return it.

Example 1:

Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]

merging them into one sorted list:
1->1->2->3->4->4->5->6

Example 2:

Input: lists = []
Output: []

Example 3:

Input: lists = [[]]
Output: []
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : ListNode(0) {}
    ListNode(int x) : ListNode(x, nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

template <>
struct std::greater<ListNode*> {
    bool operator()(const ListNode* lhs, const ListNode* rhs) const
    {
        return lhs->val > rhs->val;
    }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.size() == 0) {
        return nullptr;
    }

    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    // min heap
    priority_queue<ListNode*, vector<ListNode*>, greater<ListNode*>> pq;

    for (auto n : lists) {
        if (n) {
            pq.push(n);
        }
    }

    while (!pq.empty()) {
        auto cur = pq.top();
        auto next = cur->next;
        auto nn = new ListNode(cur->val);

        if (tail) {
            tail->next = nn;
            tail = nn;
        }
        else {
            tail = nn;
            head = nn;
        }

        pq.pop();

        if (next) {
            pq.push(next);
        }
    }

    return head;
}

ostream& operator<<(ostream& os, ListNode* l)
{
    while (l) {
        os << l->val << ",";
        l = l->next;
    }

    return os;
}

int main()
{
    vector<ListNode*> lists{
        new ListNode(1, new ListNode(4, new ListNode(5))),
        new ListNode(1, new ListNode(3, new ListNode(4))),
        new ListNode(2, new ListNode(6)),
    };

    cout << mergeKLists(lists) << endl;
}

