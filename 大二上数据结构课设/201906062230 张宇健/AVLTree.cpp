//
//  AVLTree.cpp
//  Course_design
//
//  Created by apple on 2021/1/5.
//

#include "AVLTree.hpp"

AVLTree::AVLTree(){  //默认构造函数
    treeRoot=0;
}

void AVLTree::release(TreeNode* subtreeNode){//节点释放，用递归实行，析构函数辅助函数
    if(subtreeNode!=NULL)
    {
        release(subtreeNode->left);//先从最左边的节点开始delete节点
        release(subtreeNode->right);
        delete subtreeNode;
    }
}

//类的析构函数
AVLTree::~AVLTree(){
    release(treeRoot);
}

//复制构造函数的辅助函数,使用递归进行复制
void AVLTree::copyAux(TreeNode *leftRoot , TreeNode *rightRoot){
    if(rightRoot!=NULL){
        leftRoot=new TreeNode(*rightRoot);//调用TreeNode的复制构造函数
        copyAux(leftRoot->left, rightRoot->left);
        copyAux(leftRoot->right, rightRoot->right);
    }
}

//复制构造函数
AVLTree::AVLTree(AVLTree& rightTree){
    copyAux(treeRoot, rightTree.treeRoot);
}
AVLTree& AVLTree::operator=(AVLTree &rightTree){//赋值重载函数
    if(this!=&rightTree)
    {
        release(treeRoot);
        copyAux(treeRoot, rightTree.treeRoot);
    }
    return *this;
}

//查找用户是否已经存在
void AVLTree::search(const string &name,bool &found,TreeNode *&locptr,TreeNode *&parent)
{//节点用引用使得执行这个函数后，可以使得节点指向所找到的节点
    found=false;
    locptr=treeRoot;//当前节点为根节点
    parent=NULL;//根节点的父节点为空
    while (!found && locptr!=NULL) {//循环查找节点用户名是否匹配，由于AVL是BST，二分后便于查找到
        if(((locptr->data).getName())>name){
            parent=locptr;
            locptr=parent->left;
        }
        else if(((locptr->data).getName())<name){
            parent=locptr;
            locptr=parent->right;
        }
        else if(((locptr->data).getName())==name)
        {
            found=true;    //true表示找到了用户
            break;
        }
    }
}


//用户查询，在用户注册时使用
User* AVLTree::search(const string &name){
    bool found=false;
    TreeNode* locptr=NULL,*parent=NULL;
    search(name, found, locptr, parent);//由于形参用了引用相应节点的值会改变
    if(found && locptr!=NULL)
    {
        return &(locptr->data);
    }
    else
        return NULL;
}

//在用户登入时使用，匹配是否用户名没有或密码错误
User* AVLTree::match(string name,string passWord){
    User* user=search(name);
    if(user==NULL)
    {
        cout<<"*******************************\n";
        cout<<"*         用户名不存在！      *\n";
        cout<<"*******************************\n";
        return NULL;
    }
    if(user!=NULL && (user->getName())==name &&user->getPassword()!=passWord){
        cout<<"*******************************\n";
        cout<<"*         输入密码错误        *\n";
        cout<<"*******************************\n";
        return NULL;
    }
    if(user!=NULL && (user->getName())==name &&(user->getPassword()==passWord))
    {
        cout<<"*******************************\n";
        cout<<"*         登入成功!          *\n";
        cout<<"*******************************\n";
        return user;
    }
    return NULL;
}

//将文件中读入用户信息
void AVLTree::load(string file){
    ifstream infile(file,ios::in);
    User user;
    if(!infile){
        cerr<<"文件无法打开"<<endl;
        exit(1);
    }
    else{
        while(infile>>user)//在User中有重载>>运算符，便于读入操作
        {
            try{
                insert(user);
            }
            catch(out_of_range){
                //异常时的操作
            }
        }
    }
    infile.close();
}

void AVLTree::save(string file){
    ofstream outfile(file,ios::trunc);
    if(!outfile)
    {
        cerr<<"文件无法打开"<<endl;
        exit(1);
    }
    else{
        LVR(outfile);//中序输出
    }
    outfile.close();
}

