#include <stdio.h>
#include  <stdlib.h>
#include "RBTree.h"

#define LESS (-1)
#define EQUAL (0)
#define GREATER (1)
#define FAIL (0)
#define SUCCESS (1)

void caseOneDelete(RBTree *tree, Node *M, Node *S, Node *P);

void fixTreeAfterInsert(RBTree *tree, Node *toAdd);

/**
 * constructs a new RBTree with the given CompareFunc.
 * comp: a function two compare two variables.
 */
RBTree *newRBTree(CompareFunc compFunc, FreeFunc freeFunc)
{
    RBTree *rBTree = NULL;
    rBTree = (RBTree *) malloc(sizeof(RBTree));
    if (rBTree != NULL)
    {
        rBTree->compFunc = compFunc;
        rBTree->freeFunc = freeFunc;
        rBTree->size = 0;
        rBTree->root = NULL;
        return rBTree;
    }
    else
    {
        return NULL;
    }
}

/**
 * This function preform right rotation.
 * @param tree The tree.
 * @param rotateOn the node to preform the rotation on.
 */
void rotateRight(RBTree *tree, Node *rotateOn)
{
    Node *temp = rotateOn->left;
    rotateOn->left = temp->right;

    if (temp == NULL)
    { return; }
    if (temp->right != NULL)
    {
        temp->right->parent = rotateOn;
    }
    temp->parent = rotateOn->parent;
    if (rotateOn->parent == NULL)
    {
        tree->root = &(*temp);
    }
    else
    {
        if (rotateOn == rotateOn->parent->right)
        {
            rotateOn->parent->right = &(*temp);
        }
        else
        {
            rotateOn->parent->left = &(*temp);
        }
    }
    temp->right = rotateOn;
    rotateOn->parent = temp;
}

/**
 * This function preform left rotation.
 * @param tree The tree.
 * @param rotateOn the node to preform the rotation on.
 */
void rotateLeft(RBTree *tree, Node *rotateOn)
{
    Node *temp = rotateOn->right;
    rotateOn->right = temp->left;
    if (temp == NULL)
    { return; }
    if (temp->left != NULL)
    {
        temp->left->parent = rotateOn;
    }
    temp->parent = rotateOn->parent;
    if (rotateOn->parent == NULL)
    {
        tree->root = &(*temp);
    }
    else
    {
        if (rotateOn == rotateOn->parent->left)
        {
            rotateOn->parent->left = &(*temp);
        }
        else
        {
            rotateOn->parent->right = &(*temp);
        }
    }
    temp->left = rotateOn;
    rotateOn->parent = &(*temp);
}

/**
 * This function find the parent of a given node.
 * @param M node to find his parent.
 * @return the node parent if exist, null otherwise.
 */
Node *findParent(Node *M)
{
    if (M == NULL)
    { return NULL; }
    if (M->parent != NULL)
    {
        return M->parent;
    }
    return NULL;
}

/**
 * This function find the brother of a given node.
 * @param M node to find his brother.
 * @return the node brother if exist, null otherwise.
 */
Node *findBrother(Node *M)
{
    Node *P = findParent(M);
    if (P == NULL)
    {
        return NULL;
    }
    if (M == P->left)
    {
        return P->right;
    }
    return P->left;
}

/**
 * This function find the brother of a given node.
 * @param M node to find his brother.
 * @param parent the node parent.
 * @return the node brother if exist, null otherwise.
 */
Node *findNewBrother(Node *M, Node *parent)
{
    if (M == parent->left)
    {
        return parent->right;
    }
    return parent->left;
}

/**
 * This function find the grandparent of a given node.
 * @param M node to find his grandparent.
 * @return the node grandparent if exist, null otherwise.
 */
Node *findGrandP(Node *M)
{
    return findParent(findParent(M));
}

/**
 * This function find the uncle of a given node.
 * @param M node to find his uncle.
 * @return the node uncle if exist, null otherwise.
 */
Node *findUncle(Node *M)
{
    Node *P = findParent(M);
    return (findBrother(P));
}

/**
 * The color of the uncle of the node we added is black.
 * @param tree the tree
 * @param M the node that added.
 */
void caseFourTwoInsert(RBTree *tree, Node *M)
{
    Node *grandP = findGrandP(M);
    Node *P = findParent(M);

    if (M == P->left)
    {
        rotateRight(tree, grandP);
    }
    else
    {
        rotateLeft(tree, grandP);
    }
    P->color = BLACK;
    grandP->color = RED;
}

/**
 * The color of the uncle of the node we added is black.
 * @param tree the tree
 * @param M the node that added.
 */
void caseFourInsert(RBTree *tree, Node *M)
{
    Node *grandP = findGrandP(M);
    Node *P = findParent(M);

    if (M == P->right && P == grandP->left)
    {
        rotateLeft(tree, P);
        M = M->left;
    }
    else if (M == P->left && P == grandP->right)
    {
        rotateRight(tree, P);
        M = M->right;
    }
    caseFourTwoInsert(tree, M);
}

