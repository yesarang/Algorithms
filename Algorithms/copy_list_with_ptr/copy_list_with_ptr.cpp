#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

Node* copy_rand(unordered_map<Node*, Node*>& node_map, unordered_set<Node*>& visited, Node* rand_head)
{
    if (!rand_head) {
        return nullptr;
    }
    else if (node_map.find(rand_head) != node_map.end()) {
        return node_map[rand_head];
    }

    Node* nn = new Node(rand_head->val);
    if (visited.find(rand_head) == visited.end()) {
        visited.insert(rand_head);
        nn->random = copy_rand(node_map, visited, rand_head->random);
    }

    node_map[rand_head] = nn;

    return nn;
}

Node* copyRandomList(Node* head) {
    if (!head) {
        return nullptr;
    }

    unordered_map<Node*, Node*> node_map;
    Node* nl = nullptr;
    Node* last = nullptr;

    while (head) {
        unordered_set<Node*> visited;
        visited.insert(head);
        Node* new_random = copy_rand(node_map, visited, head->random);

        Node* nn = nullptr;
        if (node_map.find(head) != node_map.end()) {
            nn = node_map[head];
        }
        else {
            nn = new Node(head->val);
            node_map[head] = nn;
        }
        nn->random = new_random;

        if (!nl) {
            nl = nn;
            last = nl;
        }
        else {
            last->next = nn;
            last = last->next;
        }

        head = head->next;
    }

    return nl;
}

int main()
{
    auto node7 = new Node(7);
    auto node13 = new Node(13);
    auto node11 = new Node(11);
    auto node10 = new Node(10);
    auto node1 = new Node(1);

    node7->next = node13;

    node13->next = node11;
    node13->random = node7;

    node11->next = node10;
    node11->random = node1;

    node10->next = node1;
    node10->random = node11;

    node1->random = node7;

    auto nl = copyRandomList(node7);
}
