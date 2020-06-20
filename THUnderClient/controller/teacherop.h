#pragma once
#include <QByteArray>
#include <vector>
#include "../definitions.h"
#include "../model/teacherclient.h"
#include <windows.h>
#include <QAudioInput>
#include <QAudioOutput>
#include <QByteArray>
#include <QScreen>
using namespace std;

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
};
