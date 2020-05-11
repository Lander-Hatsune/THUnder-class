#include "teachermainpage.h"
#include "ui_teachermainpage.h"

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

TeacherMainPage::TeacherMainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherMainPage)
{
    ui->setupUi(this);
    this->init_window();
    this->init_rec(QAudioDeviceInfo::defaultInputDevice());
    this->is_class_begin = false;
}

TeacherMainPage::~TeacherMainPage()
{
    delete ui;
    this->stop_rec();
}

void TeacherMainPage::on_b_togglestate_clicked()
{
    this->is_class_begin = !is_class_begin;
    if (is_class_begin) {
        this->m_inputIOdevice = this->m_audioInput->start();
        connect(m_inputIOdevice, SIGNAL(readyRead()),
                this, SLOT(capture_audiodata()));
        this->m_outputIOdevice = this->m_audioOutput->start();
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

void TeacherMainPage::init_rec(const QAudioDeviceInfo& deviceInfo)
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
}

void TeacherMainPage::stop_rec()
{
    this->m_audioInput->stop();
    this->m_audioOutput->stop();
}



void TeacherMainPage::on_cb_audiodevice_currentIndexChanged(int index)
{
    this->m_audioInput->stop();
    this->m_audioInput->disconnect(this);

    this->init_rec(ui->cb_audiodevice->itemData(index).value<QAudioDeviceInfo>());
}

void TeacherMainPage::get_audiodata_sent() {
    QByteArray data = this->m_inputIOdevice->read(8000 * 1 * 16 / 50);
    string data_str = data.toStdString();
    this->teacherop->send_audiopiece(data_str);
}
