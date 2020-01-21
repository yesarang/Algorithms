/*
Leetcode: https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

297. Serialize and Deserialize Binary Tree
Serialization is the process of converting a data structure or object into a sequence of bits
so that it can be stored in a file or memory buffer, or transmitted across a network connection link
to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree.
There is no restriction on how your serialization/deserialization algorithm should work.
You just need to ensure that a binary tree can be serialized to a string and
this string can be deserialized to the original tree structure.
*/

#include <string>
#include <iostream>
#include <sstream>
#include <tuple>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* l, TreeNode* r) : val(x), left(l), right(r) {}
};

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

int main()
{
    TreeNode* t =
        new TreeNode(1,
            new TreeNode(2),
            new TreeNode(3, new TreeNode(4), new TreeNode(5))
            );

    Codec codec;

    auto s1 = codec.serialize(t);
    cout << s1 << endl;
    auto s2 = codec.serialize(codec.deserialize(s1));
    cout << s2 << endl;
}

