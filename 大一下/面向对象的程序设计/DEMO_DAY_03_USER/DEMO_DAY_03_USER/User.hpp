//
//  User.hpp
//  DEMO_DAY_03_USER
//
//  Created by 范静涛 on 2021/7/27.
//

//哨兵
#ifndef User_hpp
#define User_hpp
//必要的头文件
#include <string>
#include <vector>

using namespace std;

//用户类型枚举类定义
enum class UserType {
    TRIVAL, //普通用户
    ADMIN   //管理员用户
};

//用户类声明
class User {
public:
    //不允许无用户名和密码的用户创建，故delete默认构造函数
    User() = delete;
    //不允许拷贝构造和赋值对象，因为会造成两个实例用户名相同，故delete
    User(const User&) = delete;
    User& operator=(const User&) = delete;
    
    //用于添加一个管理员，返回true表示成功，返回false表示失败（只允许一个管理员实例）
    static bool AddAdministrator();
    //用于添加一个普通用户，返回true表示成功，返回false表示失败（普通用户不能重名，也不能是Admin）
    static bool AddTrivalUser(const string& Name, const string& Password);

private:
    //指定用户名、密码和类型的构造函数，私有是为了保证使用者无法跳过用户名称和数量规则自行创建用户
    User(const string& Name, const string& Password, UserType Type);
    //释放所有已经创建的用户实例，私有是因为不允许使用者自行释放，本函数会在程序结束时自动被调用
    static void ClearAllUser();

    //用户名
    string m_Name;
    //密码
    string m_Password;
    //用户类型
    UserType m_Type;
    
    //默认的管理员用户名
    static string AdminName;
    //默认的管理员用户名
    static string AdminPassword;
    //用户列表：存放全部用户实例的指针数组，私有是为了保证使用者无法访问到用户列表
    static vector<User*> m_AllUsers;
    
    //用户自动释放全部用户列表的内嵌类
    class Garbo{
    public:
        //析构函数
        ~Garbo();
    };
    
    //用户自动释放触发器对象，此静态对象在程序结束时自动调用其析构函数，析构函数调用User::ClearAllUser()
    static Garbo m_Garbo;
};


#endif /* User_hpp */
