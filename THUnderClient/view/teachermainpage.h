#ifndef TEACHERMAINPAGE_H
#define TEACHERMAINPAGE_H

#include <QWidget>
#include <QAudioInput>
#include <QAudioOutput>
#include <QByteArray>
#include <windows.h>
#include <QTimer>
#include <QScreen>
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

signals:
    void answer_got(QString);

private slots:
    void on_b_togglestate_clicked();
    void on_cb_audiodevice_currentIndexChanged(int index);
    void get_audiodata_sent();
    void on_b_randcall_clicked();
    void on_b_pushprob_clicked();
    void grab_send_window();

    void on_b_sharescreen_clicked();

    void on_cb_vidwindow_currentIndexChanged(int index);

private:
    void init_window();
    void init_audio(const QAudioDeviceInfo&);
    void stop_audio();

    Teacherop* teacherop;
    Ui::TeacherMainPage *ui;
    bool is_class_begin;
    QScopedPointer<QAudioInput> m_audioInput;
    QScopedPointer<QAudioOutput> m_audioOutput;
    QIODevice* m_inputIOdevice;
    QIODevice* m_outputIOdevice;
    static DWORD WINAPI receive_msg(LPVOID lpParameter);

    QTimer* vid_timer;
    vector<pair<QString, HWND> > window_title_list;
    HWND cur_hwnd;
    bool screen_is_shared;
    QScreen* screen;
};



#endif // TEACHERMAINPAGE_H
