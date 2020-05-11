#ifndef STUMAINPAGE_H
#define STUMAINPAGE_H

#include <QWidget>

namespace Ui {
class StuMainPage;
}

class StuMainPage : public QWidget
{
    Q_OBJECT

public:
    explicit StuMainPage(QWidget *parent = nullptr);
    ~StuMainPage();

private:
    Ui::StuMainPage *ui;
};

#endif // STUMAINPAGE_H
