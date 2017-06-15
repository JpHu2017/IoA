//
// Created by cvrsg on 17-6-15.
//

#include "BinarySearchTree.h"

using namespace std;

void BinarySearchTree::InorderTreeWalk(BinaryTreeNode *root) const
{
    if(root != NULL)
    {
        InorderTreeWalk(root->left);
        cout << root->key << endl;
        InorderTreeWalk(root->right);
    }
}
BinaryTreeNode* BinarySearchTree::TreeMinimum(BinaryTreeNode *root) const
{
    //递归版
//        if(root->left)
//        {
//            return TreeMinimum(root->left);
//        }
//        else
//        {
//            return root;
//        }
    //循环版
    while(root->left)
    {
        root = root->left;
    }
    return root;
}
BinaryTreeNode* BinarySearchTree::TreeMaximum(BinaryTreeNode *root) const
{
    //递归版
//        if(root->right)
//        {
//            return TreeMinimum(root->right);
//        }
//        else
//        {
//            return root;
//        }
    //循环版
    while(root->right)
    {
        root = root->right;
    }
    return root;
}
BinaryTreeNode* BinarySearchTree::TreePredecessor(BinaryTreeNode *x) const
{
    if(x->left)
    {
        return TreeMaximum(x->left);
    }
    else if(!x->p || x==x->p->right)
    {
        return x->p;
    }
    else
    {
        while(!x->p || x==x->p->left)
        {
            x = x->p;
        }
        return x->p;
    }
}
BinaryTreeNode* BinarySearchTree::TreeSuccessor(BinaryTreeNode *x) const
{
    if(x->right)
    {
        return TreeMinimum(x->right);
    }
    else if(!x->p || x==x->p->left)
    {
        return x->p;
    }
    else
    {
        while(!x->p || x==x->p->right)
        {
            x = x->p;
        }
        return x->p;
    }
}
BinaryTreeNode* BinarySearchTree::TreeSearch(BinaryTreeNode *root, int key) const
{
    if(!root || root->key == key) // if root ==NULL or key is equal root.key
    {
        return root;
    }
    else if(key < root->key)
    {
        return TreeSearch(root->left,key);
    }
    else
    {
        return TreeSearch(root->right,key);
    }
}
//必须使用引用，因为这里我们想改变的是指针root，而非指针root指向的对象的值
void BinarySearchTree::TreeInsert(BinaryTreeNode* &root, BinaryTreeNode *x)
{
    BinaryTreeNode *y = root;
    BinaryTreeNode *z = NULL;
    while(y)
    {
        z = y;
        if(x->key <= y->key)
        {
            y = y->left;
        }
        else
        {
            y = y->right;
        }
    }
    x->p = z;
    if(z == NULL)
    {
        root = x;
    }
    else if(x->key <= z->key)
    {
        z->left = x;
    }
    else
    {
        z->right = x;
    }
}
void BinarySearchTree::TreeDelete(BinaryTreeNode* &root, BinaryTreeNode *x)
{
    if(x->left == NULL)
    {
        Transplant(root, x, x->right);
    }
    else if(x->right == NULL)
    {
        Transplant(root, x, x->left);
    }
    else
    {
        BinaryTreeNode *y = TreeSuccessor(x);
        if(y->p!=x)
        {
            Transplant(root, y, y->right);
            y->right = x->right;
            y->right->p = y;
        }
        Transplant(root,x,y);
        y->left = x->left;
        y->left->p = y;
    }
}
//树结点删除的辅助函数
//用y替代x
void BinarySearchTree::Transplant(BinaryTreeNode* &root, BinaryTreeNode *x, BinaryTreeNode *y)
{
    if(x->p == NULL) //root
    {
        root = y;
    }
    else
    {
        if(x == x->p->left)
        {
            x->p->left = y;
        }
        else
        {
            x->p->right = y;
        }
        if(y != NULL)
            y->p = x->p;
    }
}
/*
//错误写法
//树结点删除的辅助函数
//用y替代x
void BinarySearchTree::Transplant(BinaryTreeNode* &root, BinaryTreeNode *x, BinaryTreeNode *y)
{
    if(x->p == NULL) //root
    {
        root = y;
    }
    else
    {
        //错误：由于y可能为nil,有不存在父结点的可能
        //所以这里会报错
        y->p = x->p;
        if(x == x->p->left)
        {
            x->p->left = y;
        }
        else
        {
            x->p->right = y;
        }

    }
}
*/
