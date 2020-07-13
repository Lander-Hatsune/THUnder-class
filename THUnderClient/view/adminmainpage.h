#ifndef ADMINMAINPAGE_H
#define ADMINMAINPAGE_H

#include "../controller/adminop.h"
#include <QWidget>

namespace Ui {
class AdminMainPage;
}

class AdminMainPage : public QWidget
{
    Q_OBJECT

public:
    explicit AdminMainPage(QWidget *parent = nullptr,
                           Adminop* adminop = nullptr);
    ~AdminMainPage();

private slots:
    void on_b_add_clicked();

    void on_b_del_clicked();

    void on_b_change_clicked();

    void on_rb_changepswd_clicked();

    void on_rb_changeusername_clicked();

private:
    Ui::AdminMainPage *ui;
    Adminop* adminop;
};

#endif // ADMINMAINPAGE_H
