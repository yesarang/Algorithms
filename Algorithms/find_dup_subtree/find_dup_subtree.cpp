/*
Leetcode: https://leetcode.com/problems/find-duplicate-subtrees/

652. Find Duplicate Subtrees

Given the root of a binary tree, return all duplicate subtrees.
For each kind of duplicate subtrees, you only need to return the root node of any one of them.
Two trees are duplicate if they have the same structure with the same node values.

Example 1:
Input: root = [1,2,3,4,null,2,4,null,null,4]
Output: [[2,4],[4]]

Example 2:
Input: root = [2,1,1]
Output: [[1]]

Example 3:
Input: root = [2,2,2,3,null,3,null]
Output: [[2,3],[3]]
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

struct TreeNode {
    static int seq_id;

    int id;
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : TreeNode(0) {}
    TreeNode(int x) : TreeNode(x, nullptr, nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : id(seq_id++), val(x), left(left), right(right)
    {}
};

int TreeNode::seq_id = 0;

class Codec {
    void serialize_helper(stringstream& strm, TreeNode* root) {
        if (!root) {
            strm << "N,";
            return;
        }

        strm << root->val << ",";
        serialize_helper(strm, root->left);
        serialize_helper(strm, root->right);
    }

    tuple<TreeNode*, int> deserialize_helper(const string& data, int i) {
        if (data[i] == 'N') {
            return make_tuple(nullptr, i + 2);
        }

        int icomma = data.find(',', i);
        auto val = stoi(data.substr(i, icomma - i));
        auto n = new TreeNode(val);

        auto [l, le] = deserialize_helper(data, icomma + 1);
        auto [r, re] = deserialize_helper(data, le);

        n->left = l;
        n->right = r;

        return make_tuple(n, re);
    }

public:
    string serialize(TreeNode* root) {
        stringstream strm;

        serialize_helper(strm, root);

        return strm.str();
    }

    TreeNode* deserialize(const string& data) {
        auto [r, _] = deserialize_helper(data, 0);

        return r;
    }
};

int find_dup_helper(
    TreeNode* node,
    int& tree_seq_id,
    unordered_map<string, int>& visited,
    unordered_map<int, int>& ndups,
    vector<TreeNode*>& duptrees
)
{
    if (!node) {
        return 0;
    }

    stringstream strm;
    strm << node->val << ","
        << find_dup_helper(node->left, tree_seq_id, visited, ndups, duptrees) << ","
        << find_dup_helper(node->right, tree_seq_id, visited, ndups, duptrees);
    auto tstr = strm.str();

    if (visited.find(tstr) == visited.end()) {
        visited.insert(make_pair(tstr, ++tree_seq_id));
    }

    auto tree_id = visited[tstr];
    ndups[tree_id]++;
    if (ndups[tree_id] == 2) {
        duptrees.push_back(node);
    }

    return tree_id;
}

vector<TreeNode*> findDuplicateSubtrees(TreeNode* root)
{
    unordered_map<string, int> visited;
    unordered_map<int, int> ndups;
    vector<TreeNode*> duptrees;

    int tree_seq_id = 0;
	find_dup_helper(root, tree_seq_id, visited, ndups, duptrees);

	return duptrees;
}

ostream& operator<<(ostream& os, TreeNode* t)
{
    Codec codec;
    os << codec.serialize(t);

    return os;
}

int main()
{
    Codec codec;
    auto t = codec.deserialize("0,0,0,N,N,N,0,N,0,N,0,N,N,");

    cout << codec.serialize(t) << endl;

    for (auto d : findDuplicateSubtrees(t)) {
        cout << d << endl;
    }
}

