/*
Leet code: https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/

We are given a binary tree (with root node root), a target node, and an integer value K.

Return a list of the values of all nodes that have a distance K from the target node.  The answer can be returned in any order.

Example 1:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2

Output: [7,4,1]

Explanation:
The nodes that are a distance 2 from the target node (with value 5)
have values 7, 4, and 1.

Note that the inputs "root" and "target" are actually TreeNodes.
The descriptions of the inputs above are just serializations of these objects.
*/

#include <iostream>
#include <stack>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* l, TreeNode* r) : val(x), left(l), right(r) {}
};

void get_depth_list(TreeNode* root, int tdepth, vector<int>& depth_list)
{
    if (!root) {
        return;
    }

    if (tdepth > 0) {
        get_depth_list(root->left, tdepth - 1, depth_list);
        get_depth_list(root->right, tdepth - 1, depth_list);
    }
    else {
        depth_list.push_back(root->val);
    }
}

using parent_stack = stack <pair<TreeNode*, bool/*go_left*/>>;

// returns true if target node has been found
bool search_all_dist_k_from_target(parent_stack& s, TreeNode* node, TreeNode* tnode, int K, vector<int>& kdist_list)
{
    if (!node) {
        return false;
    }

    if (node == tnode) {
        get_depth_list(node, K, kdist_list);

        int dist = 0;
        while (K > dist && !s.empty()) {
            auto [parent, go_left] = s.top();
            s.pop();

            // We went up, so increase dist.
            ++dist;

            if (K - dist == 0) {
                kdist_list.push_back(parent->val);
                break;
            }

            // We're going down, so increase dist again.
            get_depth_list((go_left ? parent->left : parent->right), K - dist - 1, kdist_list);
        }

        return true;
    }
    else {
        s.push(make_pair(node, false));
        if (search_all_dist_k_from_target(s, node->left, tnode, K, kdist_list)) {
            return true;
        }

        // set go_left to true since we're going to right
        s.top().second = true;
        bool found = search_all_dist_k_from_target(s, node->right, tnode, K, kdist_list);

        if (!found) {
            s.pop();
        }

        return found;
    }
}

void make_edges_from_node_to_parent(TreeNode* node, TreeNode* parent, unordered_map<TreeNode*, TreeNode*>& node_to_parent)
{
    if (!node) {
        return;
    }

    node_to_parent.insert(make_pair(node, parent));
    make_edges_from_node_to_parent(node->left, node, node_to_parent);
    make_edges_from_node_to_parent(node->right, node, node_to_parent);
}

vector<int> kdist_helper(TreeNode* target, int K, unordered_map<TreeNode*, TreeNode*>& node_to_parent)
{
    vector<int> ret;
    unordered_set<TreeNode*> visited;

    queue<pair<TreeNode*, int/*distance from target*/>> q;
    q.push(make_pair(target, 0));
    visited.insert(target);

    while (!q.empty()) {
        auto [node, dist] = q.front();
        q.pop();

        if (dist == K) {
            ret.push_back(node->val);
            continue;
        }

        if (node->left && visited.find(node->left) == visited.end()) {
            visited.insert(node->left);
            q.push(make_pair(node->left, dist + 1));
        }
        if (node->right && visited.find(node->right) == visited.end()) {
            visited.insert(node->right);
            q.push(make_pair(node->right, dist + 1));
        }
        if (node_to_parent.find(node) != node_to_parent.end()) {
            if (auto parent = node_to_parent[node]; parent && visited.find(parent) == visited.end()) {
                visited.insert(parent);
                q.push(make_pair(parent, dist + 1));
            }
        }
    }

    return move(ret);
}

enum AlgoKind {
    AlgoKind1,
    AlgoKind2,
};

vector<int> distanceK(TreeNode* root, TreeNode* target, int K, AlgoKind algo_kind )
{
    switch (algo_kind) {
    /* Algorithm 1:
    - Used only dfs.
    - Search the target first using dfs and while doing dfs, set up parent node's path
      for K depth list using stack
    - When the target is found, call depth_list algorithm with K
    */
    case AlgoKind1:
    {
        vector<int> kdist_list;
        parent_stack s;

        search_all_dist_k_from_target(s, root, target, K, kdist_list);

        return kdist_list;
    }

    /* Algorith 2:
    Basically, leverage bfs graph algorithm by
    converting the tree to a graph using unordered_map & dfs where
    parent node is also a neighbor.

    Each node has neighbor node->left, node->right, and map[node] == parent.
    */
    case AlgoKind2:
    {
        unordered_map<TreeNode*, TreeNode*> node_to_parent;

        make_edges_from_node_to_parent(root, nullptr, node_to_parent);

        return move(kdist_helper(target, K, node_to_parent));
    }
    }
}

ostream& operator<<(ostream& os, const vector<int>& v)
{
    for (auto e : v) {
        os << e << ", ";
    }
    return os;
}

int main()
{
    TreeNode* target =
        new TreeNode(5,
            new TreeNode(6),
            new TreeNode(2, new TreeNode(7), new TreeNode(4))
        );

    TreeNode* root =
        new TreeNode(3,
            target,
            new TreeNode(1, new TreeNode(0), new TreeNode(8))
        );

    cout << distanceK(root, target, 2, AlgoKind1) << endl;
    cout << distanceK(root, target, 2, AlgoKind2) << endl;

    TreeNode* t1 = new TreeNode(2);
    TreeNode* r1 =
        new TreeNode(0,
            new TreeNode(1, new TreeNode(3), t1),
            nullptr
        );

    cout << distanceK(r1, t1, 1, AlgoKind1) << endl;
    cout << distanceK(r1, t1, 1, AlgoKind2) << endl;

    TreeNode* t2 = new TreeNode(3);
    TreeNode* r2 =
        new TreeNode(0,
            new TreeNode(2),
            new TreeNode(1, t2, nullptr)
        );

    cout << distanceK(r2, t2, 3, AlgoKind1) << endl;
    cout << distanceK(r2, t2, 3, AlgoKind2) << endl;

    TreeNode* t3 = new TreeNode(3, nullptr, new TreeNode(4));
    TreeNode* r3 =
        new TreeNode(0,
            new TreeNode(0),
            new TreeNode(2, nullptr, t3)
            );

    cout << distanceK(r3, t3, 0, AlgoKind1) << endl;
    cout << distanceK(r3, t3, 0, AlgoKind2) << endl;
}

