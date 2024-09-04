//
//  User.cpp
//  DEMO_DAY_03_USER
//
//  Created by 范静涛 on 2021/7/27.
//

#include "User.hpp"

//静态成员初始化
//初始化用户指针列表为空表
vector<User*> User::m_AllUsers{};
//初始化用户自动释放触发器对象
User::Garbo User::m_Garbo{};
//默认的管理员用户名
string User::AdminName{"Admin"};
//默认的管理员用户名
string User::AdminPassword{"Admin"};

//指定用户名、密码和类型的构造函数
User::User(const string& Name, const string& Password, UserType Type){
    //用户名和密码不可为空
    if (Name.empty()) {
        throw string("Empty user name");
    }
    if (Name.empty()) {
        throw string("Empty password");
    }
    //私有非静态成员赋初值
    m_Name = Name;
    m_Password = Password;
    m_Type = Type;
}

//创建一个管理员
bool User::AddAdministrator(){
    //所搜是已存在管理员
    for (const auto& n : m_AllUsers) {
        //存在返回false
        if (n->m_Type == UserType::ADMIN) {
            return false;
        }
    }
    
    //不存在则新建并存入用户指针列表，返回true
    m_AllUsers.push_back(new User(AdminName, AdminPassword, UserType::ADMIN));
    return true;
}

bool User::AddTrivalUser(const string& Name, const string& Password){
    //用户名不能是Admin
    if (Name == AdminName) {
        return false;
    }

    //所搜是已存在同名用户
    for (const auto& n : m_AllUsers) {
        //存在返回false
        if (n->m_Name == Name) {
            return false;
        }
    }
    //不存在则新建并存入用户指针列表，返回true
    m_AllUsers.push_back(new User(Name, Password, UserType::TRIVAL));
    return true;
}

//释放全部用户
void User::ClearAllUser(){
    //遍历用户指针，释放示例，指针置空
    for (auto& n : m_AllUsers) {
        delete n;
        n = nullptr;
    }
    //清空列表
    m_AllUsers.clear();
}

//自动释放用户触发器析构函数，在程序结束时自动被调用
User::Garbo::~Garbo(){
    //释放全部用户
    User::ClearAllUser();
}



