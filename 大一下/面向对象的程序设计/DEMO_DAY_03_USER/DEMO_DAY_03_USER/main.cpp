//
//  main.cpp
//  DEMO_DAY_03_USER
//
//  Created by 范静涛 on 2021/7/27.
//

#include <iostream>
#include "User.hpp"

int main(int argc, const char * argv[]) {
    bool IsAdded = false;
    IsAdded = User::AddAdministrator();
    IsAdded = User::AddAdministrator();
    IsAdded = User::AddTrivalUser("1", "456");
    IsAdded = User::AddTrivalUser("1", "567");
    IsAdded = User::AddTrivalUser("2", "567");
    IsAdded = User::AddTrivalUser("Admin", "567");
    return 0;
}
