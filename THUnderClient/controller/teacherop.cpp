#include "teacherop.h"
#include <vector>
#include <QString>
#include <QDateTime>
#include <iostream>
#include <QTimer>
#include <QApplication>
#include <QDesktopWidget>
#include <QBuffer>
using namespace std;

Teacherop::Teacherop(Teacherclient* teacherclient) {
    this->teacherclient = teacherclient;
    this->init_audio(QAudioDeviceInfo::defaultInputDevice());
    this->init_vid();
    CreateThread(nullptr, 0, this->receive_msg, (LPVOID)this, 0, nullptr);
}

Teacherop::~Teacherop() {
    this->stop_audio();
}
    
void Teacherop::init_audio(const QAudioDeviceInfo& deviceInfo)
{
    QAudioFormat format;
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::SignedInt);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setCodec("audio/pcm");

    if (!deviceInfo.isFormatSupported(format)) {
        cout << "Default format not supported - trying to use nearest";
        format = deviceInfo.nearestFormat(format);
    }

    cout << "tryna set audio input and output" << endl;
    this->m_audioInput.reset(new QAudioInput(deviceInfo, format));
    this->m_audioOutput.reset(new QAudioOutput(deviceInfo, format));
    cout << "input and output set" << endl;
    this->m_outputIOdevice = this->m_audioOutput->start();
}

void Teacherop::stop_audio()
{
    this->m_audioInput->stop();
    this->m_audioOutput->stop();
}

void Teacherop::init_vid()
{
    this->vid_timer = new QTimer();
    this->vid_timer->setInterval(200);
    connect(this->vid_timer, SIGNAL(timeout()), this, SLOT(grab_send_window()));
    this->cur_hwnd = (HWND) QApplication::desktop()->winId();
    this->screen = QApplication::primaryScreen();
}

void Teacherop::send_audiopiece(string& audio) {
    this->teacherclient->send_audiopiece(audio);
}

DWORD WINAPI Teacherop::receive_msg(LPVOID lpParameter) {
    Teacherop* cur = (Teacherop*) lpParameter;
    while (true) {
        string msg = cur->teacherclient->receive_msg();
        if (msg.empty() || msg.length() < 4) continue;
        string msg_head = msg.substr(0, 4);
        cout << "received msg, " << msg.length() << ", " << msg_head << endl;
        if (msg_head == AUDIO_MSG) {
            cout << "audio message!" << endl;
            msg = msg.substr(4);
            printf("sliced\n");
            QByteArray audio_piece = QByteArray::fromStdString(msg);
            printf("converted\n");
            cur->m_outputIOdevice->write(audio_piece);
            printf("played\n");
        }
        else if (msg_head == CALLED_USERNAME) {
            msg = msg.substr(4);
            QString show_called_username = QString::fromStdString("Called: " + msg);
            emit cur->called_username(show_called_username);
        }
        else if (msg_head == ANS_PROB) {
            msg = msg.substr(4);
            printf("got answer, emit\n");
            cout << msg << endl;
            emit cur->ans_got(QString::fromStdString(msg));
        }
        else if (msg_head == ATT_DATA) {
            msg = msg.substr(4);

            unsigned div = msg.find(':');
            string username = msg.substr(0, div);
            msg = msg.substr(div + 1);

            div = msg.find(':');
            quint32 enter_time = atoi(msg.substr(0, div).c_str());
            string str_enter = QDateTime::fromSecsSinceEpoch(enter_time).toString().toStdString();
            msg = msg.substr(div + 1);

            div = msg.find(':');
            quint32 quit_time = atoi(msg.substr(0, div).c_str());
            string str_quit = QDateTime::fromSecsSinceEpoch(quit_time).toString().toStdString();
            msg = msg.substr(div + 1);

            string ratio = msg;

            cur->add_record(username, str_enter, str_quit, ratio);
        }
    }
}

void Teacherop::broadcast_start()
{
    this->m_inputIOdevice = this->m_audioInput->start();
    connect(m_inputIOdevice, SIGNAL(readyRead()),
            this, SLOT(get_audiodata_sent()));
    this->m_outputIOdevice = this->m_audioOutput->start();
}

void Teacherop::broadcast_end()
{
    this->m_audioInput->stop();
}

void Teacherop::switch_audio(const QAudioDeviceInfo& new_info)
{
    this->m_audioInput->stop();
    this->m_audioInput->disconnect(this);

    this->init_audio(new_info);
}

void Teacherop::get_audiodata_sent() {
    QByteArray data = this->m_inputIOdevice->read(1000);
    string data_str = data.toStdString();
    cout << "write " << data_str.length() << endl;
    this->send_audiopiece(data_str);
}

void Teacherop::sharing_start()
{
    printf("sharing start\n");

    this->vid_timer->start();
}

void Teacherop::sharing_stop()
{
    this->vid_timer->stop();
}

void Teacherop::randcall() {
    this->teacherclient->randcall();
}

void Teacherop::endcall() {
    this->teacherclient->endcall();
}

void Teacherop::send_prob(string prob, string ans, string right_ans) {
    this->teacherclient->send_prob(prob, ans, right_ans);
}

void Teacherop::pull_prob()
{
    teacherclient->pull_prob();
}

void Teacherop::get_window_title_list(vector<pair<QString, HWND> >& list)
{
    vector<pair<string, HWND> > stdlist;
    teacherclient->get_window_title_list(stdlist);
    for (int i = 0; i < stdlist.size(); i++) {
        list.push_back(make_pair(QString::fromStdString(stdlist[i].first), stdlist[i].second));
    }
}

void Teacherop::send_vid(QByteArray& data)
{
    string msg = data.toStdString();
    teacherclient->send_vid(msg);
}

void Teacherop::add_record(const string& username, const string& start_time,
                           const string& quit_time, const string& att_ratio)
{
    teacherclient->add_record(username, start_time, quit_time, att_ratio);
}

void Teacherop::get_records(vector<Record*>& records)
{
    for (int i = 0; i < teacherclient->records.size(); i++) {
        Record* rec = teacherclient->records[i];
        records.push_back(rec);
    }
    printf("get_records: records size: %d\n", records.size());
}

void Teacherop::grab_send_window()
{
    QByteArray data;
    QBuffer buffer(&data);
    QPixmap map = screen->grabWindow((WId)this->cur_hwnd);
    map = map.scaledToWidth(500);
    map.save(&buffer, "jpg", 10);
    this->send_vid(data);
}

void Teacherop::switch_window(HWND hwnd)
{
    this->vid_timer->stop();
    this->cur_hwnd = hwnd;
}
