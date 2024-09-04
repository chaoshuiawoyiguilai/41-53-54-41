#ifndef USER_H
#define USER_H

#include<string>
#include<vector>
#include<iostream>
#include<memory>
using namespace std;

#include "CipherText.hpp"

class User
{
public:
    User() = delete;
    User(const User&) = delete;
    User& operator=(const User&) = delete;

    virtual bool IsAdministrator() const;
    void OutputToStream(ostream& Stream) const;
    static void SaveToFile(const string& FileName);
    static void LoadFromFile(const string& FileName);
    static shared_ptr<User> Verify(const string& Name, const string& Password);
protected:
    User(const string& Name, const CipherText& Password);
    void AddUser(const string& Name, const CipherText& Password);
private:
    static bool IsExist(const string& Name);
    static vector<shared_ptr<User>> m_All;

    string m_Name;
    CipherText m_Password;
};

#endif // USER_H