/**
 * The color of the uncle of the node we added is red.
 * @param tree the tree
 * @param M the node that added.
 */
void caseThreeInsert(RBTree *tree, Node *M)
{
    Node *uncle;
    Node *grandP;

    M->parent->color = BLACK;
    if (M->parent == M->parent->parent->left)
    {
        uncle = M->parent->parent->right;
    }
    else
    {
        uncle = M->parent->parent->left;
    }
    if (uncle != NULL)
    {
        uncle->color = BLACK;
    }
    grandP = M->parent->parent;
    grandP->color = RED;
    fixTreeAfterInsert(tree, grandP);
}

/**
 * the node that added is the root.
 * @param tree the tree.
 * @param M the node that added.
 */
void caseOneInsert(Node *M)
{
    M->color = BLACK;
}

/**
 * This function fix the tree after inserting node.
 * @param tree the tree.
 * @param toAdd the node that added.
 */
void fixTreeAfterInsert(RBTree *tree, Node *toAdd)
{
    Node *grandP = findGrandP(toAdd);
    Node *P = findParent(toAdd);
    Node *uncle = findUncle(toAdd);
    if (P == NULL)
    {
        uncle = NULL;
        caseOneInsert(toAdd);
    }

    else if (P->color == BLACK)
    {
        return;
    }
    else if (grandP != NULL && uncle != NULL && uncle->color == RED)
    {
        caseThreeInsert(tree, toAdd);
    }
    else
    {
        caseFourInsert(tree, toAdd);
    }
}

/**
 * add an item to the tree
 * @param tree: the tree to add an item to.
 * @param data: item to add to the tree.
 * @return: 0 on failure, other on success. (if the item is already in the tree - failure).
 */
