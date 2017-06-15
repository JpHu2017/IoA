//
// Created by cvrsg on 17-6-15.
//

#ifndef REDBLACKTREE_RBTREE_H
#define REDBLACKTREE_RBTREE_H

#include <iostream>

enum Color{red, black};
//Red-Black Tree Node
class RBTreeNode
{
public:
    //Constructor
    RBTreeNode(Color clr)
            :p(NULL), left(NULL), right(NULL), color(clr) {}
    //member
    int key;
    double satellite_data;
    Color color;
    RBTreeNode *p;
    RBTreeNode *left;
    RBTreeNode *right;
};

class RBTree {
public:
    RBTree() : root(nil) { }

    //function
    void RBTreeInorderWalk(RBTreeNode* x);
    RBTreeNode* RBTreeMinimum(RBTreeNode *x) const;
    RBTreeNode* RBTreeMaximum(RBTreeNode *x) const;
    RBTreeNode* RBTreeSuccessor(RBTreeNode *x) const;
    RBTreeNode* RBTreePredecessor(RBTreeNode *x) const;
    RBTreeNode* RBTreeSearch(RBTreeNode *x, int key) const;
    void RBTreeInsert(RBTreeNode *z);
    void RBTreeDelete(RBTreeNode *z);

    //member
    RBTreeNode *root;
    //必须定义nil，与二叉搜索树不同的是，红黑树的叶结点为nil
    static RBTreeNode *nil;

private:
    //private function
    void RBTreeInsertFixup(RBTreeNode *z);
    void RBTreeTransplant(RBTreeNode* u, RBTreeNode *v);
    void RBTreeDeleteFixup(RBTreeNode *x);
    void LeftRotate(RBTreeNode *x);
    void RightRotate(RBTreeNode *x);
};


#endif //REDBLACKTREE_RBTREE_H
