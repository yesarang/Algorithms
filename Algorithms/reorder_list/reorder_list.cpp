#include <iostream>
#include <tuple>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

tuple<ListNode*, ListNode*> divide_list(ListNode* head)
{
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next;
        fast = fast->next;
    }

    ListNode* nl = slow->next;
    slow->next = nullptr;

    return make_tuple(head, nl);
}

ListNode* reverse_list(ListNode* l)
{
    if (!l) {
        return nullptr;
    }

    ListNode* nl = nullptr;
    ListNode* cur = nullptr;

    while (l) {
        cur = l;
        l = l->next;
        cur->next = nl;
        nl = cur;
    }

    return nl;
}

ListNode* merge_list(ListNode* l1, ListNode* l2)
{
    if (!l1) {
        return l2;
    }
    else if (!l2) {
        return l1;
    }

    ListNode* nl = nullptr;
    ListNode* last = nullptr;
    ListNode* f1 = nullptr;
    ListNode* f2 = nullptr;

    while (l1 && l2) {
        f1 = l1->next;
        f2 = l2->next;

        if (!nl) {
            nl = l1;
            last = nl;
            last->next = l2;
            last = l2;
        }
        else {
            last->next = l1;
            last = last->next;
            last->next = l2;
            last = last->next;
        }

        l1 = f1;
        l2 = f2;
    }

    if (l1) {
        last->next = l1;
    }
    else if (l2) {
        last->next = l2;
    }

    return nl;
}

ostream& operator<<(ostream& os, ListNode* head)
{
    while (head) {
        os << head->val << ", ";
        head = head->next;
    }

    return os;
}

void reorderList(ListNode* head) {
    if (!head) {
        return;
    }

    auto [l1, l2] = divide_list(head);
    l2 = reverse_list(l2);
    merge_list(l1, l2);
}

int main()
{
    auto l = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));

    cout << l << endl;

    reorderList(l);

    cout << l << endl;
}
