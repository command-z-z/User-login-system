//
//  main.cpp
//  Course_design
//
//  Created by apple on 2021/1/3.
//

#include <iostream>
#include "AVLTree.hpp"
#include "TreeNode.hpp"
#define KEY 111111//密钥的宏定义
using namespace std;
int main() {
    AVLTree myTree;  //我的AVL树
    myTree.load("/Users/apple/Desktop/xcode/Course_design/Course_design/User.txt");//从文件中导入用户信息。初始化二叉树
    int nkey;//管理员密钥
    int nOption1,nOption2,nOption3,nOption4;//用来选择操作
    int nRemoveFlag=0;//注销时的标志
    string sName;// 用户名
    string sName2;//新的用户名
    string sName3;//要删除的用户名
    string sName4;//要注册的用户名
    string sPassword1;//用户密码
    string sPassword2;//用户旧密码
    string sPassword3;//用户新密码
    string sPassword4;//再次输入用户新密码
    string sPassword5;//注册密码
    string sPassword6;//再次输入注册新密码
    User user;//记录用户
    User* userPtr;
    while(1)
    {
        cout<<"*******************************\n";
        cout<<"*        服务系统登入         *\n";
        cout<<"*******************************\n";
        cout<<"*        1.用户登入           *\n";
        cout<<"*        2.用户注册           *\n";
        cout<<"*        3.管理员权限         *\n";
        cout<<"*        4.测试题            *\n";
        cout<<"*     提示：退出系统请输入0   *\n";
        cout<<"*******************************\n";
        cout<<"请输入您想要进行的操作：";
        cin>>nOption1;
        if(nOption1==0)break;
        switch (nOption1) {
            case 1:{
                system("clear");
                cout<<"*******************************\n";
                cout<<"      请输入用户名:";
                cin>>sName;
                cout<<"      请输入密码:";
                cin>>sPassword1;
                cout<<"*******************************\n";
                userPtr=myTree.match(sName, sPassword1);//此变量即为登入的用户
                if(userPtr==NULL)
                    break;//直接返回上层
                while(2)
                    {
                        system("clear");
                        if(nRemoveFlag==1)break;//当注销后也直接返回上层界面
                        cout<<"*******************************\n";
                        cout<<"*        用户选择界面         *\n";
                        cout<<"*******************************\n";
                        cout<<"*        1.用户密码更新       *\n";
                        cout<<"*        2.用户名更新         *\n";
                        cout<<"*        3.用户注销           *\n";
                        cout<<"*    提示：返回上一级界面按-1  *\n";
                        cout<<"*******************************\n";
                        cout<<"请输入您想要进行的操作：";
                        cin>>nOption2;
                        if(nOption2==-1)break;
                        switch (nOption2) {
                            case 1:
                            {
                                cout<<"       请输入旧密码:";
                                cin>>sPassword2;
                                cout<<"       请输入新密码:";
                                cin>>sPassword3;
                                cout<<"       请再次输入新密码:";
                                cin>>sPassword4;//旧密码不符
                                if(sPassword2!=sPassword1){
                                    cout<<"*******************************\n";
                                    cout<<"*        旧密码输入错误        *\n";
                                    cout<<"*******************************\n";
                                }
                                else if(sPassword3!=sPassword4){//两次新密码不相同
                                    cout<<"*******************************\n";
                                    cout<<"*        两次密码不匹配        *\n";
                                    cout<<"*******************************\n";
                                }
                                else{
                                    userPtr->changePassword(sPassword4);
                                    cout<<"*******************************\n";
                                    cout<<"*         密码修改成功         *\n";
                                    cout<<"*******************************\n";
                                }
                                int i=0;
                                cout<<"输入-1返回上层界面:";
                                cin>>i;
                                if(i==-1)
                                {
                                    break;
                                }
                            }
                            case 2:
                            {
                                cout<<"       请输入要更改的用户名:";
                                cin>>sName2;
                                if(myTree.search(sName2)!=NULL){
                                    cout<<"*******************************\n";
                                    cout<<"          用户名已经存在\n";
                                    cout<<"*******************************\n";
                                }
                                else{
                                    userPtr->changeName(sName2);
                                    cout<<"*******************************\n";
                                    cout<<"          用户名更改成功\n";
                                    cout<<"*******************************\n";
                                }
                                int i=0;
                                cout<<"输入-1返回上层界面:";
                                cin>>i;
                                if(i==-1)
                                {
                                    break;
                                }
                            }
                            case 3:
                                cout<<"*******************************\n";
                                cout<<"     请问确定要注销账户吗？\n";
                                cout<<"     1.确定     2.取消\n";
                                cout<<"*******************************\n";
                                cout<<"请输入你的选择：";
                                cin>>nOption3;
                                if(nOption3==1)
                                {
                                    if (myTree.remove(userPtr->getName())) {
                                        cout<<"*******************************\n";
                                        cout<<"*         用户已经注销          *\n";
                                        cout<<"*******************************\n";
                                        nRemoveFlag=1;//用户注销后。此账户不存在，因此直接返回上层
                                        break;
                                    }
                                }
                                else{
                                    cout<<"**************************\n";
                                    cout<<"     已取消注销！！！\n";
                                    cout<<"**************************\n";
                                }
                                break;//退出case3
                            }
                    }
            }
                break;//case为1结尾
            case 2:
                {
                    system("clear");
                    cout<<"*******************************\n";
                    cout<<"*        用户注册界面         *\n";
                    cout<<"*******************************\n";
                    cout<<"请输入注册用户名：";
                    cin>>sName4;
                    cout<<"请输入密码：";
                    cin>>sPassword5;
                    cout<<"请再次输入密码";
                    cin>>sPassword6;
                    if(myTree.search(sName4)!=NULL)
                    {
                        cout<<"**************************\n";
                        cout<<"     用户名已存在"<<endl;
                        cout<<"**************************\n";
                    }
                    else if(sPassword6!=sPassword5){
                        cout<<"**************************\n";
                        cout<<"     密码输入不符"<<endl;
                        cout<<"**************************\n";
                    }
                    else
                    {
                        user.setName(sName4);
                        user.setPassword(sPassword6);
                        if(myTree.insert(user)){
                            cout<<"     注册成功"<<endl;
                            break;
                        }
                    }
                    break;//退出case2
                }
            case 3:
                {
                    system("clear");
                    cout<<"******************************\n";
                    cout<<" 请输入管理员密钥:";
                    cin>>nkey;
                    if(nkey!=KEY)
                    {
                        cout<<"**********************\n";
                        cout<<"     密钥输入错误！！！"<<endl;
                        cout<<"**********************\n";
                        break;//直接返回上一层
                    }
                    else
                    {
                        while (4)
                        {
                            system("clear");
                            cout<<"*******************************\n";
                            cout<<"*        管理员界面           *\n";
                            cout<<"*******************************\n";
                            cout<<"*      1.用户信息二叉树显示   *\n";
                            cout<<"*      2.用户信息删除         *\n";
                            cout<<"*   提示：返回上一级界面按-1  *\n";
                            cout<<"*******************************\n";
                            cout<<"请输入您想要进行的操作：";
                            cin>>nOption4;
                            if(nOption4==-1){
                                system("clear");
                                break;
                            }
                            switch (nOption4) {
                                case 1:
                                {
                                    cout<<" *************************************用户信息二叉树图显示*************************************\n";
                                    myTree.graph(cout);
                                    int i=0;
                                    cout<<"输入-1返回上层界面:";
                                    cin>>i;
                                    if(i==-1)
                                    {
                                        break;
                                    }
                                }
                                case 2:
                                    cout<<"*******************************\n";
                                    cout<<"请输入要删除的用户信息的用户名:";
                                    cin>>sName3;
                                    cout<<"请问确定要删除账户"<<sName3<<"吗？\n";
                                    cout<<"1.确定     2.取消\n";
                                    cout<<"请输入你的选择：";
                                    cin>>nOption3;
                                    if(nOption3==1)
                                    {
                                        if(myTree.remove(sName3))
                                        {
                                            cout<<"**********************\n";
                                            cout<<"*      删除成功！    *"<<endl;
                                            cout<<"**********************\n";
                                            int j=0;
                                            cout<<"输入-1返回上层界面:";
                                            cin>>j;
                                            if(j==-1)
                                            {
                                                break;
                                            }
                                        }
                                    }
                                    else{
                                        cout<<"     已取消删除！！！\n";
                                    }
                                    int j=0;
                                    cout<<"输入-1返回上层界面:";
                                    cin>>j;
                                    if(j==-1)
                                    {
                                        break;
                                    }
                            }
                        }
                    }
                }
            }
        }
    myTree.save("/Users/apple/Desktop/xcode/Course_design/Course_design/User.txt");
}
