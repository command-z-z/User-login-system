//
//  AVLTree.hpp
//  Course_design
//
//  Created by apple on 2021/1/5.
//

#ifndef AVLTree_hpp
#define AVLTree_hpp

#include <iostream>
#include <string>
#include <fstream>
#include "User.hpp"
#include "TreeNode.hpp"
using namespace std;
class AVLTree{
private:
    TreeNode* treeRoot;//根节点定义
    //以下函数只是些公共函数的辅助函数，因此写在私有类下
    void release(TreeNode *subtreeNode);//析构函数的辅助函数，用于节点释放
    void copyAux(TreeNode* leftRoot,TreeNode* rightRoot);//复制构造函数的辅助函数
    void inorderAux(ostream& out,TreeNode*subtreeRoot);//辅助中序遍历输出函数
    void LRotate(TreeNode *parent,TreeNode* subtree);//简单左旋
    void RRotate(TreeNode *parent,TreeNode* subtree);//简单右旋
    void LRRotate(TreeNode* parent,TreeNode* subtree);//左右旋
    void RLRotate(TreeNode* parent,TreeNode* subtree);//右左旋
    void findDeepest2NodeAux(TreeNode *&deepest2Node,TreeNode *&parent,TreeNode *subtreeNode);//寻找后序后平衡因子为+-2的节点的辅助函数
    void refreshBothImformationAux(int &subheight,int subfloor,TreeNode* subtreeNode);//用于更新树中的内容的辅助函数，树高，树的层数，树的平衡因子
    void balanceAux(TreeNode* deepest2Node,TreeNode* parent);//用于平衡二叉树的辅助函数
    void graphAux(ostream& out,int indent,TreeNode *subtreeRoot);//用于输出函数的辅助
public:
    AVLTree(); //AVLTree 类的默认构造函数
    AVLTree(AVLTree &rightTree);//AVLTree 类的复制构造函数
    ~AVLTree(); //AVLTree 类的析构函数
    AVLTree &operator=(AVLTree &rightTree);//AVLTree类的赋值重载
    void search(const string& name,bool& found,TreeNode* &locptr,TreeNode* &parent);//搜索函数，用来查找用户是否存在,found是标识，locptr为当前节点，parent为父节点
    User* search(const string &name);//函数重载，通过用户名进行查找，如果用户不存在则返回NULL，用于注册用户时使用
    User* match(string name,string passWord);//查找用户，在用户登入时用
    void load(string File); //将文件中的用户信息读入
    void save(string file);//保存到文件
    bool insert(User user);//插入用户信息形成AVL树(其中有四种平衡操作)
    bool remove(const string &name);//根据用户名删除用户
    void LVR(ostream& out);//中序遍历
    bool findDeep2Node(TreeNode *&deepest2Node,TreeNode *&parent);//用于后序后平衡因子为+-2的节点，第一个参数为平衡因子为+-2的节点，第二个参数为该节点的父节点
    void refreshBothImformation();//插入后，用于刷新树中的内容，树的高度，树的层数，树的平衡因子
    void balance();//用于二叉树的平衡
    void graph(ostream& out);//用于图形输出
    void graph(string file);
    void test(TreeNode *subtreeRoot);//测试中序代码辅助
    void test1();//测试中序代码
};

#endif /* AVLTree_hpp */
