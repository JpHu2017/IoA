#include <iostream>
#include <vector>
#include "RBTree.h"

using namespace std;



int main() {
    vector<int> keys = {41, 38, 31, 12, 19, 8};
    RBTree* rbt = new RBTree;
    for(int i=0; i<keys.size(); ++i)
    {
        RBTreeNode* x = new RBTreeNode(red);
        x->key = keys[i];
        rbt->RBTreeInsert(x);
    }
    cout << "The Tree is:" << endl;
    rbt->RBTreeInorderWalk(rbt->root);
    cout<< endl;
    cout << "The Maximum key is " << rbt->RBTreeMaximum(rbt->root)->key << endl;
    cout << "The Minimum key is " << rbt->RBTreeMinimum(rbt->root)->key << endl;
    int find_key = 38;
    RBTreeNode* y = rbt->RBTreeSearch(rbt->root, find_key);
    string find_flag = (y!=rbt->nil)?"Yes":"No";
    cout << "Whether the key " << find_key << "in the RB Tree? " << "Yes/No >> " <<
            find_flag << endl;
    cout << "The key " << find_key << "'s predecessor is " << rbt->RBTreePredecessor(y)->key << endl;
    cout << "The key " << find_key << "'s successor is " << rbt->RBTreeSuccessor(y)->key << endl;
    rbt->RBTreeDelete(y);
    cout << "Delete the key " << find_key << ", the tree is:"<< endl;
    rbt->RBTreeInorderWalk(rbt->root);
    cout<< endl;
    return 0;
}