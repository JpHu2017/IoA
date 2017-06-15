#include <iostream>
#include <vector>
#include "BinarySearchTree.h"

using namespace std;

int main() {
    vector<int> keys = {2,3,7,1,3,5,6,4};
    BinarySearchTree *BST;
    BST= new BinarySearchTree;
    //Build a binary search tree
    for(int i=0; i<keys.size(); ++i)
    {
        BinaryTreeNode *x = new BinaryTreeNode;
        x->key = keys[i];
        x->satellite_data = 0; // not considered in here
        BST->TreeInsert(BST->Root, x);
    }
    BinaryTreeNode *q;
    int key = 3;
    q = BST->TreeSearch(BST->Root, key);
    cout << "Search Elem is Right or Wrong? " << (q->key==key?"Right":"Wrong") << endl;
    cout << "Minimum elem: " << BST->TreeMinimum(BST->Root)->key << endl;
    cout << "Maximum elem: " << BST->TreeMaximum(BST->Root)->key << endl;
    cout << "Predecessor of " << q->key << ": " << BST->TreePredecessor(q)->key << endl;
    cout << "Successor of " << q->key << ": " << BST->TreeSuccessor(q)->key << endl;
    BinaryTreeNode *x = new BinaryTreeNode;
    x->key = 8;
    BST->TreeInsert(BST->Root, x);
    cout << "Insert elem " << x->key << " :" << endl;
    BST->InorderTreeWalk(BST->Root);
    BST->TreeDelete(BST->Root,q);
    cout << "Delete elem " << q->key << " :" << endl;
    BST->InorderTreeWalk(BST->Root);
    return 0;
}