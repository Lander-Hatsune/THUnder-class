#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>
#include <string>
#include <QString>
#include "../controller/loginop.h"
#include "../controller/adminop.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginPage; }
QT_END_NAMESPACE

class LoginPage : public QMainWindow
{
    Q_OBJECT

public:
    LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

private slots:
    void on_b_login_clicked();

private:
    Loginop* loginop;
    Ui::LoginPage *ui;
};
#endif // LOGINPAGE_H
