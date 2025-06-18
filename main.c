#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void flatten(struct TreeNode* root) {
    struct TreeNode* curr = root;

    while (curr != NULL) {
        if (curr->left != NULL) {
            struct TreeNode* prev = curr->left;

            while (prev->right != NULL) {
                prev = prev->right;
            }
            
            prev->right = curr->right;
            curr->right = curr->left;
            curr->left = NULL;
        }

        curr = curr->right;
    }
}

// Helper function to create a binary tree from an array
struct TreeNode* createTree(int* nodes, int size) {
    if (size == 0) return NULL;

    struct TreeNode** treeArray = (struct TreeNode**)malloc(size * sizeof(struct TreeNode*));
    for (int i = 0; i < size; i++) {
        if (nodes[i] != -1) {
            treeArray[i] = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            treeArray[i]->val = nodes[i];
            treeArray[i]->left = NULL;
            treeArray[i]->right = NULL;
        } else {
            treeArray[i] = NULL;
        }
    }

    for (int i = 0; i < size; i++) {
        if (treeArray[i] == NULL) continue;
        
        int leftIndex = 2 * i + 1;
        int rightIndex = 2 * i + 2;
        
        if (leftIndex < size) {
            treeArray[i]->left = treeArray[leftIndex];
        }
        if (rightIndex < size) {
            treeArray[i]->right = treeArray[rightIndex];
        }
    }

    struct TreeNode* root = treeArray[0];
    free(treeArray);
    return root;
}

// Helper function to print the flattened tree
void printFlattenedTree(struct TreeNode* root) {
    printf("[");
    int first = 1;
    while (root != NULL) {
        if (!first) {
            printf(",null,");
        } else {
            first = 0;
        }
        printf("%d", root->val);
        root = root->right;
    }
    printf("]");
}

int main() {
    // Test cases
    int testCase1[] = {1, 2, 5, 3, 4, -1, 6};
    int testCase2[] = {};
    int testCase3[] = {0};

    int size1 = sizeof(testCase1) / sizeof(testCase1[0]);
    int size2 = sizeof(testCase2) / sizeof(testCase2[0]);
    int size3 = sizeof(testCase3) / sizeof(testCase3[0]);

    struct TreeNode* root1 = createTree(testCase1, size1);
    struct TreeNode* root2 = createTree(testCase2, size2);
    struct TreeNode* root3 = createTree(testCase3, size3);

    flatten(root1);
    flatten(root2);
    flatten(root3);

    // Print results
    printf("Input: root = [");
    for (int i = 0; i < size1; i++) {
        if (i != 0) printf(",");
        if (testCase1[i] == -1) {
            printf("null");
        } else {
            printf("%d", testCase1[i]);
        }
    }
    printf("]\nOutput: ");
    printFlattenedTree(root1);
    printf("\n");

    printf("Input: root = []\nOutput: ");
    printFlattenedTree(root2);
    printf("\n");

    printf("Input: root = [0]\nOutput: ");
    printFlattenedTree(root3);
    printf("\n");

    // Free memory
    // Note: In a real application, you would need to properly free all tree nodes
    // This is simplified for the example
    free(root1);
    free(root2);
    free(root3);

    return 0;
}
