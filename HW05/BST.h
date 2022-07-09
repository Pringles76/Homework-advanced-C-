#ifndef _BST_ADT_H
#define _BST_ADT_H

typedef struct TreeNode TreeNode;

struct TreeNode
{
    TreeNode* left;
    TreeNode* right;
    int element;
};

typedef struct BST
{
    TreeNode* root;
}BST;

#endif // !_BST_ADT_H

// *** Personal Functions *** //
int isEmptyTree(BST* bst);
void IOF(TreeNode* root);
void POF(TreeNode* root);
void RIO(TreeNode* root, int N, int* V);

int maximum(int L, int R);
void sameH(TreeNode* root, int* check);
int getHeight(TreeNode* root);

// *** Assignment Functions *** //
void initBST(BST* bst);
void insertBST(BST* bst, int value);
void printTreeInorder(BST* bst);
void destroyBST(BST* bst);
int findIndexNFromLast(BST* bst, int N);
int sameHeightLeaves(BST* bst);