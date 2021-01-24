//
//  TreeNode.hpp
//  Course_design
//
//  Created by apple on 2021/1/5.
//

#ifndef TreeNode_hpp
#define TreeNode_hpp

#include<iostream>
#include "User.hpp"
class TreeNode{
private:
    User data;//节点的数据内容
    TreeNode* left;//节点左节点
    TreeNode* right;//节点右节点
    int height;//以该节点为根的树的高度
    int floors;//该节点所在的层数，设根节点为第0层
    int balanceFactor;//平衡因子，左子树高度减右子树高度
public:
    TreeNode();//无参构造函数
    TreeNode(User &u);//复制构造函数
    ~TreeNode(){}//析构函数
    TreeNode(TreeNode& Node);//复制构造函数
    friend class AVLTree;//将AVLTree声明为友元类，使得可以访问TreeNode的成员
};

#endif /* TreeNode_hpp */
