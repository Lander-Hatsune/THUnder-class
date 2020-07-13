#ifndef ANSPROBWINDOW_H
#define ANSPROBWINDOW_H

#include <QWidget>
#include <QDateTime>
#include "../controller/stuop.h"

namespace Ui {
class AnsProbWindow;
}

class AnsProbWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AnsProbWindow(QWidget *parent = nullptr, Stuop* stuop = nullptr,
                           string msg = "");
    ~AnsProbWindow();

private slots:
    void on_b_send_clicked();

private:
    Ui::AnsProbWindow *ui;
    Stuop* stuop;
    qint64 start_time;
};

#endif // ANSPROBWINDOW_H
