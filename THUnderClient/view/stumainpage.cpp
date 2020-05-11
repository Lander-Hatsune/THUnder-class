#include "stumainpage.h"
#include "ui_stumainpage.h"

StuMainPage::StuMainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StuMainPage)
{
    ui->setupUi(this);
}

StuMainPage::~StuMainPage()
{
    delete ui;
}
