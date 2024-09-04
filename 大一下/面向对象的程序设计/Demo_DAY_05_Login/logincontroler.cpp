#include "logincontroler.h"
#include "user.h"
#include "administrator.h"

LoginControler::LoginControler()
{
    User::LoadFromFile("../../../Users.txt");
}

LoginResult LoginControler::Login(const QString& Name, const QString& Password){
    try {
        shared_ptr<User> LoginedUser = User::Verify(Name.toStdString(), Password.toStdString());
        if (LoginedUser->IsAdministrator()) {
            return LoginResult::ADMIN_LOGINED;
        }
        else {
            return LoginResult::USER_LOGINED;
        }
    } catch (invalid_argument e) {
        if (e.what() == string("No such user.")) {
            return LoginResult::NO_USER;
        }
        else {
            return LoginResult::WRONG_PASSWORD;
        }
    }
}
