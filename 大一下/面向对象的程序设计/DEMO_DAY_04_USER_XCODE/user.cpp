#include "user.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <fstream>
using namespace std;

#include "administrator.h"

vector<shared_ptr<User>> User::m_All{};

User::User(const string& Name, const CipherText& Password) : m_Password(Password){
    auto Finder = [&Name](shared_ptr<User> ptr)->bool{return (ptr->m_Name == Name);};
    auto it = find_if(m_All.begin(), m_All.end(), Finder);
    if (it != m_All.end()) {
        if ((*it)->IsAdministrator()) {
            throw invalid_argument("Administrator exists.");
        }
        else {
            throw invalid_argument("Duplicate username");
        }
    }
    m_Name = Name;
    m_All.push_back(shared_ptr<User>(this));
}

void User::AddUser(const string& Name, const CipherText& Password){
    new User(Name, Password);
}

bool User::IsExist(const string& Name) {
    auto Finder = [&Name](shared_ptr<User> ptr)->bool{return (ptr->m_Name == Name);};
    auto it = find_if(m_All.begin(), m_All.end(), Finder);
    return (it != m_All.end());
}
//
bool User::IsAdministrator() const{
    return false;
}

void User::OutputToStream(ostream& Stream) const{
    Stream << m_Name << endl << m_Password << endl;
}

void User::SaveToFile(const string& FileName){
    ofstream File(FileName);
    if (!File.is_open()) {
        throw invalid_argument("Can't Create File : " + FileName);
    }
    auto Saver = [&File](shared_ptr<User> Ptr){Ptr->OutputToStream(File);};
    File << m_All.size() << endl;
    for_each(m_All.begin(), m_All.end(),Saver);
    File.close();
}

void User::LoadFromFile(const string& FileName){
    ifstream File(FileName);
    if (!File.is_open()) {
        throw invalid_argument("File Not Exist: " + FileName);
    }
    unsigned long UserCount;
    File >> UserCount;
    File.get();
    if (UserCount <= 1) {
        new Administrator();
    }
    else{
        string Name;
        string Password;
        getline(File, Name);
        getline(File, Password);
        new Administrator(CipherText::MakeFromCipherText(Password));
        for (unsigned long i = 0; i < UserCount - 1; i++) {
            getline(File, Name);
            getline(File, Password);
            new User(Name, CipherText::MakeFromCipherText(Password));
        }
    }
   File.close();
}

shared_ptr<User> User::Verify(const string& Name, const string& Password){
    auto Finder = [&Name](shared_ptr<User> ptr)->bool{return (ptr->m_Name == Name);};
    auto it = find_if(m_All.begin(), m_All.end(), Finder);
    if (it == m_All.end()) {
        throw invalid_argument("No such user.");
    }
    else if ((*it)->m_Password != Password){
        throw invalid_argument("Wrong password.");
    }
    else {
        return *it;
    }
}
