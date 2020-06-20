/*************************************************************************
[Filename]               stuop.h
[Modules & purpose]      connect StuMainPage & Stuclient
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/

#pragma once
#include "../definitions.h"
#include "../model/stuclient.h"
#include <QAudioInput>
#include <QAudioOutput>
#include <QByteArray>
#include <QString>
#include <windows.h>
#include <QTimer>
#include <QImage>
#include <QPixmap>

/*************************************************************************
[Class Name]        Stuop
[Function]          the controller between StuMainPage and Stuclient
[Interfaces]        
- init_audio: initialize audio settings
- stop_audio: stop recording & sending
- receive_msg: thread function
- constructor Stuop: copy the Stuclient* param
- deconstructor ~Stu:
- send_audio_piece: pass one piece of audio to Stuclient
- send_ans: pass the answer to the Stuclient
- switch_audio_device: switch audio device
[Developer & date] 王文新, 2020/5
[Modification log] None
*************************************************************************/
class Stuop: public QObject {
    Q_OBJECT
private:
    Stuclient* stuclient;
    void init_audio(const QAudioDeviceInfo&);
    void stop_audio();
    QScopedPointer<QAudioInput> m_audioInput;
    QScopedPointer<QAudioOutput> m_audioOutput;
    QIODevice* m_inputIOdevice;
    QIODevice* m_outputIOdevice;
    static DWORD WINAPI receive_msg(LPVOID lpParameter);
    QTimer* att_timer;

signals:
    void ansprob(QString);
    void is_muted(bool);
    void pullprob();
    void new_frame(QByteArray);
    void get_attention(bool*);

private slots:
    void get_audiodata_sent();
    void send_attention();

public:
    Stuop(Stuclient*);
    ~Stuop();
    Stuop& operator = (const Stuop&) = delete;
    Stuop(const Stuop&) = delete;
    void send_audiopiece(string&);
    void send_ans(const string&, const unsigned&);

    void switch_audio_device(QAudioDeviceInfo);
};
