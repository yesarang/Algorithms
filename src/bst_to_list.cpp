#include <iostream>
#include <tuple>
#include <functional>

using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

Node* treeToDoublyList(Node* root) {
    if (!root) {
        return nullptr;
    }

    function<tuple<Node*, Node*>(Node*)> impl =
        [&](Node* node) {
        Node* head = nullptr;
        Node* last = nullptr;
        Node* right = node->right;

        if (node->left) {
            auto [lhead, llast] = impl(node->left);

            llast->right = node;
            node->left = llast;
            node->right = lhead;
            lhead->left = node;

            head = lhead;
            last = node;
        }
        else {
            node->right = node;
            node->left = node;
            head = node;
            last = node;
        }

        if (right) {
            auto [rhead, rlast] = impl(right);

            last->right = rhead;
            rhead->left = last;
            rlast->right = head;
            head->left = rlast;
            last = rlast;
        }

        return make_tuple(head, last);
    };

    auto [head, _] = impl(root);

    return head;
}

void print(Node* head) {
    auto node = head;
    cout << node->val;
    node = head->right;

    while (node != head) {
        cout << "," << node->val;
        node = node->right;
    }
    cout << endl;
}

int main() {
    Node* t = new Node(4,
        new Node(2,
            new Node(1, nullptr, nullptr),
            new Node(3, nullptr, nullptr)),
        new Node(5, nullptr, nullptr));

    auto head = treeToDoublyList(t);
    print(head);
}

