// Standart header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Current assignment header files
#include "BST.h"
#include "TreePrintLibrary.h"

// *************** Macros *************** //

// Memory allocation check macro
#define MCHECK(PTR) do { \
                          if((bst) == (NULL)) { \
                          puts("Error/insertBST/New tree node creation: malloc faliure."); \
                          exit(1); }}while(0)


// *************** Functions (Personal) *************** //

// Function to check if the tree is empty
int isEmptyTree(BST* bst)
{
    if (bst->root == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Inorder traversal function for printing
void IOF(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }

    IOF(root->left);
    printf("%d" , root->element);
    IOF(root->right);
}

// Postorder traversal function for freeing
void POF(TreeNode* root)
{
    // Ending condition
    if (root == NULL)
    {
        return;
    }

    // Function actions
    POF(root->left);
    POF(root->right);
    free(root);
}

// Reversed in order function for searching
void RIO(TreeNode* root, int N, int* V)
{
    // Ending condition 1
    if (root == NULL)
    {
        return;
    }

    // Progression
    RIO(root->right, N, V);
    N--;
    RIO(root->left, N, V);

    // Final touch
    if (N == 1)
    {
        *V = root->element;
    }
}

int maximum(int L, int R)
{
    if (L > R)
    {
        return L;
    }
    else
    {
        return R;
    }
}

int getHeight(TreeNode* root)
{
    // Ending condition
    if (root == NULL)
    {
        return 0;
    }

    // Progression
    return maximum(getHeight(root->right), getHeight(root->left)) + 1;
}

void sameH(TreeNode* root, int* check)
{
    // Ending condition
    if (root == NULL)
    {
        return;
    }

    // Progression 1
    if (getHeight(root->left) != getHeight(root->right))
    {
        *check = 0;
        return;
    }

    // Progression 2
    sameH(root->left, check);
    sameH(root->right, check);
}


// *************** Functions (Assignment) *************** //


void initBST(BST* bst)
{
    // BST initialization
    bst->root = NULL;
}

void insertBST(BST* bst, int value)
{
    // Part [1/2]: New tree node creation
    TreeNode* NewNode = (TreeNode*)malloc(sizeof(TreeNode));
    MCHECK(NewNode);
    NewNode->element = value;
    NewNode->left = NULL;
    NewNode->right = NULL;

    // Part [2/2]: New tree node insertion
    
    // First insersion actions
    if (isEmptyTree(bst) == 1)
    {
        bst->root = NewNode;
        return;
    }

    // Left branch actions
    if (NewNode->element <= bst->root->element)
    {
        if (bst->root->left == NULL)
        {
            bst->root->left = NewNode;
        }
        else
        {
            insertBST(bst->root->left, NewNode);
        }
    }

    // Right branch actions
    if (NewNode->element > bst->root->element)
    {
        if (bst->root->right == NULL)
        {
            bst->root->right = NewNode;
        }
        else
        {
            insertBST(bst->root->right, NewNode);
        }
    }
}

void printTreeInorder(BST* bst)
{
    // Case [1/2]: Empty tree
    if (isEmptyTree(bst) == 1)
    {
        puts("Unable to print th tree because the tree is empty.");
        return;
    }

    // Case [2/2]: Unempty tree
    IOF(bst->root);
    printf("\n\n");
}

void destroyBST(BST* bst)
{
    // Case[1/2]: Empty tree
    if (isEmptyTree(bst) == 1)
    {
        puts("Note: the tree cannot be destroyed because it is already empty.");
        return;
    }

    // Case [2/2]: Unempty tree
    POF(bst->root);
}

int findIndexNFromLast(BST* bst, int N)
{
    // Case[1/2]: Empty tree
    if (isEmptyTree(bst) == 1)
    {
        puts("Cannot search for the index because the tree is empty.");
        return;
    }

    // Case [2/2]: Unempty tree
    int V = 0;
    RIO(bst, N, &V);
    return V;
}

int sameHeightLeaves(BST* bst)
{
    // Case[1/2]: Empty tree
    if (isEmptyTree(bst) == 1)
    {
        puts("Cannot search for the height because the tree is empty.");
        return 0;
    }

    // Case [2/2]: Unempty tree
    int check = 1;
    sameH(bst->root, &check);
    return check;
}