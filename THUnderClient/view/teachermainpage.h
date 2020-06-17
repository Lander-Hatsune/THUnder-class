#ifndef TEACHERMAINPAGE_H
#define TEACHERMAINPAGE_H

#include <QWidget>
#include <QAudioInput>
#include <QAudioOutput>
#include <QByteArray>
#include <windows.h>
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
    void get_audiodata_sent();

    void on_b_randcall_clicked();

    void on_b_pushprob_clicked();

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
};

#endif // TEACHERMAINPAGE_H
