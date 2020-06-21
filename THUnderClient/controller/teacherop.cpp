/*************************************************************************
[Filename]               teacherop.cpp
[Modules & purpose]      connect TeacherMainPage & Teacherclient
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/

#include "teacherop.h"
using namespace std;

/*************************************************************************
Name:       Teacherop
Function:   constructor
Params:     Teacherclient*(input)
Return val: N/A
Developer & date: 王文新, 2020/5
Modification log: 2020/6/20
*************************************************************************/
Teacherop::Teacherop(Teacherclient* teacherclient) {
    this->teacherclient = teacherclient;
    this->init_audio(QAudioDeviceInfo::defaultInputDevice());
    this->init_vid();
    CreateThread(nullptr, 0, this->receive_msg, (LPVOID)this, 0, nullptr);
}

/*************************************************************************
Name:       ~Teacherop
Function:   deconstructor
Params:     None
Return val: N/A
Developer & date: 王文新, 2020/5
Modification log: 2020/6/20
*************************************************************************/
Teacherop::~Teacherop() {
    this->stop_audio();
}

/*************************************************************************
Name:       init_audio
Function:   initialize audio settings
Params:     QAudioDeviceInfo&(input)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
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
        format = deviceInfo.nearestFormat(format);
    }

    this->m_audioInput.reset(new QAudioInput(deviceInfo, format));
    this->m_audioOutput.reset(new QAudioOutput(deviceInfo, format));
    this->m_outputIOdevice = this->m_audioOutput->start();
}

/*************************************************************************
Name:       stop_audio
Function:   stop audio recording
Params:     None
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::stop_audio()
{
    this->m_audioInput->stop();
    this->m_audioOutput->stop();
}

/*************************************************************************
Name:       init_vid
Function:   initialize screen catching settings
Params:     None
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::init_vid()
{
    this->vid_timer = new QTimer();
    this->vid_timer->setInterval(200);
    connect(this->vid_timer, SIGNAL(timeout()), this, SLOT(grab_send_window()));
    this->cur_hwnd = (HWND) QApplication::desktop()->winId();
    this->screen = QApplication::primaryScreen();
}

/*************************************************************************
Name:       send_audiopiece
Function:   send audiopiece
Params:     string(input)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::send_audiopiece(string& audio) {
    this->teacherclient->send_audiopiece(audio);
}

/*************************************************************************
Name:       receive_msg
Function:   thread function, receive and process socket messages
Params:     LPVOID(input)
Return val: DWORD WINAPI
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
DWORD WINAPI Teacherop::receive_msg(LPVOID lpParameter) {
    Teacherop* cur = (Teacherop*) lpParameter;
    while (true) {
        string msg = cur->teacherclient->receive_msg();
        if (msg.empty() || msg.length() < 4) continue;
        string msg_head = msg.substr(0, 4);
        if (msg_head == AUDIO_MSG) {
            msg = msg.substr(4);
            QByteArray audio_piece = QByteArray::fromStdString(msg);
            cur->m_outputIOdevice->write(audio_piece);
        }
        else if (msg_head == CALLED_USERNAME) {
            msg = msg.substr(4);
            QString show_called_username = QString::fromStdString("Called: " + msg);
            emit cur->called_username(show_called_username);
        }
        else if (msg_head == ANS_PROB) {
            msg = msg.substr(4);
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

/*************************************************************************
Name:       broadcast_start
Function:   start recording
Params:     none
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::broadcast_start()
{
    this->m_inputIOdevice = this->m_audioInput->start();
    connect(m_inputIOdevice, SIGNAL(readyRead()),
            this, SLOT(get_audiodata_sent()));
    this->m_outputIOdevice = this->m_audioOutput->start();
}

/*************************************************************************
Name:       broadcast_end
Function:   end recording
Params:     none
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::broadcast_end()
{
    this->m_audioInput->stop();
}

/*************************************************************************
Name:       switch_audio
Function:   switch audio device
Params:     QAudioDeviceInfo(input)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::switch_audio(const QAudioDeviceInfo& new_info)
{
    this->m_audioInput->stop();
    this->m_audioInput->disconnect(this);

    this->init_audio(new_info);
}

/*************************************************************************
Name:       get_audiodata_sent
Function:   fetch the prepared audio data, and send it
Params:     none
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::get_audiodata_sent() {
    QByteArray data = this->m_inputIOdevice->read(1000);
    string data_str = data.toStdString();
    this->send_audiopiece(data_str);
}

/*************************************************************************
Name:       sharing_start
Function:   start sharing screen
Params:     none
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::sharing_start()
{
    this->vid_timer->start();
}

/*************************************************************************
Name:       sharing_stop
Function:   stop sharing screen
Params:     none
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::sharing_stop()
{
    this->vid_timer->stop();
}

/*************************************************************************
Name:       randcall
Function:   start a random roll call
Params:     none
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::randcall() {
    this->teacherclient->randcall();
}

/*************************************************************************
Name:       endcall
Function:   end the started random roll call
Params:     none
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::endcall() {
    this->teacherclient->endcall();
}

/*************************************************************************
Name:       send_prob
Function:   send a problem
Params:     string * 3(input)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::send_prob(string prob, string ans, string right_ans) {
    this->teacherclient->send_prob(prob, ans, right_ans);
}

/*************************************************************************
Name:       pull_prob
Function:   force stop receiving answers
Params:     none
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::pull_prob()
{
    teacherclient->pull_prob();
}

/*************************************************************************
Name:       get_window_title_list
Function:   get_window_title_list
Params:     vector<pair<QString, HWND> >&(output)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::get_window_title_list(vector<pair<QString, HWND> >& list)
{
    vector<pair<string, HWND> > stdlist;
    teacherclient->get_window_title_list(stdlist);
    for (int i = 0; i < stdlist.size(); i++) {
        list.push_back(make_pair(QString::fromStdString(stdlist[i].first), stdlist[i].second));
    }
}

/*************************************************************************
Name:       send_vid
Function:   send video data
Params:     QByteArray(input)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::send_vid(QByteArray& data)
{
    string msg = data.toStdString();
    teacherclient->send_vid(msg);
}

/*************************************************************************
Name:       add_record
Function:   add a piece of record
Params:     string * 4(input)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::add_record(const string& username, const string& start_time,
                           const string& quit_time, const string& att_ratio)
{
    teacherclient->add_record(username, start_time, quit_time, att_ratio);
}

/*************************************************************************
Name:       get_records
Function:   fetch all the records
Params:     vector<Record*>&(output)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::get_records(vector<Record*>& records)
{
    for (int i = 0; i < teacherclient->records.size(); i++) {
        Record* rec = teacherclient->records[i];
        records.push_back(rec);
    }
}

/*************************************************************************
Name:       grab_send_window
Function:   grab and send window once
Params:     none
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::grab_send_window()
{
    QByteArray data;
    QBuffer buffer(&data);
    QPixmap map = screen->grabWindow((WId)this->cur_hwnd);
    map = map.scaledToWidth(500);
    map.save(&buffer, "jpg", 10);
    this->send_vid(data);
}

/*************************************************************************
Name:       switch_window
Function:   switch the window to be shared
Params:     hwnd(input)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::switch_window(HWND hwnd)
{
    this->vid_timer->stop();
    this->cur_hwnd = hwnd;
}

/*************************************************************************
Name:       classover
Function:   classover
Params:     none
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherop::class_over()
{
    this->teacherclient->class_over();
}
