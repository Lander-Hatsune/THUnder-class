#ifndef PUSHPROBDIALOG_H
#define PUSHPROBDIALOG_H

#include <QDialog>
#include "../controller/teacherop.h"

namespace Ui {
class PushProbDialog;
}

class PushProbDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PushProbDialog(QWidget *parent = nullptr, Teacherop* teacherop = nullptr);
    ~PushProbDialog();

private slots:
    void on_b_push_clicked();

private:
    Ui::PushProbDialog *ui;
    Teacherop* teacherop;
    static DWORD WINAPI receive_msg(LPVOID lpParameter);
};

#endif // PUSHPROBDIALOG_H
