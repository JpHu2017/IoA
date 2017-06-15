//
// Created by cvrsg on 17-6-15.
//

#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_BINARYSEARCHTREE_H

#include <iostream>

class BinaryTreeNode
{
public:
    //注意并不需要为left,right,p分配内存空间，在创建结点时，它会自己分配内存
    //这里left,right,p仅起到连接作用
    BinaryTreeNode()
    {
        left = NULL;
        right = NULL;
        p = NULL;
    }
    //key and satellite data
    int key;
    double satellite_data;
    //pointer
    BinaryTreeNode *left;
    BinaryTreeNode *right;
    BinaryTreeNode *p;

};

class BinarySearchTree
{
public:
    BinarySearchTree(){Root = NULL;}
    //member
    BinaryTreeNode *Root;
    //function
    void InorderTreeWalk(BinaryTreeNode *root) const;
    BinaryTreeNode* TreeMinimum(BinaryTreeNode *root) const;
    BinaryTreeNode* TreeMaximum(BinaryTreeNode *root) const;
    BinaryTreeNode* TreePredecessor(BinaryTreeNode *x) const;
    BinaryTreeNode* TreeSuccessor(BinaryTreeNode *x) const;
    BinaryTreeNode* TreeSearch(BinaryTreeNode *root, int key) const;
    void TreeInsert(BinaryTreeNode* &root, BinaryTreeNode *x);
    void TreeDelete(BinaryTreeNode* &root, BinaryTreeNode *x);

private:
    void Transplant(BinaryTreeNode* &root, BinaryTreeNode *x, BinaryTreeNode *y);
};


#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H
