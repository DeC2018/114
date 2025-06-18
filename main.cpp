#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    void flatten(TreeNode* root) {
        if (root == nullptr)
            return;

        flatten(root->left);
        flatten(root->right);

        TreeNode* const left = root->left;
        TreeNode* const right = root->right;

        root->left = nullptr;
        root->right = left;

        TreeNode* rightmost = root;
        while (rightmost->right)
            rightmost = rightmost->right;
        rightmost->right = right;
    }
};

// Helper function to create a binary tree from a vector
TreeNode* createTree(const vector<int>& nodes) {
    if (nodes.empty() || nodes[0] == -1) return nullptr;

    TreeNode* root = new TreeNode(nodes[0]);
    queue<TreeNode*> q;
    q.push(root);

    size_t index = 1;
    while (!q.empty() && index < nodes.size()) {
        TreeNode* current = q.front();
        q.pop();

        if (index < nodes.size() && nodes[index] != -1) {
            current->left = new TreeNode(nodes[index]);
            q.push(current->left);
        }
        index++;

        if (index < nodes.size() && nodes[index] != -1) {
            current->right = new TreeNode(nodes[index]);
            q.push(current->right);
        }
        index++;
    }

    return root;
}

// Helper function to print the flattened tree
void printFlattenedTree(TreeNode* root) {
    cout << "[";
    bool first = true;
    while (root) {
        if (!first) {
            cout << ",null,";
        } else {
            first = false;
        }
        cout << root->val;
        root = root->right;
    }
    cout << "]";
}

int main() {
    Solution solution;

    // Test cases
    vector<vector<int>> testCases = {
        {1, 2, 5, 3, 4, -1, 6},
        {},
        {0}
    };

    for (const auto& testCase : testCases) {
        TreeNode* root = createTree(testCase);
        solution.flatten(root);

        cout << "Input: root = [";
        for (size_t i = 0; i < testCase.size(); ++i) {
            if (i != 0) cout << ",";
            if (testCase[i] == -1) {
                cout << "null";
            } else {
                cout << testCase[i];
            }
        }
        cout << "]\nOutput: ";
        printFlattenedTree(root);
        cout << "\n";
    }

    return 0;
}
