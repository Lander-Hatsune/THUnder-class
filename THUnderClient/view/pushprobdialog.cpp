#include "pushprobdialog.h"
#include "ui_pushprobdialog.h"
using namespace std;

PushProbDialog::PushProbDialog(QWidget *parent, Teacherop* teacherop) :
    QDialog(parent),
    ui(new Ui::PushProbDialog)
{
    ui->setupUi(this);
    this->teacherop = teacherop;
    connect(teacherop, SIGNAL(ans_got(QString)), this, SLOT(refresh_tables(QString)));
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

void PushProbDialog::on_b_pull_clicked()
{
    teacherop->pull_prob();
    ui->lbl_prob->setText("Problem (pulled)");
}

void PushProbDialog::refresh_tables(QString qmsg)
{
    string msg = qmsg.toStdString();
    unsigned div = msg.find(':');
    QString username = QString::fromStdString(msg.substr(0, div));
    msg = msg.substr(div + 1);
    div = msg.find(':');
    QString ans = QString::fromStdString(msg.substr(0, div));
    QString time = QString::fromStdString(msg.substr(div + 1));

    // insert new student to table: result
    for (int i = 0; i < 4; i++) {
        if (ans[i] != '0') {
            QTableWidgetItem* item1 = this->ui->tbl_result->item(i, 0);
            QString oritext = item1->text();
            item1->setText(oritext + username + ", ");

            QTableWidgetItem* item2 = this->ui->tbl_result->item(i, 1);
            oritext = item2->text();
            unsigned orinumber = oritext.toUInt();
            orinumber += 1;
            item2->setText(QString::fromStdString(to_string(orinumber)));
        }
    }

    // insert new student to table: result_2
    this->ui->tbl_result_2->insertRow(0);
    QTableWidgetItem* item2_1 = new QTableWidgetItem(username);
    this->ui->tbl_result_2->setItem(0, 0, item2_1);
    QTableWidgetItem* item2_2 = new QTableWidgetItem(ans);
    this->ui->tbl_result_2->setItem(0, 1, item2_2);
    QTableWidgetItem* item2_3 = new QTableWidgetItem(time);
    this->ui->tbl_result_2->setItem(0, 2, item2_3);
}
