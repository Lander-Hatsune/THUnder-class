#include "adminmainpage.h"
#include "ui_adminmainpage.h"

AdminMainPage::AdminMainPage(QWidget *parent, Adminop* adminop) :
    QWidget(parent),
    ui(new Ui::AdminMainPage)
{
    ui->setupUi(this);
    this->adminop = adminop;
    ui->rb_changepswd->click();
}

AdminMainPage::~AdminMainPage()
{
    delete ui;
}

void AdminMainPage::on_b_add_clicked()
{
    string username = ui->le_addusername->text().toStdString();
    string pswd = ui->le_addpswd->text().toStdString();
    CLT_TYPE type = 3 - ui->cb_type->currentIndex();// 1: ADMIN, 2: TEACHER, 3: STU
    QString ret;
    if (username.empty() || pswd.empty()) {
        ret = "Username or password shouldn't be blank";
    } else {
        ret = this->adminop->add_clientop(username, pswd, type);
    }
    ui->lbl_add_alert->setText(ret);
}


void AdminMainPage::on_b_del_clicked()
{
    string username = ui->le_delusername->text().toStdString();
    QString ret;
    if (username.empty()) {
        ret = "Username shouldn't be blank";
    } else {
        ret = this->adminop->del_clientop(username);
    }
    ui->lbl_del_alert->setText(ret);
}

void AdminMainPage::on_rb_changepswd_clicked()
{
    ui->lbl_changewhat->setText("New password:");
}

void AdminMainPage::on_rb_changeusername_clicked()
{
    ui->lbl_changewhat->setText("New username:");
}

void AdminMainPage::on_b_change_clicked()
{
    string username = ui->le_changeusername->text().toStdString();
    string changeto = ui->le_changeto->text().toStdString();
    QString ret;
    if (ui->rb_changepswd->isDown()) {
        if (username.empty() || changeto.empty()) {
            ret = "Username or new password shouldn't be blank";
        } else {
            ret = this->adminop->change_pswdop(username, changeto);
        }
    } else {
        if (username.empty() || changeto.empty()) {
            ret = "Username or new username shouldn't be blank";
        } else {
            ret = this->adminop->change_usernameop(username, changeto);
        }
    }
    ui->lbl_change_alert->setText(ret);
}

