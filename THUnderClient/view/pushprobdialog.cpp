#include "pushprobdialog.h"
#include "ui_pushprobdialog.h"
#include <iostream>
using namespace std;

PushProbDialog::PushProbDialog(QWidget *parent, Teacherop* teacherop) :
    QDialog(parent),
    ui(new Ui::PushProbDialog)
{
    ui->setupUi(this);
    this->teacherop = teacherop;
}

PushProbDialog::~PushProbDialog()
{
    delete ui;
}

void PushProbDialog::on_b_push_clicked()
{
    string prob = ui->te_prob->toPlainText().toStdString();
    string ans = ui->te_a->toPlainText().toStdString() + ":" +
                 ui->te_b->toPlainText().toStdString() + ":" +
                 ui->te_c->toPlainText().toStdString() + ":" +
                 ui->te_d->toPlainText().toStdString();
    string right_ans = "";
    if (ui->cb_a->isChecked()) {
        right_ans += "A";
    }
    if (ui->cb_b->isChecked()) {
        right_ans += "B";
    }
    if (ui->cb_c->isChecked()) {
        right_ans += "C";
    }
    if (ui->cb_d->isChecked()) {
        right_ans += "D";
    }
    teacherop->send_prob(prob, ans, right_ans);
}

DWORD WINAPI PushProbDialog::receive_msg(LPVOID lpParameter)
{
    PushProbDialog* cur = (PushProbDialog*) lpParameter;
    while (true) {
        string msg = cur->teacherop->receive_msg();
        if (msg.empty() || msg == "\n") continue;
        string msg_head = msg.substr(0, 4);
        cout << "received msg, " << msg.length() << ", " << msg_head << endl;
        if (msg_head == ANS_PROB) {
            msg = msg.substr(4);
            msg = msg.substr(0, msg.length() - 1);
            unsigned div = msg.find(':');
            string username = msg.substr(0, div);
            msg = msg.substr(div + 1);
            div = msg.find(':');
            string ans = msg.substr(0, div);
            string time = msg.substr(div + 1);

            // insert new student to table: result
            for (int i = 0; i < ans.length(); i++) {
                if (ans[i] != '0') {
                    QTableWidgetItem* item = cur->ui->tbl_result->item(i, 0);
                    QString oritext = item->text();
                    oritext = oritext + QString::fromStdString(username + ", ");
                    item->setText(oritext);

                    item = cur->ui->tbl_result->item(i, 1);
                    oritext = item->text();
                    unsigned orinumber = oritext.toUInt();
                    orinumber += 1;
                    item->setText(QString::fromStdString(to_string(orinumber)));
                }
            }

            // insert new student to table: result_2
            cur->ui->tbl_result_2->insertRow(0);
            QTableWidgetItem* item = cur->ui->tbl_result_2->item(0, 0);
            item->setText(QString::fromStdString(username));
            item = cur->ui->tbl_result_2->item(0, 1);
            item->setText(QString::fromStdString(ans));
            item = cur->ui->tbl_result_2->item(0, 2);
            item->setText(QString::fromStdString(time));
        }
    }
}