//将用户信息插入AVL树中（四种平衡操作）
bool AVLTree::insert(User user){
    bool found=false;
    TreeNode *locptr=NULL,*parent=NULL;//定义两个节点
    search(user.getName(),found,locptr,parent);//通过search方法来查找user用户是否已经存在
    if(found){//说明节点中已经有这个用户名
        cout<<"*******************************\n";
        cout<<"*         用户名已存在！         *\n";
        cout<<"*******************************\n";
        return false;
    }
    if(!found){//说明节点中原本没这个用户名
        locptr=new TreeNode(user);//创建新的节点，有些参数为user的构造函数
        if(parent==NULL)//即没有根节点的时候
        {
            treeRoot=locptr;
        }
        else if (user.getName()>parent->data.getName()){//由于要满足BST性质判断插入位置,大的插入在右边
            parent->right=locptr;
        }
        else{//否则插入在左边
            parent->left=locptr;
        }
    }
    refreshBothImformation();//插入后更新树高
    //由于插入的新的节点引起不平衡，所以只需找到此节点方向的最近的平衡因子为+-2的节点
    TreeNode* grandparent=NULL,*deepest2NodeParent=NULL,*deepest2Node=NULL;
    locptr=treeRoot;
    parent=NULL;
    while (locptr!=NULL)
    {
        if(parent!=NULL){
            grandparent=parent;
        }
        parent=locptr;
        if(user.getName()<locptr->data.getName())
        {
            if(locptr->balanceFactor==2 || locptr->balanceFactor==-2){//记录平衡因子的位置
                deepest2Node=parent;
                deepest2NodeParent=grandparent;
            }
            locptr=locptr->left;
        }
        else if(user.getName()>locptr->data.getName()){
            if(locptr->balanceFactor==2 || locptr->balanceFactor==-2){
                deepest2Node=parent;
                deepest2NodeParent=grandparent;
            }
            locptr=locptr->right;
        }
        if (locptr->data.getName()==user.getName() && locptr->data.getPassword()==user.getPassword()) {
            break;//寻找到该节点则说明已经找到最深的节点，即可退出循环
        }
    }
    balanceAux(deepest2Node,deepest2NodeParent);//插入后进行二叉树的平衡
    return true;
}

//用户注销方法，包括4种平衡操作
bool AVLTree::remove(const string &name){
    bool found=false;
    TreeNode *x=NULL,*parent=NULL;
    search(name, found, x, parent);
    if(!found)
    {
        cout<<"用户不存在\n";
        return false;
    }
    /*
    *删除一个节点需要考虑3种情况
    *（1）x是一个叶子结点（2）x有一个子女 （3）x有两个子女
    *（1）（2）可以合并为最多只有一个非空子树的情况
    *（3）可以看做是相当于另一个节点来替代被删除的节点，转化为（1（2）情况
    *被替代的要么是右子树的最小元素或者是左子树的最大元素，保证其最多只有一个非空子树的情况
    */
    if(x->left!=NULL && x->right!=NULL)//节点有两个子女的情况
    {
        TreeNode *xSucc=x->right;
        parent=x;
        while(xSucc->left!=NULL){
            parent=xSucc;
            xSucc=xSucc->left;
        }
        x->data=xSucc->data;//用右子树的最小元素代替要删元素
        x=xSucc;//将情况3转化为1或2，只要删除用于替代的节点即可删除x
    }
    //下面处理（1）（2）两种情况
    TreeNode *subtree=x->left;
    if(subtree==NULL){
        subtree=x->right;//如果left为空则指向右子树，右子树为空的情况也包括在内
    }
    if(parent==NULL)//被删除的是根节点
    {
        treeRoot=NULL;
    }
    else if(parent->left==x)//判断x在父节点的哪个子树中
    {
        parent->left=subtree;
    }
    else{
        parent->right=subtree;
    }
    delete x;//把要删的删除
    x=NULL;
    refreshBothImformation();//刷新各个节点的参数
    TreeNode *deepest2Node=NULL,*deepest2NodeParent=NULL;
    findDeep2Node(deepest2Node, deepest2NodeParent);
    balanceAux(deepest2Node, deepest2NodeParent);
    return true;
}

//辅助中序遍历操作
void AVLTree::inorderAux(ostream &out, TreeNode *subtreeRoot){
    if(subtreeRoot!=NULL){
        inorderAux(out, subtreeRoot->left);
        out<<subtreeRoot->data;
        inorderAux(out, subtreeRoot->right);//中序递归输出
    }
}

//中序遍历输出二叉树到out流中
void AVLTree::LVR(ostream &out){
    inorderAux(out, treeRoot);
}

