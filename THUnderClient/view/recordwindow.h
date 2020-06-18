#ifndef RECORDWINDOW_H
#define RECORDWINDOW_H

#include <QWidget>
#include "../model/record.h"

namespace Ui {
class RecordWindow;
}

class RecordWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RecordWindow(QWidget *parent = nullptr,
                          vector<Record*> records = vector<Record*>());
    ~RecordWindow();

private:
    Ui::RecordWindow *ui;
};

#endif // RECORDWINDOW_H
