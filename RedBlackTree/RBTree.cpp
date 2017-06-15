//
// Created by cvrsg on 17-6-15.
//

#include "RBTree.h"
#include <glog/logging.h>
using namespace std;

RBTreeNode* RBTree::nil = new RBTreeNode(black);

void RBTree::RBTreeInorderWalk(RBTreeNode* x)
{
    if(x!=nil)
    {
        RBTreeInorderWalk(x->left);
        cout << x->key << ", ";
        RBTreeInorderWalk(x->right);
    }
}
//获取以结点x为根的子树上的关键字最小的结点
//const的作用：说明其不会修改数据成员
RBTreeNode* RBTree::RBTreeMinimum(RBTreeNode *x) const
{
    if(x==nil)
    {
        return x;
    }
    else
    {
        while(x->left!=nil)
        {
            x = x->left;
        }
        return x;
    }
}
RBTreeNode* RBTree::RBTreeMaximum(RBTreeNode *x) const
{
    if(x==nil)
    {
        return x;
    }
    else
    {
        while(x->right!=nil)
        {
            x = x->right;
        }
        return x;
    }
}
//后继
RBTreeNode* RBTree::RBTreeSuccessor(RBTreeNode *x) const
{
    /*//原始代码
    if(x==nil)
    {
        return x;
    }
    else
    {
        //情况1:结点x有右子树
        if(x->right!=nil)
        {
            return RBTreeMinimum(x->right);
        }
        else if(x->p!=nil)
        {
            //情况2:结点x无右子树，且结点x是其父结点的左孩子
            if(x->p->left == x)
            {
                return x->p;
            }
            else
            {
                //情况3:结点x无右子树，且结点x是其父结点的右孩子
                while(x->p!=nil && x->p->right==x)
                {
                    x = x->p;
                }
                return x->p;
            }
        }
        else
        {
            return x->p;
        }
    }*/
    //精简代码
    if(x==nil)
    {
        return x;
    }
    else
    {
        if(x->right!=nil)
        {
            return RBTreeMinimum(x->right);
        }
        else
        {
            while(x->p!=nil && x->p->right==x)
            {
                x = x->p;
            }
            return x->p;
        }
    }
}
//前驱
RBTreeNode* RBTree::RBTreePredecessor(RBTreeNode *x) const
{
    if(x==nil)
    {
        return x;
    }
    else
    {
        if(x->left!=nil)
        {
            return RBTreeMaximum(x->left);
        }
        else
        {
            while(x->p!=nil && x->p->left==x)
            {
                x = x->p;
            }
            return x->p;
        }
    }
}
//查找
RBTreeNode* RBTree::RBTreeSearch(RBTreeNode *x, int key) const
{
    /*//原始代码
    if(x==NULL)
    {
        return x;
    }
    else
    {
        if(x->key==key)
        {
            return x;
        }
        else if(x->key<key)
        {
            return RBTreeSearch(x->left, key);
        }
        else
        {
            return RBTreeSearch(x->right, key);
        }
    }*/
    //精简代码
    if(x==nil || key==x->key)
    {
        return x;
    }
    else if(key<x->key)
    {
        return RBTreeSearch(x->left, key);
    }
    else
    {
        return RBTreeSearch(x->right, key);
    }
}
//在以root为根的红黑树上，插入元素z
void RBTree::RBTreeInsert(RBTreeNode *z)
{
    //原始代码
    /*RBTreeNode *s = root;
    RBTreeNode *t = nil;
    if(s==nil)
    {
        root = z;
    }
    else
    {
        while(s!=nil)
        {
            t = s;
            if(z->key<=s->key)
            {
                s = s->left;
            }
            else
            {
                s = s->right;
            }
        }
        if(s->p==nil)
        {
            if(z->key<=s->key)
                root->left = z;
            else
                root->right = z;
            z->p = s;
        }
        else
        {
            if(z->key <= t->key)
                t->left = z;
            else
                t->right = z;
            z->p = t;
        }
    }*/
    //精简代码
    RBTreeNode *s = root;
    RBTreeNode *t = nil;
    while(s!=nil)
    {
        t = s;
        if(z->key<=s->key)
        {
            s = s->left;
        }
        else
        {
            s = s->right;
        }
    }
    if(t==nil)
        root = z;
    else if(z->key<=t->key)
        t->left = z;
    else
        t->right = z;
    z->p = t;
    //修正红黑树
    z->left = nil;
    z->right = nil;
    z->color = red;
    RBTreeInsertFixup(z);
}
void RBTree::RBTreeInsertFixup(RBTreeNode *z)
{
    //如果z->p->color == black，没有破坏红黑树的性质
    //如果z->p->color == red，那么通过循环维护红黑树性质
    //且我们知道，如果z->p->color==red，那么一定存在z->p->p，因为根结点颜色为黑
    //如果z->p==nil,z为根结点，在循环之后修改
    while(z->p!=nil && z->p->color==red)
    {
        //z的父结点为左孩子
        if(z->p==z->p->p->left)
        {
            RBTreeNode* y = z->p->p->right;
            //情况1:x的父结点为红色，且叔结点也为红色
            if(y->color==red)
            {
                z->p->color = black;
                y->color = black;
                z->p->p->color = red;
                z = z->p->p;
            }
                //情况2:x的叔结点为红色，且x为其父结点的右孩子
            else if(y->color==black && z->p->right==z)
            {
                z = z->p;
                LeftRotate(z);
            }
                //情况3:x的叔结点为红色，且x为其父结点的左孩子
            else
            {
                z->p->color = black;
                z->p->p->color = red;
                RightRotate(z->p->p);
            }
        }
        else //z的父结点为右孩子
        {
            RBTreeNode* y = z->p->p->left;
            //情况1:x的父结点为红色，且叔结点也为红色
            if(y->color==red)
            {
                z->p->color = black;
                y->color = black;
                z->p->p->color = red;
                z = z->p->p;
            }
                //情况2:x的叔结点为红色，且x为其父结点的右孩子
            else if(y->color==black && z->p->left==z)
            {
                z = z->p;
                RightRotate(z);
            }
                //情况3:x的叔结点为红色，且x为其父结点的左孩子
            else
            {
                z->p->color = black;
                z->p->p->color = red;
                LeftRotate(z->p->p);
            }
        }
    }
    root->color = black;
}
//在以root为根的红黑树上，删除元素z
void RBTree::RBTreeDelete(RBTreeNode *z)
{
    if(z==nil)
    {
        LOG(ERROR) << "You can't delete a nil node!" << endl;
    }
    RBTreeNode* y = z;
    RBTreeNode* x;
    Color y_original_color = y->color;

    if(z->left==nil)
    {
        x = z->right;
        RBTreeTransplant(z,z->right);
    }
    else if(z->right==nil)
    {
        x = z->left;
        RBTreeTransplant(z,z->left);
    }
        //有2个孩子
    else
    {
        //首先寻找z的后继，删除后，替换z的应该是z的后继
        y = RBTreeSuccessor(z);
        y_original_color = y->color;
        x = y->right;
        if(z->right==y)
        {
            x->p = y;
        }
        else
        {
            RBTreeTransplant(y,y->right);
            y->right = z->right;
            y->right->p = y; //也可以写成 z->right->p = y;更新是成对
        }
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
        RBTreeTransplant(z,y);
    }
    if(y_original_color==black)
        RBTreeDeleteFixup(x);
}
//替换：这里假设u不为空结点，若u为空结点，也无法进行替换工作
void RBTree::RBTreeTransplant(RBTreeNode* u, RBTreeNode *v)
{
    if(u==nil)
    {
        LOG(ERROR) << "ERROR: u can't be a nil node!" << endl;
    }
    if(u->p==nil)
    {
        root = v;
    }
    else
    {
        if(u->p->left==u)
        {
            u->p->left = v;
        }
        else if(u->p->right==u)
        {
            u->p->right = v;
        }
    }
    v->p = u->p;  //为什么可以不加v!=nil的判断条件；书中解释为即使v=nil，同样可以对v赋值。有没有更具体的作用
}
void RBTree::RBTreeDeleteFixup(RBTreeNode *x)
{
    while(x!=root && x->color==black)
    {
        //x为左孩子
        if(x==x->p->left)
        {
            RBTreeNode* w = x->p->right;
            //情况1:x的兄弟结点w的颜色为红色，则它们的父结点一定为黑色
            //左旋，将情况1转为情况2,3,4(即x的兄弟结点w为黑色）
            //因为w为红色，则w->left为黑色，左旋之后其成为x的兄弟结点
            if(w->color==red)
            {
                x->p->color = red;
                w->color = black;
                LeftRotate(x->p);
                w = x->p->right; //更新w结点
            }
            //情况2:w的左右子结点都为黑色，直接将w的颜色变为红色
            //为了弥补丢失的一重黑色，将x->p置为x
            //这时候，原本的x变成单重黑，而x->p（即转变后的x）变成双重黑
            if(w->left->color==black && w->right->color==black)
            {
                w->color = red;
                x = x->p;
            }
                //情况3:当w的左子结点为红色，而右子结点为黑色
                //围绕w右旋，并相应设置颜色，以保证不违反性质5
            else if(w->right->color==black)
            {
                w->left->color = black;
                w->color = red;
                RightRotate(w);
            }
                //情况4:w的右子结点为红色，左旋，依次修改w,x->p,w->right的颜色
                //去除x的双重颜色，并保证性质不变
            else
            {
                w->color = x->p->color;
                x->p->color = black;
                w->right->color = black;
                LeftRotate(x->p);
                x = root;
            }
        }
        else //x为右孩子
        {
            //和左孩子情况正好相反
            RBTreeNode* w = x->p->left;
            //情况1:x的兄弟结点w的颜色为红色，则它们的父结点一定为黑色
            //左旋，将情况1转为情况2,3,4(即x的兄弟结点w为黑色）
            //因为w为红色，则w->left为黑色，左旋之后其成为x的兄弟结点
            if(w->color==red)
            {
                x->p->color = red;
                w->color = black;
                RightRotate(x->p);
                w = x->p->left; //更新w结点
            }
            //情况2:w的左右子结点都为黑色，直接将w的颜色变为红色
            //为了弥补丢失的一重黑色，将x->p置为x
            //这时候，原本的x变成单重黑，而x->p（即转变后的x）变成双重黑
            if(w->left->color==black && w->right->color==black)
            {
                w->color = red;
                x = x->p;
            }
                //情况3:当w的左子结点为红色，而右子结点为黑色
                //围绕w右旋，并相应设置颜色，以保证不违反性质5
            else if(w->left->color==black)
            {
                w->right->color = black;
                w->color = red;
                LeftRotate(w);
            }
                //情况4:w的右子结点为红色，左旋，依次修改w,x->p,w->right的颜色
                //去除x的双重颜色，并保证性质不变
            else
            {
                w->color = x->p->color;
                x->p->color = black;
                w->left->color = black;
                RightRotate(x->p);
                x = root;
            }
        }
    }
    x->color = black;
}
//插入，删除操作的辅助函数：旋转
//能完成左旋，则需要x->right不为NULL
void RBTree::LeftRotate(RBTreeNode *x)
{
    if(x->right==nil)
    {
        LOG(ERROR) << "x->right can't be a nil node!" << endl;
    }
    RBTreeNode* y = x->right;
    //移动beta（y的左子树），建立x与beta之间的关系
    x->right = y->left;
    if(y->left!=nil)
    {
        y->left->p = x;
    }
    //建立x->p与y之间的关系
    if(x->p == nil)
    {
        root = y;
    }
    else if(x->p->left==x)
    {
        x->p->left = y;
    }
    else
    {
        x->p->right = y;
    }
    y->p = x->p;
    //重新建立x与y之间的关系
    y->left = x;
    x->p = y;
}
//右旋
void RBTree::RightRotate(RBTreeNode *x)
{
    if(x->left==nil)
    {
        LOG(ERROR) << "x->left can't be a nil node!" << endl;
    }
    RBTreeNode* y = x->left;
    //
    x->left = y->right;
    if(y->right!=nil)
    {
        x->right->p = y;
    }
    //
    if(x->p==nil)
    {
        root = y;
    }
    else if(x->p->left==x)
    {
        x->p->left = y;
    }
    else
    {
        x->p->right = y;
    }
    y->p = x->p;
    //
    y->right = x;
    x->p = y;
}

