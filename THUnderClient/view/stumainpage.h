#ifndef STUMAINPAGE_H
#define STUMAINPAGE_H

#include <QWidget>
#include <QAudioInput>
#include <QAudioOutput>
#include <QByteArray>
#include <QString>
#include <windows.h>
#include "ansprobwindow.h"
#include "../controller/stuop.h"

namespace Ui {
class StuMainPage;
}

class StuMainPage : public QWidget
{
    Q_OBJECT

public:
    explicit StuMainPage(QWidget *parent = nullptr, Stuop* stuop = nullptr);
    ~StuMainPage();

signals:
    void ansprob(QString);

private slots:
    void get_audiodata_sent();
    void on_cb_audiodevice_currentIndexChanged(int index);
    void new_ansprobwindow(QString msg);

private:
    void init_window();
    void init_audio(const QAudioDeviceInfo&);
    void stop_audio();
    Ui::StuMainPage *ui;
    Stuop* stuop;
    QScopedPointer<QAudioInput> m_audioInput;
    QScopedPointer<QAudioOutput> m_audioOutput;
    QIODevice* m_inputIOdevice;
    QIODevice* m_outputIOdevice;
    static DWORD WINAPI receive_msg(LPVOID lpParameter);
    bool is_muted;
    AnsProbWindow* ansprobwindow;
};

#endif // STUMAINPAGE_H
