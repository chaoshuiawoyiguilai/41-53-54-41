#ifndef LOGINCONTROLER_H
#define LOGINCONTROLER_H

#include <QString>
enum class LoginResult
{
    ADMIN_LOGINED,
    USER_LOGINED,
    NO_USER,
    WRONG_PASSWORD,
};

class LoginControler
{
public:
    LoginControler();
    LoginResult Login(const QString& Name, const QString& Password);
};

#endif // LOGINCONTROLER_H
