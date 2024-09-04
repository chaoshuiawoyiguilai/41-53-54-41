#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "user.h"
#include "CipherText.hpp"
#include <string>
using namespace std;

class Administrator : public User
{
public:
    Administrator(const Administrator&) = delete ;
    Administrator& operator=(const Administrator&) = delete;
    void AddUser(const string& Name, const string& Password);
    Administrator();
    Administrator(const CipherText& Password);
    bool IsAdministrator() const override;
};

#endif // ADMINISTRATOR_H
