#include <QMessageBox>
#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}


void LoginWindow::on_btnLogin_clicked()
{
    LoginResult Res = Controler.Login(
                ui->edtUserName->text(),
                ui->edtPassword->text());
    if (Res == LoginResult::NO_USER) {
        QMessageBox::information(NULL, "登录失败", "用户名不存在！", QMessageBox::Ok);
    }
    else if (Res == LoginResult::WRONG_PASSWORD) {
        QMessageBox::information(NULL, "登录失败", "密码错误！", QMessageBox::Ok);
    }
    else if (Res == LoginResult::ADMIN_LOGINED) {
        QMessageBox::information(NULL, "登录成功", "管理员已登录！", QMessageBox::Ok);
    }
    else {
        QMessageBox::information(NULL, "登录车工", "用户 " + ui->edtUserName->text() + " 已登录！", QMessageBox::Ok);
    }
}
