#include "administrator.h"


void Administrator::AddUser(const string &Name, const string& Password){
    this->User::AddUser(Name, Password);
}

bool Administrator::IsAdministrator() const {
    return true;
}

Administrator::Administrator():User("Admin", string("Admin")) {
}

Administrator::Administrator(const CipherText& Password):User("Admin", Password) {
    
}
