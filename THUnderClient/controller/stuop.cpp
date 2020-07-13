/*************************************************************************
[Filename]               stuop.cpp
[Modules & purpose]      connect StuMainPage & Stuclient
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/
#include "stuop.h"
using namespace std;

/*************************************************************************
Name:       Stuop
Function:   constructor
Params:     Stuclient*(input)
Return val: N/A
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
Stuop::Stuop(Stuclient* stuclient) {
    this->stuclient = stuclient;
    this->att_timer = new QTimer();
    this->att_timer->setInterval(1000);
    connect(att_timer, SIGNAL(timeout()), this, SLOT(send_attention()));
    att_timer->start();

    this->init_audio(QAudioDeviceInfo::defaultInputDevice());
    CreateThread(nullptr, 0, receive_msg, (LPVOID)this, 0, nullptr);
}

/*************************************************************************
Name:       ~Stuop
Function:   deconstructor
Params:     None
Return val: N/A
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
Stuop::~Stuop() {
    stop_audio();
}

/*************************************************************************
Name:       init_audio
Function:   initialize audio settings
Params:     QAudioDeviceInfo&(input)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Stuop::init_audio(const QAudioDeviceInfo& deviceInfo)
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
Params:     none
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Stuop::stop_audio()
{
    this->m_audioInput->stop();
    this->m_audioOutput->stop();
}

/*************************************************************************
Name:       send_audiopiece
Function:   send audio piece
Params:     string&(input)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Stuop::send_audiopiece(string& audio) {
    this->stuclient->send_audiopiece(audio);
}

/*************************************************************************
Name:       send_ans
Function:   send the answer
Params:     string&(input), unsigned&(input)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Stuop::send_ans(const std::string& ans, const unsigned& time)
{
    this->stuclient->send_ans(ans, time);
}

/*************************************************************************
Name:       send_attention
Function:   send attention data
Params:     void
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Stuop::send_attention()
{
    bool activated;
    emit get_attention(&activated);
    stuclient->send_attention(activated);
}

/*************************************************************************
Name:       switch audio device
Function:   
Params:     QAudioDeviceInfo
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Stuop::switch_audio_device(QAudioDeviceInfo new_info)
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
void Stuop::get_audiodata_sent() {
    QByteArray data = this->m_inputIOdevice->read(1000);

    string data_str = data.toStdString();

    this->send_audiopiece(data_str);
}

/*************************************************************************
Name:       receive_msg
Function:   thread function, receive and process socket messages
Params:     LPVOID(input)
Return val: DWORD WINAPI
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
DWORD WINAPI Stuop::receive_msg(LPVOID lpParameter)
{
    Stuop* cur = (Stuop*) lpParameter;
    while (true) {
        string msg = cur->stuclient->receive_msg();
        if (msg.empty() || msg.length() < 4) continue;
        string msg_head = msg.substr(0, 4);
        if (msg_head == AUDIO_MSG) {
            msg = msg.substr(4);
            QByteArray audio_piece = QByteArray::fromStdString(msg);
            cur->m_outputIOdevice->write(audio_piece);
        }
        else if (msg_head == AUDIO_OPEN) {
            cur->m_inputIOdevice = cur->m_audioInput->start();
            connect(cur->m_inputIOdevice, SIGNAL(readyRead()),
                    cur, SLOT(get_audiodata_sent()));
            emit cur->is_muted(false);

        }
        else if (msg_head == AUDIO_SHUT) {
            cur->m_audioInput->suspend();
            emit cur->is_muted(true);
        }
        else if (msg_head == PUSH_PROB) {
            msg = msg.substr(4);
            emit cur->ansprob(QString::fromStdString(msg));
        }
        else if (msg_head == PULL_PROB) {
            emit cur->pullprob();
        }
        else if (msg_head == VID_MSG) {
            msg = msg.substr(4);
            QByteArray data = QByteArray::fromStdString(msg);
            emit cur->new_frame(data);
        }
        else if (msg_head == CLASS_OVER) {
            emit cur->class_over();
        }
    }
}
