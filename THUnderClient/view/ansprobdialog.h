#ifndef ANSPROBDIALOG_H
#define ANSPROBDIALOG_H

#include <QDialog>
#include "../controller/stuop.h"

namespace Ui {
class AnsProbDialog;
}

class AnsProbDialog : public QDialog
{
    Q_OBJECT

    friend class StuMainPage;
public:
    explicit AnsProbDialog(QWidget *parent = nullptr,
                           Stuop* stuop = nullptr, string msg = "",
                           QWidget* stumainpage = nullptr);
    ~AnsProbDialog();

private slots:
    void on_b_send_clicked();

private:
    QWidget* stumainpage;
    Ui::AnsProbDialog *ui;
    Stuop* stuop;
    qint64 start_time;
    static DWORD WINAPI receive_msg(LPVOID lpParameter);
};

#endif // ANSPROBDIALOG_H
