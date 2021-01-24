//
//  User.hpp
//  Course_design
//
//  Created by apple on 2021/1/5.
//

#ifndef User_hpp
#define User_hpp

#include<iostream>
#include <string>
#define MAX_NAME_LENGTH 32 //名字最长32位
#define MAX_PASSWORD_LENGTH 16  //密码最长16位
using namespace std;
class User{
private:
    string sName;//用于记录用户的
    string sPassword;//用户密码；；
public:
    User(string name="",string password="");//构造函数
    User(User& u);//拷贝构造函数
    string getName();//得到用户名
    string getPassword();//得到密码
    void setName(string name);//设置用户姓名
    void setPassword(string password);//设置用户密码
    void changeName(string name);//更新用户姓名
    void changePassword(string password);//更新用户密码
    friend istream& operator>>(istream& in,User& u);//重载输入，向文件中输入用户
    friend ostream& operator<<(ostream& out,User& u);//重载输出 ，向文件中输出用户。 声明为友元函数
};
#endif /* User_hpp */