int insertToRBTree(RBTree *tree, void *data)
{
    if (tree == NULL || data == NULL)
    {
        return FAIL;
    }
    if (RBTreeContains(tree, data) != EQUAL)
    {
        return FAIL;
    }
    Node *toAdd = NULL;
    toAdd = (Node *) malloc(sizeof(Node));
    if (toAdd == NULL)
    {
        return FAIL;
    }
    toAdd->data = data;
    Node *x = tree->root;
    Node *temp = NULL;

    while (x != NULL)
    {
        temp = x;
        if (tree->compFunc(toAdd->data, x->data) < 0)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    toAdd->parent = temp;
    toAdd->right = NULL;
    toAdd->left = NULL;

    if (temp == NULL)
    {
        tree->root = toAdd;
        toAdd->color = BLACK;
        tree->size++;
        return SUCCESS;
    }
    else
    {
        toAdd->color = RED;
        if (tree->compFunc(toAdd->data, temp->data) < 0)
        {
            temp->left = toAdd;
        }
        else
        {
            temp->right = toAdd;
        }
    }
    fixTreeAfterInsert(tree, toAdd);
    tree->size++;
    return SUCCESS;
}

/**
 * This function finds the node that hold a given data.
 * @param tree the tree.
 * @param data of the needed node.
 * @return the node that hold data.
 */
Node *findNodeToDelete(RBTree *tree, void *data)
{
    Node *helper = tree->root;
    while (helper != NULL)
    {
        if (tree->compFunc(helper->data, data) == EQUAL)
        {
            return helper;
        }
        if (tree->compFunc(helper->data, data) < EQUAL)
        {
            helper = helper->right;
        }
        else
        {
            helper = helper->left;
        }
    }
    return NULL;
}

/**
 * function that find the successor node of given node.
 * @param currNode given node.
 * @return The successor node.
 */
Node *findSuccessorNode(Node *currNode)
{
    while (currNode->left != NULL)
    {
        currNode = currNode->left;
    }
    return currNode;
}

/**
 * union the parent of a and b so a deleted.
 * @param tree the tree.
 * @param a node to delete.
 * @param b where to connect.
 */
void unionNodes(RBTree *tree, Node *a, Node *b)
{
    if (a->parent == NULL)
    {
        tree->root = b;
    }
    else
    {
        if (a == a->parent->left)
        {
            a->parent->left = b;
        }
        else
        {
            a->parent->right = b;
        }
    }
    if (b != NULL)
    {
        b->parent = a->parent;
    }
    free(a);
    a = NULL;
}

/**
 * remove an item from the tree
 * @param tree: the tree to remove an item from.
 * @param data: item to remove from the tree.
 * @return: 0 on failure, other on success. (if data is not in the tree - failure).
 */
int deleteFromRBTree(RBTree *tree, void *data)
{
    if (tree == NULL)
    {
        return FAIL;
    }
    if (RBTreeContains(tree, data) == EQUAL)
    {
        return FAIL;
    }
    Node *M = findNodeToDelete(tree, data);
    Node *successor;
    Color mColor = M->color;
    Node *child = NULL;
    if (M->right != NULL && M->left != NULL)
    {
        successor = findSuccessorNode(M->right);
        void *tempD = (M)->data;
        (M)->data = successor->data;
        successor->data = tempD;
        M = successor;
        mColor = successor->color;
        child = M->right;
    }
    else if (M->right != NULL)
    {
        mColor = M->right->color;
        void *tempDa = (M)->data;
        (M)->data = M->right->data;
        M->right->data = tempDa;
        M = M->right;
        child = M->right;
    }
    else if (M->left != NULL)
    {
        child = M->left;
        mColor = child->color;
        void *tempData = (M)->data;
        (M)->data = M->left->data;
        M->left->data = tempData;
        M = M->left;
        child = M->right;
    }

    if (M == NULL)
    {
        return FAIL;
    }

    Node *S = findBrother(M);
    Node *P = findParent(M);
    unionNodes(tree, M, child);
    if (mColor == BLACK)
    {
        if (child == NULL)
        {
            caseOneDelete(tree, child, S, P);
        }
        else if (child->color == RED)
        {
            child->color = BLACK;
        }
        else
        {
            caseOneDelete(tree, child, S, P);
        }
    }
    tree->freeFunc(data);
    tree->size--;
    return SUCCESS;
}

/**
 * check whether the tree RBTreeContains this item.
 * @param tree: the tree to add an item to.
 * @param data: item to check.
 * @return: 0 if the item is not in the tree, other if it is.
 */
int RBTreeContains(const RBTree *tree, const void *data)
{
    Node *temp;
    if (tree == NULL || data == NULL || tree->root == NULL)
    {
        return FAIL;
    }
    temp = tree->root;
    while (temp != NULL)
    {
        if (tree->compFunc(temp->data, data) == EQUAL)
        {
            return SUCCESS;
        }
        else if (tree->compFunc(data, temp->data) < EQUAL)
        {
            temp = temp->left;
        }
        else
        {
            temp = temp->right;
        }
    }
    return FAIL;
}

/**
 * Delete node from tree if sibling is black, sibling sons one black and one red.
 * @param tree the tree.
 * @param M node to delete.
 * @param S sibling of the node to delete.
 * @param P parent of the node to delete.
 */
void caseSixDelete(RBTree *tree, Node *M, Node *S, Node *P)
{
    if (S)
    {
        S->color = P->color;
    }
    P->color = BLACK;

    if (M == (P->left ? P->left : NULL))
    {
        if (S)
        {
            if (S->right)
            {
                S->right->color = BLACK;
            }
        }
        rotateLeft(tree, P);
    }
    else
    {
        if (S)
        {
            if (S->left)
            {
                S->left->color = BLACK;
            }
        }

        rotateRight(tree, P);
    }
}

/**
 * Delete node from tree if sibling is black, sibling sons one black and one red.
 * @param tree the tree.
 * @param M node to delete.
 * @param S sibling of the node to delete.
 * @param P parent of the node to delete.
 */
void caseFiveDelete(RBTree *tree, Node *M, Node *S, Node *P)
{
    if ((S ? S->color : BLACK) == BLACK)
    {
        if ((M == (P->left ? P->left : NULL)) &&
            ((S ? (S->right ? S->right->color : BLACK) : BLACK) == BLACK) &&
            ((S ? (S->left ? S->left->color : BLACK) : BLACK) == RED))
        {
            if (S)
            {
                S->color = RED;
                if (S->left)
                {
                    S->left->color = BLACK;
                }
            }
            rotateRight(tree, S);
        }
        else if ((M == (P->right ? P->right : NULL)) &&
                 ((S ? (S->left ? S->left->color : BLACK) : BLACK) == BLACK) &&
                 (S ? (S->right ? S->right->color : BLACK) : BLACK) == RED)
        {
            S->color = RED;
            S->right->color = BLACK;
            rotateLeft(tree, S);
        }
        S = findNewBrother(M, P);
    }
    caseSixDelete(tree, M, S, P);
}

/**
 * Delete node from tree if is parent is red, sibling is black, sibling sons are  black.
 * @param tree the tree.
 * @param M node to delete.
 * @param S sibling of the node to delete.
 * @param P parent of the node to delete.
 */
void caseFourDelete(RBTree *tree, Node *M, Node *S, Node *P)
{
    if (((P ? P->color : BLACK) == RED) && ((S ? S->color : BLACK) == BLACK) &&
        ((S ? (S->left ? S->left->color : BLACK) : BLACK) == BLACK) &&
        ((S ? (S->right ? S->right->color : BLACK) : BLACK) == BLACK))
    {
        if (S)
        {
            S->color = RED;
        }
        if (P)
        {
            P->color = BLACK;
        }
    }
    else
    {
        caseFiveDelete(tree, M, S, P);
    }
}

/**
 * Delete node from tree if is parent is black, sibling is black, sibling sons are  black.
 * @param tree the tree.
 * @param M node to delete.
 * @param S sibling of the node to delete.
 * @param P parent of the node to delete.
 */
void caseThreeDelete(RBTree *tree, Node *M, Node *S, Node *P)
{
    if (((P ? P->color : BLACK) == BLACK) && ((S ? S->color : BLACK) == BLACK) &&
        ((S ? (S->left ? S->left->color : BLACK) : BLACK) == BLACK) &&
        ((S ? (S->right ? S->right->color : BLACK) : BLACK) == BLACK))
    {
        if (S)
        {
            S->color = RED;
        }
        caseOneDelete(tree, P, findBrother(P), findParent(P));
    }
    else
    {
        caseFourDelete(tree, M, S, P);
    }
}

/**
 * Delete node from tree if is sibling is red.
 * @param tree the tree.
 * @param M node to delete.
 * @param S sibling of the node to delete.
 * @param P parent of the node to delete.
 */
void caseTwoDelete(RBTree *tree, Node *M, Node *S, Node *P)
{
    if (S == NULL)
    {
        caseThreeDelete(tree, M, S, P);
    }
    if (S->color == RED)
    {
        P->color = RED;
        S->color = BLACK;
        if (M == (P ? P->left : NULL))
        {
            rotateLeft(tree, P);

        }
        else
        {
            rotateRight(tree, P);
        }
        S = findNewBrother(M, P);
        caseOneDelete(tree, M, S, P);
    }
    else
    {
        caseThreeDelete(tree, M, S, P);
    }
}

/**
 * Delete node from tree if is parent is null.
 * @param tree the tree.
 * @param M node to delete.
 * @param S sibling of the node to delete.
 * @param P parent of the node to delete.
 */
void caseOneDelete(RBTree *tree, Node *M, Node *S, Node *P)
{
    if (P == NULL)
    {
        return;
    }
    caseTwoDelete(tree, M, S, P);
}

/**
 * Helper fo the forEach function.
 * @param tree tree to go over.
 * @param func function to activate on each node.
 * @param args for the func.
 * @param node start node.
 * @return 0 on failure, 1 on success.
 */
int forEachHelper(const RBTree *tree, forEachFunc func, void *args, Node *node)
{
    if (node == NULL)
    {
        return SUCCESS;
    }
    else
    {
        if (node->left == NULL && node->right == NULL)
        {
            return func(node->data, args);
        }
        else if (node->left != NULL && node->right == NULL)
        {
            return forEachHelper(tree, func, args, node->left) && func(node->data, args);
        }
        else if (node->right != NULL && node->left == NULL)
        {
            return func(node->data, args) && forEachHelper(tree, func, args, node->right);
        }
        else
        {
            return forEachHelper(tree, func, args, node->left) && func(node->data, args) &&
                   forEachHelper(tree, func, args, node->right);
        }
    }
}

/**
 * Activate a function on each item of the tree. the order is an ascending order. if one of the activations of the
 * function returns 0, the process stops.
 * @param tree: the tree with all the items.
 * @param func: the function to activate on all items.
 * @param args: more optional arguments to the function (may be null if the given function support it).
 * @return: 0 on failure, other on success.
 */
int forEachRBTree(const RBTree *tree, forEachFunc func, void *args)
{
    Node *temp;
    if (tree == NULL || func == NULL)
    {
        return FAIL;
    }
    if (tree->root == NULL)
    {
        return SUCCESS;
    }
    temp = tree->root;
    int res = forEachHelper(tree, func, args, temp);
    return res;
}

/**
 * Helper function to free RBTree.
 * @param tree to free.
 * @param node start node.
 */
void freeHelper(RBTree *tree, Node *node)
{
    if (node != NULL)
    {
        if (node->left != NULL)
        {
            freeHelper(tree, node->left);
            tree->freeFunc(node->left->data);
            free(node->left);
            node->left = NULL;
        }
        if (node->right != NULL)
        {
            freeHelper(tree, node->right);
            tree->freeFunc(node->right->data);
            free(node->right);
            node->right = NULL;
        }
    }
    else
    {
        return;
    }
}

/**
 * free all memory of the data structure.
 * @param tree: pointer to the tree to free.
 */
void freeRBTree(RBTree **tree)
{
    if ((*tree) == NULL || tree == NULL)
    {
        return;
    }
    Node *temp = (*tree)->root;
    freeHelper(*tree, temp);
    if ((*tree)->root != NULL)
    {
        (*tree)->freeFunc((*tree)->root->data);
        free((*tree)->root);
    }
    free(*tree);
    tree = NULL;
}