//四种旋转皆为私有函数
//简单左旋，subtree为平衡因子为-2的节点，parent为其父节点
void AVLTree::LRotate(TreeNode *parent, TreeNode *subtree){
    if(subtree==NULL)//第一种情况 当subtree为空时直接返回
        return;
    TreeNode* node1=NULL,*node2=NULL;
    if(subtree==treeRoot)//第二种情况当subtree为根节点时，注意对根节点的操作
    {
        node1=treeRoot;
        node2=node1->right;
        treeRoot=node2; //经过简单左旋则node2为根节点
        node1->right=node2->left;//将node2的左节点给node1右节点保证了二叉树的性质
        node2->left=node1;
    }
    else{//第三种情况subtree不为根节点时，保证时subtree的右节点的右节点则进行左旋操作
        node1=subtree;
        node2=node1->right;
        if(parent->left==subtree)//subtree可能在parent的左边也可能在parent的右边，分两种情况讨论
            parent->left=node2;  //node2代替node1的位置
        if(parent->right==subtree)
            parent->right=node2;
        node1->right=node2->left;
        node2->left=node1;
    }
}

//简单右旋
void AVLTree::RRotate(TreeNode *parent, TreeNode *subtree){
    if(subtree==NULL)//第一种情况当subtree为空时，直接返回
        return;
    TreeNode *node1=NULL,*node2=NULL;
    if(subtree==treeRoot)//第二种情况当subtree为根节点时
    {
        node1=treeRoot;
        node2=node1->left;
        treeRoot=node2;
        node1->left=node2->right;
        node2->right=node1;
    }
    else{
        node1=subtree;  //第三种情况当subtree为普通节点时
        node2=subtree->left;
        if (parent->left==subtree) {
            parent->left=node2;
        }
        else if (parent->right==subtree)
            parent->right=node2;
        node1->left=node2->right;
        node2->right=node1;
    }
}

//左右旋
void AVLTree::LRRotate(TreeNode *parent, TreeNode *subtree){
    if(subtree==NULL)
        return;
    TreeNode *node1=NULL,*node2=NULL,*node3=NULL;
    node1=subtree;
    node2=node1->left;
    node3=node2->right;
    if(node3->right==NULL)//考虑到node3->right为空时不可以直接使用LRotate
    {
        node2->right=node3->left;
        node3->left=node2;
        node1->left=node3;
        RRotate(parent, node1);
    }
    else{
        LRotate(node1, node2);//先左旋，以node1为父节点，node2为子节点进行
        RRotate(parent, node1);//再右旋，以parent为父节点，以node1为子节点
    }
}

//右左旋
void AVLTree::RLRotate(TreeNode *parent, TreeNode *subtree){
    if(subtree==NULL){
        return;
    }
    TreeNode *node1=NULL,*node2=NULL,*node3=NULL;
    node1=subtree;
    node2=node1->right;
    node3=node2->left;
    if(node3->left==NULL)//考虑到node3->right为空时不可以直接使用LRotate
    {
        node2->left=node3->right;
        node3->right=node2;
        node1->right=node3;
        LRotate(parent, node1);
    }
    else{
        RRotate(node1, node2);
        LRotate(parent, node1);
    }
}

//找到平衡因子为+-2的节点的辅助函数//第一个参数为平衡因子为+-2的节点，parent为其父节点，第三个参数为根节点
void AVLTree::findDeepest2NodeAux(TreeNode *&deepest2Node, TreeNode *&parent, TreeNode *subtreeNode){
    if(subtreeNode!=NULL)
    {
        if((subtreeNode==treeRoot)&&((subtreeNode->balanceFactor==2)||(subtreeNode->balanceFactor=-2)))//对subtreeNode==treeRoot要单独考虑，因为其parent=NULL
        {
            deepest2Node=treeRoot;
            parent=NULL;
        }
        //因为插入一个节点或删除一个节点不会造成两颗无关对子树不平衡
        findDeepest2NodeAux(deepest2Node, parent, subtreeNode->left);//递归左子树
        findDeepest2NodeAux(deepest2Node, parent, subtreeNode->right);//递归右子树
        if((subtreeNode->right!=NULL)&&((subtreeNode->balanceFactor==2)||(subtreeNode->balanceFactor==-2)))
        {
            if(deepest2Node==NULL ||subtreeNode->right->floors>deepest2Node->floors)//当还没有找到平衡因子为+-2的节点时或是找到更深的平衡因子为+-2时更新deepest2Node和parent
            {
                deepest2Node=subtreeNode->right;//更新deepest2Node
                parent=subtreeNode;//更新parent
            }
        }
        if((subtreeNode->left!=NULL)&&((subtreeNode->balanceFactor==2)||(subtreeNode->balanceFactor==-2)))
        {
            if (deepest2Node==NULL || subtreeNode->left->floors>deepest2Node->floors) {//当还没有找到平衡因子为+-2的节点时或是找到更深的平衡因子为+-2时更新deepest2Node和parent
                deepest2Node=subtreeNode->left;
                parent=subtreeNode;
            }
        }
    }
}

