#include "teachermainpage.h"
#include "ui_teachermainpage.h"

#include <string>
#include <QString>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

TeacherMainPage::TeacherMainPage(QWidget *parent, Teacherop* teacherop) :
    QWidget(parent),
    ui(new Ui::TeacherMainPage)
{
    this->teacherop = teacherop;
    ui->setupUi(this);
    this->init_window();
    this->init_audio(QAudioDeviceInfo::defaultInputDevice());
    this->is_class_begin = false;
    CreateThread(nullptr, 0, receive_msg, (LPVOID)this, 0, nullptr);
}

TeacherMainPage::~TeacherMainPage()
{
    delete ui;
    this->stop_audio();
}

void TeacherMainPage::on_b_togglestate_clicked()
{
    this->is_class_begin = !is_class_begin;
    if (is_class_begin) {
        ui->b_togglestate->setText("Class over");
        this->m_inputIOdevice = this->m_audioInput->start();
        connect(m_inputIOdevice, SIGNAL(readyRead()),
                this, SLOT(get_audiodata_sent()));
        this->m_outputIOdevice = this->m_audioOutput->start();
    } else {
        ui->b_togglestate->setText("Class begin");
        this->m_audioInput->suspend();
    }
}

void TeacherMainPage::init_window()
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

void TeacherMainPage::init_audio(const QAudioDeviceInfo& deviceInfo)
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

void TeacherMainPage::stop_audio()
{
    this->m_audioInput->stop();
    this->m_audioOutput->stop();
}



void TeacherMainPage::on_cb_audiodevice_currentIndexChanged(int index)
{
    this->m_audioInput->stop();
    this->m_audioInput->disconnect(this);

    this->init_audio(ui->cb_audiodevice->itemData(index).value<QAudioDeviceInfo>());
}

void TeacherMainPage::get_audiodata_sent() {
    QByteArray data = this->m_inputIOdevice->read(1000);

    string data_str = data.toStdString();
    for (int i = 0; i < data.length(); i++)
        if (data_str[i] == '\n')
            data_str[i] = '\n' + 1;
    cout << "write " << data_str.length() << endl;
    //this->m_outputIOdevice->write(data); // echo
    this->teacherop->send_audiopiece(data_str);
}

DWORD WINAPI TeacherMainPage::receive_msg(LPVOID lpParameter)
{
    TeacherMainPage* cur = (TeacherMainPage*) lpParameter;
    while (true) {
        string msg = cur->teacherop->receive_msg();
        if (msg.empty() || msg == "\n") continue;
        string msg_head = msg.substr(0, 4);
        cout << "received msg, " << msg.length() << ", " << msg_head << endl;
        if (msg_head == AUDIO_MSG) {
            cout << "audio message!" << endl;
            msg = msg.substr(0, msg.length() - 1);
            msg = msg.substr(4);
            printf("sliced\n");
            QByteArray audio_piece = QByteArray::fromStdString(msg);
            printf("converted\n");
            cur->m_outputIOdevice->write(audio_piece);
            printf("played\n");
        }
        else if (msg_head == CALLED_USERNAME) {
            msg = msg.substr(0, msg.length() - 1);
            msg = msg.substr(4);
            QString show_called_username = QString::fromStdString("Called: " + msg);
            cur->ui->lbl_called->setText(show_called_username);
        }
        else if (msg_head == ANS_PROB) {
            msg = msg.substr(4);
            msg = msg.substr(0, msg.length() - 1);
            printf("got answer, emit\n");
            cout << msg << endl;
            emit cur->answer_got(QString::fromStdString(msg));
        }
    }
}

void TeacherMainPage::on_b_randcall_clicked()
{
    if (ui->b_randcall->text() == "Random roll call") {
        this->teacherop->randcall();
        ui->b_randcall->setText("End this call");
    }
    else {
        this->teacherop->endcall();
        ui->lbl_called->setText("");
        ui->b_randcall->setText("Random roll call");
    }
}


void TeacherMainPage::on_b_pushprob_clicked()
{
    PushProbDialog* pushprobdialog = new PushProbDialog(nullptr, this->teacherop);
    pushprobdialog->setWindowTitle("Push problem (teacher mode (THUnder class))");
    // pushprobdialog->setWindowFlag(Qt::WindowStaysOnTopHint);
    pushprobdialog->show();
    connect(this, SIGNAL(answer_got(QString)), pushprobdialog, SLOT(refresh_tables(QString)));
}
