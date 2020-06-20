#include "loginpage.h"
#include "./ui_loginpage.h"
using std::to_string;

using namespace std;

LoginPage::LoginPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    this->loginop = new Loginop();
    this->setWindowTitle("THUnder Class-login");
}

LoginPage::~LoginPage()
{
    delete ui;
    delete this->loginop;
}


void LoginPage::on_b_login_clicked()
{
    string username = this->ui->le_username->text().toStdString();
    string pswd = this->ui->le_pswd->text().toStdString();
    string ip = this->ui->le_ip->text().toStdString();

    if (username.empty() || pswd.empty()) return;
    QString ret = this->loginop->login(username, pswd, ip);
    if (ret == ":SHUT:") {
        this->close();
    }
    else if (ret == ":HIDE:") {
        this->hide();
    }

    ui->lbl_pswdalert->setText(ret);
}
