#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* merge_list(ListNode* l1, ListNode* l2)
{
    if (!l1) {
        return l2;
    }

    if (!l2) {
        return l1;
    }

    ListNode* nl = nullptr;
    ListNode* last = nullptr;

    while (l1 && l2) {
        if (l1->val < l2->val) {
            if (!nl) {
                nl = l1;
                last = nl;
            }
            else {
                last->next = l1;
                last = last->next;
            }

            l1 = l1->next;
        }
        else {
            if (!nl) {
                nl = l2;
                last = nl;
            }
            else {
                last->next = l2;
                last = last->next;
            }

            l2 = l2->next;
        }
    }

    if (l1) {
        last->next = l1;
    }
    else {
        last->next = l2;
    }

    return nl;
}

ostream& operator<<(ostream& os, ListNode* l)
{
    while (l) {
        cout << l->val << ", ";
        l = l->next;
    }

    return os;
}

int main()
{
    auto l1 = new ListNode(1, new ListNode(2, new ListNode(4)));
    auto l2 = new ListNode(1, new ListNode(3, new ListNode(4)));

    cout << "l1: " << l1 << endl;
    cout << "l2: " << l2 << endl;

    cout << "merged list: " << merge_list(l1, l2) << endl;
}

