//
//  TreeNode.cpp
//  Course_design
//
//  Created by apple on 2021/1/5.
//

#include "TreeNode.hpp"

TreeNode::TreeNode():data(NULL),left(NULL),right(NULL),height(0),floors(0),balanceFactor(0){}//无参构造函数

TreeNode::TreeNode(User& u):data(u),left(NULL),right(NULL),height(0),floors(0),balanceFactor(0){}//构造函数

TreeNode::TreeNode(TreeNode& Node){
    data=Node.data;
    left=Node.left;
    right=Node.right;
    balanceFactor=Node.balanceFactor;
    height=Node.height;
    floors=Node.floors;
}//复制构造函数
