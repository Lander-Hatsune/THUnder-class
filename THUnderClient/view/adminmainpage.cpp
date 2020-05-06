#include "adminmainpage.h"
#include "ui_adminmainpage.h"

AdminMainPage::AdminMainPage(QWidget *parent, const Adminop* adminop) :
    QWidget(parent),
    ui(new Ui::AdminMainPage)
{
    ui->setupUi(this);
    this->op = adminop;
}

AdminMainPage::~AdminMainPage()
{
    delete ui;
}
