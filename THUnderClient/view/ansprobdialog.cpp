#include "ansprobdialog.h"
#include "ui_ansprobdialog.h"
#include <string>
#include <cstring>
#include <QString>
#include <QDateTime>
#include <iostream>
using namespace std;

AnsProbDialog::AnsProbDialog(QWidget *parent, Stuop* stuop, string msg, QWidget* stumainpage) :
    QDialog(parent),
    ui(new Ui::AnsProbDialog)
{
    ui->setupUi(this);
    this->stuop = stuop;
    this->start_time = QDateTime::currentSecsSinceEpoch();
    printf("start time set\n");
    string prob_msg[6];
    for (int i = 0; i < 5; i++) {
        unsigned div = msg.find(':');
        prob_msg[i] = msg.substr(0, div);
        msg = msg.substr(div + 1);
        cout << prob_msg[i] << endl;
    }
    cout << msg << endl;
    this->ui->tb_prob->setText(QString::fromStdString(prob_msg[0]));
    this->ui->tb_a->setText(QString::fromStdString(prob_msg[1]));
    this->ui->tb_b->setText(QString::fromStdString(prob_msg[2]));
    this->ui->tb_c->setText(QString::fromStdString(prob_msg[3]));
    this->ui->tb_d->setText(QString::fromStdString(prob_msg[4]));
    if (msg.length() > 1)
        this->ui->lbl_single_multiple->setText(
                "The problem has MULTIPLE correct answers!");
    else this->ui->lbl_single_multiple->setText(
                "The problem has ONE correct answer!");
    this->stumainpage = stumainpage;
    cout << "all set\n";

}

AnsProbDialog::~AnsProbDialog()
{
    delete ui;
}

void AnsProbDialog::on_b_send_clicked()
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
    // CreateThread
}

DWORD WINAPI AnsProbDialog::receive_msg(LPVOID lpParameter) {
    AnsProbDialog* cur = (AnsProbDialog*) lpParameter;
    while (true) {
        string msg = cur->stuop->receive_msg();
        if (msg.empty() || msg == "\n") continue;
        string msg_head = msg.substr(0, 4);
        cout << "received msg, " << msg.length() << ", " << msg_head << endl;
        if (msg_head == PULL_PROB) {
            cur->close();
            CreateThread(nullptr, 0, cur->stumainpage->receive_msg, (LPVOID)this, 0, nullptr);
            break;
        }
    }
}
