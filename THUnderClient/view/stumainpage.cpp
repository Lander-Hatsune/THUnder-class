#include "stumainpage.h"
#include "ui_stumainpage.h"
#include <windows.h>
#include <iostream>
using std::cout;
using std::endl;

StuMainPage::StuMainPage(QWidget *parent, Stuop* stuop) :
    QWidget(parent),
    ui(new Ui::StuMainPage)
{
    this->stuop = stuop;
    ui->setupUi(this);
    /*
    this->timer = new QTimer();
    this->timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(receive_msg()));
    timer->start();
    */
    this->init_window();
    this->init_audio(QAudioDeviceInfo::defaultInputDevice());
    this->is_muted = true;
    CreateThread(nullptr, 0, receive_msg, (LPVOID)this, 0, nullptr);
}

StuMainPage::~StuMainPage()
{
    delete ui;
    this->stop_audio();
}

void StuMainPage::init_audio(const QAudioDeviceInfo& deviceInfo)
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

    cout << "tryna set input and output" << endl;
    this->m_audioInput.reset(new QAudioInput(deviceInfo, format));
    this->m_audioOutput.reset(new QAudioOutput(deviceInfo, format));
    cout << "input and output set" << endl;
    this->m_outputIOdevice = this->m_audioOutput->start();
}

void StuMainPage::stop_audio()
{
    this->m_audioInput->stop();
    this->m_audioOutput->stop();
}

void StuMainPage::init_window()
{
    const QAudioDeviceInfo &default_deviceinfo =
            QAudioDeviceInfo::defaultInputDevice();
    ui->cb_audiodevice->addItem(default_deviceinfo.deviceName(),
                                QVariant::fromValue(default_deviceinfo));
    for (auto &deviceInfo: QAudioDeviceInfo::availableDevices(QAudio::AudioInput)) {
        if (deviceInfo != default_deviceinfo)
            ui->cb_audiodevice->addItem(deviceInfo.deviceName(),
                                        QVariant::fromValue(deviceInfo));
    }
}

void StuMainPage::on_cb_audiodevice_currentIndexChanged(int index)
{
    this->m_audioInput->stop();
    this->m_audioInput->disconnect(this);

    this->init_audio(ui->cb_audiodevice->itemData(index).value<QAudioDeviceInfo>());
}

void StuMainPage::get_audiodata_sent() {
    QByteArray data = this->m_inputIOdevice->read(1000); // 8000 * 16 * 4 byte/sec, 640 bytes / batch -> 1/800 sec

    string data_str = data.toStdString();
    for (int i = 0; i < data.length(); i++)
        if (data_str[i] == '\n')
            data_str[i] = '\n' + 1;
    cout << "write " << data_str.length() << endl;
    //cout << data_str << endl;
    //this->m_outputIOdevice->write(data);

    this->stuop->send_audiopiece(data_str);
}

DWORD WINAPI StuMainPage::receive_msg(LPVOID lpParameter)
{
    StuMainPage* cur = (StuMainPage*) lpParameter;
    while (true) {
        string msg = cur->stuop->receive_msg();
        if (msg.empty() || msg == "\n") continue;
        cout << "received msg" << endl;
        string msg_head = msg.substr(0, 4);
        if (msg_head == AUDIO_MSG) {
            cout << "audio message!" << msg.length() << endl;
            msg = msg.substr(0, msg.length() - 1);
            msg = msg.substr(4);
            QByteArray audio_piece = QByteArray::fromStdString(msg);
            cur->m_outputIOdevice->write(audio_piece);
        }
        else if (msg_head == AUDIO_OPEN) {
            cout << "called" << endl;
            cur->m_inputIOdevice = cur->m_audioInput->start();
            connect(cur->m_inputIOdevice, SIGNAL(readyRead()),
                    cur, SLOT(get_audiodata_sent()));
            cur->ui->lbl_is_muted->setText("You are now UNMUTED");
        }
        else if (msg_head == AUDIO_SHUT) {
            cout << "called over" << endl;
            cur->m_audioInput->suspend();
            cur->ui->lbl_is_muted->setText("You are muted");
        }
    }
}