//寻找平衡因子为+-2的节点
bool AVLTree::findDeep2Node(TreeNode *&deepest2Node,TreeNode *&parent){
    if(treeRoot->left->balanceFactor==2 || treeRoot->left->balanceFactor==-2){
        deepest2Node=treeRoot->left;
        parent=treeRoot;
        return true;
    }
    else if (treeRoot->right->balanceFactor==2 || treeRoot->left->balanceFactor==-2){
        deepest2Node=treeRoot->right;
        parent=treeRoot;
        return true;
    }
    else if(treeRoot->balanceFactor==2 || treeRoot->balanceFactor ==-2){
        deepest2Node=treeRoot;
        return true;
    }
    else
        return true;
}

//用于更新树中的内容
void AVLTree::refreshBothImformation(){
    int h=0;
    refreshBothImformationAux(h, 0, treeRoot);//从根节点开始对每一个节点的内容进行更新
}

//更新树中的内容的辅助函数，树高，树的层数，树的平衡因子。 通过递归来实现更新
//subheight代表该节点的为根节点的高度
//subfloor表示当前节点所在层数
void AVLTree::refreshBothImformationAux(int &subheight,int subfloor,TreeNode* subtreeNode){
    if(subtreeNode==NULL){
        subheight=0;
    }
    else if (subtreeNode!=NULL)
    {
        int left_height=0,right_height=0;//定义左右子树的高
        subtreeNode->floors=subfloor;//更新层数
        refreshBothImformationAux(left_height, subfloor+1, subtreeNode->left);//递归更新左子树
        refreshBothImformationAux(right_height, subfloor+1, subtreeNode->right);//递归更新右子树
        subtreeNode->balanceFactor=left_height-right_height;//更新平衡因子
        if(left_height>right_height){
            subheight=1+left_height;
        }
        else
            subheight=1+right_height;
        subtreeNode->height=subheight;//更新height
    }
}

//二叉树的平衡
void AVLTree::balance(){
    TreeNode *deepest2Node=NULL,*parent=NULL;
    findDeep2Node(deepest2Node, parent);
    balanceAux(deepest2Node, parent);
}

//用于平衡二叉树的辅助函数
void AVLTree::balanceAux(TreeNode* deepest2Node,TreeNode* parent){
    if(deepest2Node!=NULL)
    {
        if(deepest2Node->balanceFactor==2)//平衡因子为2则必定为左子树引起的不平衡
        {
            if(deepest2Node->left->right==NULL || ((deepest2Node->left->right!=NULL) && (deepest2Node->left->left!=NULL) && (deepest2Node->left->left->height)>=(deepest2Node->left->right->height))){
                //比较deepest2Node左子树与其左子树的右子树，如果其以节点为根节点的高即height大，进行简单右旋
                //若存在两节点height相同情况，则既是左左情况又是左右情况，也直接通过接单右旋来完成相关操作
                
                RRotate(parent,deepest2Node);
            }
            else //否则通过左右旋
            {
                LRRotate(parent,deepest2Node);
            }
        }
        else if (deepest2Node->balanceFactor==-2) //若平衡因子为-2一定是右子树引起的
        {
            if(deepest2Node->right->left==NULL ||(deepest2Node->right->left!=NULL && deepest2Node->right->right!=NULL && (deepest2Node->right->right->height)>=(deepest2Node->right->left->height)))
            {
                //右右情况则简单左旋
                LRotate(parent,deepest2Node);
            }
            else{//否则进行右左旋
                RLRotate(parent,deepest2Node);
            }
        }
        refreshBothImformation();//经过一次平衡后就要刷新树的其余信息
    }
}

//用于图形输出
void AVLTree::graph(ostream &out)//用于图形的输出
{
    graphAux(out,0,treeRoot);
}

//输入到文件
void AVLTree::graph(string file){
    if(file==""){
        cout<<"文件名不规范"<<endl;
    }
    ofstream outfile(file,ios::trunc);
    graph(outfile);
    outfile.close();
}

//用于图形输出的辅助函数
void AVLTree::graphAux(ostream &out, int indent, TreeNode *subtreeRoot){
    if(subtreeRoot!=NULL)
    {
        graphAux(out, indent+20, subtreeRoot->left);
        out<<setw(indent)<<" "<<subtreeRoot->data<<endl;
        graphAux(out, indent+20, subtreeRoot->right);
    }
}

