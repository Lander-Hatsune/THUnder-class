#include "loginpage.h"
#include "./ui_loginpage.h"
#include "../controller/loginop.h"
#include <string>
#include <QString>
using std::to_string;

LoginPage::LoginPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);
}

LoginPage::~LoginPage()
{
    delete ui;
}


void LoginPage::on_b_login_clicked()
{
    string username = this->ui->le_username->text().toStdString();
    string pswd = this->ui->le_pswd->text().toStdString();
    unsigned keeploginpage = this->op->login(username, pswd);
    printf("%d\n", *(this->op->failtime));
    if (*(this->op->failtime) >= 1) {
        ui->lbl_pswdalert->setText("username or password is invalid,\nyou can try " +
                                   QString::fromStdString(to_string(3 - *(this->op->failtime))) +
                                   " more times");
    }
    if (!keeploginpage) this->close();
}
