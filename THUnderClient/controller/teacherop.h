/*************************************************************************
[Filename]               teacherop.h
[Modules & purpose]      connect TeacherMainPage & Teacherclient
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/
#pragma once
#include <QByteArray>
#include <vector>
#include "../definitions.h"
#include "../model/teacherclient.h"
#include <windows.h>
#include <QAudioInput>
#include <QAudioOutput>
#include <QScreen>
#include <QString>
#include <QDateTime>
#include <QTimer>
#include <QApplication>
#include <QDesktopWidget>
#include <QBuffer>
using namespace std;

/*************************************************************************
[Class Name]        Teacherop
[Function]          the controller between TeacherMainPage and Teacherclient
[Interfaces]        
- init_audio: initialize audio settings
- stop_audio: stop recording & sending
- receive_msg: thread function
- constructor Teacherop: copy the Stuclient* param
- deconstructor ~Teacherop:
- send_audio_piece: pass one piece of audio to Teacherclient
- switch_audio_device: switch audio device
- rand_call: start a random roll call
- end_call: stop the started random roll call
- send_prob: send the problem
- pull_prob: force pull the problem, stop receiving answers
- get_window_title_list: get all the windows' titles into the vector
- add_record: add a new record
- get_records: get all records
- broadcast_start: start audio broadcasting
- broadcast_end: stop audio broadcasting
- sharing_start: start screen sharing
- sharing_stop: stop screen sharing
- switch_window: switch the shared window
[Developer & date] 王文新, 2020/5
[Modification log] 2020/6/20
*************************************************************************/
class Teacherop: public QObject {
    Q_OBJECT
private:
    Teacherclient* teacherclient;
    static DWORD WINAPI receive_msg(LPVOID lpParameter);
    void send_audiopiece(string&);
    void init_audio(const QAudioDeviceInfo&);
    void stop_audio();
    QScopedPointer<QAudioInput> m_audioInput;
    QScopedPointer<QAudioOutput> m_audioOutput;
    QIODevice* m_inputIOdevice;
    QIODevice* m_outputIOdevice;
    void init_vid();
    void send_vid(QByteArray&);
    QScreen* screen;
    QTimer* vid_timer;

signals:
    void called_username(QString);
    void ans_got(QString);
    
private slots:
    void get_audiodata_sent();
    void grab_send_window();

public:
    Teacherop(Teacherclient*);
    ~Teacherop();
    Teacherop(const Teacherop&) = delete;
    Teacherop& operator = (const Teacherop&) = delete;

    void randcall();
    void endcall();
    void send_prob(string, string, string);
    void pull_prob();

    void get_window_title_list(vector<pair<QString, HWND> >&);

    void add_record(const string&, const string&,
                    const string&, const string&);
    void get_records(vector<Record*>&);
    void broadcast_start();
    void broadcast_end();
    void switch_audio(const QAudioDeviceInfo&);

    HWND cur_hwnd;
    void sharing_start();
    void sharing_stop();
    void switch_window(HWND hwnd);

    void class_over();
};
