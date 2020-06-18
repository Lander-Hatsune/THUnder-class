#include "ansprobwindow.h"
#include "ui_ansprobwindow.h"
#include <QDateTime>
#include <iostream>
using namespace std;

AnsProbWindow::AnsProbWindow(QWidget *parent, Stuop* stuop, string msg) :
    QWidget(parent),
    ui(new Ui::AnsProbWindow)
{
    ui->setupUi(this);
    this->stuop = stuop;

    this->start_time = QDateTime::currentSecsSinceEpoch();
    string prob_msg[6];
    for (int i = 0; i < 5; i++) {
        unsigned div = msg.find(':');
        prob_msg[i] = msg.substr(0, div);
        msg = msg.substr(div + 1);
        cout << prob_msg[i] << endl;
    }
    cout << msg << endl;
    this->ui->tb_prob->setText(QString::fromStdString(prob_msg[0]));
    this->ui->tb_a_2->setText(QString::fromStdString(prob_msg[1]));
    this->ui->tb_b->setText(QString::fromStdString(prob_msg[2]));
    this->ui->tb_c->setText(QString::fromStdString(prob_msg[3]));
    this->ui->tb_d->setText(QString::fromStdString(prob_msg[4]));
    if (msg.length() > 1)
        this->ui->lbl_single_multiple->setText(
                "The problem has MULTIPLE correct answers!");
    else this->ui->lbl_single_multiple->setText(
                "The problem has ONE correct answer!");
    cout << "all set\n";

}

AnsProbWindow::~AnsProbWindow()
{
    delete ui;
}

void AnsProbWindow::on_b_send_clicked()
{
    string ans = "";
    if (ui->cb_a->isChecked())
        ans += "A";
    else ans += "0";

    if (ui->cb_b->isChecked())
        ans += "B";
    else ans += "0";

    if (ui->cb_c->isChecked())
        ans += "C";
    else ans += "0";

    if (ui->cb_d->isChecked())
        ans += "D";
    else ans += "0";

    unsigned usedtime = QDateTime::currentSecsSinceEpoch() - this->start_time;
    stuop->send_ans(ans, usedtime);
    this->close();
}
