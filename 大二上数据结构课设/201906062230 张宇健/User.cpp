//
//  User.cpp
//  Course_design
//
//  Created by apple on 2021/1/5.
//

#include "User.hpp"
#include <iostream>
using namespace std;

User::User(string name,string password):sName(name),sPassword(password){} //构造函数

User::User(User& u){
    sName=u.sName;sPassword=u.sPassword;
}//拷贝构造函数

string User::getName(){
    return sName;
}//得到用户姓名

string User::getPassword(){
    return sPassword;
}//得到用户密码

void User::setName(string name){
    sName=name;
}//设置用户姓名

void User::setPassword(string password){
    sPassword=password;
}//设置用户密码

void User::changeName(string name){
    sName=name;
}//更新用户姓名

void User::changePassword(string password){
    sPassword=password;
}//更新用户密码

istream& operator>>(istream& in,User& u){
    string name;
    string password;
    in>>name>>password;
    if (name.length()>MAX_NAME_LENGTH) {//输入时判断姓名是否越界
        throw out_of_range("用户名长度越界"+name+" "+password);
    }
    else if (password.length()>MAX_PASSWORD_LENGTH){//判断密码是否越界
        throw out_of_range("密码长度越界"+name+" "+password);
    }
    else{
        u.setName(name);
        u.setPassword(password);
    }
    return in;
}////重载输入，可以从文件中输入用户

ostream& operator<<(ostream& out,User& u){
    out<<u.sName<<" "<<u.sPassword<<endl;
    return out;
}//重载输出 ，向文件中写出用户

