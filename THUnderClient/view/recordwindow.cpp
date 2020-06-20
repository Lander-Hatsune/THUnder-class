#include "recordwindow.h"
#include "ui_recordwindow.h"
using namespace std;

RecordWindow::RecordWindow(QWidget *parent, vector<Record*> records) :
    QWidget(parent),
    ui(new Ui::RecordWindow)
{
    ui->setupUi(this);
    for (int i = 0; i < records.size(); i++) {
        Record* rec = records[i];
        QString username = QString::fromStdString(rec->username);
        QString start_time = QString::fromStdString(rec->start_time);
        QString quit_time = QString::fromStdString(rec->quit_time);
        QString att_ratio = QString::fromStdString(rec->att_ratio);
        this->ui->tbl->insertRow(0);
        QTableWidgetItem* item1 = new QTableWidgetItem(username);
        QTableWidgetItem* item2 = new QTableWidgetItem(start_time);
        QTableWidgetItem* item3 = new QTableWidgetItem(quit_time);
        QTableWidgetItem* item4 = new QTableWidgetItem(att_ratio);
        ui->tbl->setItem(0, 0, item1);
        ui->tbl->setItem(0, 1, item2);
        ui->tbl->setItem(0, 2, item3);
        ui->tbl->setItem(0, 3, item4);
    }
}

RecordWindow::~RecordWindow()
{
    delete ui;
}
