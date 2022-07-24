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

// Insersion function
void insertToTree(TreeNode* root, TreeNode* NewNode)
{
    // Left branch actions
    if (NewNode->element <= root->element)
    {
        if (root->left == NULL)
        {
            root->left = NewNode;
        }
        else
        {
            insertToTree(root->left, NewNode);
        }
    }

    // Right branch actions
    else if (NewNode->element > root->element)
    {
        if (root->right == NULL)
        {
            root->right = NewNode;
        }
        else
        {
            insertToTree(root->right, NewNode);
        }
    }
}

// Inorder traversal function for printing
void IOF(TreeNode* root)
{
    // Ending condition
    if (root == NULL)
    {
        return;
    }

    // Progression
    IOF(root->left);
    printf("%d  " , root->element);
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

    // Progression
    POF(root->left);
    POF(root->right);
    free(root);
}

// Reversed in order function for searching
void RIO(TreeNode* root, int* N, int* V)
{
    // Ending condition
    if (root == NULL)
    {
        return;
    }

    // Progression
    RIO(root->right, N, V);
    (*N)--;
    // Final touch
    if (*N == 0)
    {
        *V = root->element;
    }
    RIO(root->left, N, V);

    
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

    // Progression
    if (getHeight(root->left) != getHeight(root->right))
    {
        *check = 0;
        return;
    }
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
    // Further insersion actions
    else
    {
        insertToTree(bst->root, NewNode);
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
    printf("Elements in order: ");
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
        return -1;
    }

    // Case [2/2]: Unempty tree
    int V = 0;
    RIO(bst->root, &N, &V);
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