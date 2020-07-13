#ifndef TEACHERMAINPAGE_H
#define TEACHERMAINPAGE_H

#include <QWidget>
#include <QAudioInput>
#include <QAudioOutput>
#include <QByteArray>
#include <windows.h>
#include <QTimer>
#include <QScreen>
#include <string>
#include <QString>
#include <QApplication>
#include <QDesktopWidget>
#include <QDateTime>
#include <QBuffer>
#include <vector>
#include "pushprobdialog.h"
#include "../controller/teacherop.h"

namespace Ui {
class TeacherMainPage;
}

class TeacherMainPage : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherMainPage(QWidget *parent = nullptr,
                             Teacherop* teacherop = nullptr);
    ~TeacherMainPage();


private slots:
    void on_b_togglestate_clicked();
    void on_cb_audiodevice_currentIndexChanged(int index);
    void on_b_randcall_clicked();
    void on_b_pushprob_clicked();

    void on_b_sharescreen_clicked();

    void on_cb_vidwindow_currentIndexChanged(int index);


    void show_called_username(QString);

private:
    void init_window();


    Teacherop* teacherop;
    Ui::TeacherMainPage *ui;
    bool is_class_begin;


    vector<pair<QString, HWND> > window_title_list;

    bool screen_is_shared;

};



#endif // TEACHERMAINPAGE_H
