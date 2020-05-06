#ifndef ADMINMAINPAGE_H
#define ADMINMAINPAGE_H

#include <QWidget>
#include "../model/client.h"
#include "../controller/adminop.h"

namespace Ui {
class AdminMainPage;
}

class AdminMainPage : public QWidget
{
    Q_OBJECT

public:
    explicit AdminMainPage(QWidget *parent = nullptr, const Adminop*);
    ~AdminMainPage();

private:
    Ui::AdminMainPage *ui;
    const Adminop* op;
};

#endif // ADMINMAINPAGE_H
