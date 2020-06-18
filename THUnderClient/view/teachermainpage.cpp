#include "teachermainpage.h"
#include "ui_teachermainpage.h"
#include "recordwindow.h"

#include <string>
#include <QString>
#include <QApplication>
#include <QDesktopWidget>
#include <QDateTime>
#include <QBuffer>
#include <windows.h>
#include <vector>
#include <iostream>
using namespace std;


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

    this->screen_is_shared = false;
    this->vid_timer = new QTimer();
    this->vid_timer->setInterval(300);
    vid_timer->stop();

    connect(this->vid_timer, SIGNAL(timeout()), this, SLOT(grab_send_window()));
    printf("connect timer\n");
    this->cur_hwnd = (HWND) QApplication::desktop()->winId();
    printf("desktop id\n");
    this->window_title_list.push_back(make_pair("desktop", cur_hwnd));
    this->screen = QApplication::primaryScreen();
    printf("initialized\n");

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
        this->vid_timer->stop();
        ui->b_togglestate->setText("Class begin");
        this->m_audioInput->suspend();
        this->hide();
        vector<Record*> records;
        teacherop->get_records(records);
        printf("got records %d\n", records.size());
        RecordWindow* recordwindow = new RecordWindow(nullptr, records);
        recordwindow->show();
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

    this->teacherop->get_window_title_list(window_title_list);
    for (int i = 0; i < window_title_list.size(); i++) {
        ui->cb_vidwindow->addItem(window_title_list[i].first);
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

    cout << "tryna set audio input and output" << endl;
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
        else if (msg_head == ATT_DATA) {
            msg = msg.substr(4);
            msg = msg.substr(0, msg.length() - 1);

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

            cur->teacherop->add_record(username, str_enter, str_quit, ratio);
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



void TeacherMainPage::grab_send_window()
{
    QByteArray data;
    QBuffer buffer(&data);
    QPixmap map = screen->grabWindow((WId)this->cur_hwnd);
    map = map.scaledToWidth(500);
    map.save(&buffer, "bmp", 20);
    teacherop->send_vid(data);
}

void TeacherMainPage::on_b_sharescreen_clicked()
{
    this->screen_is_shared = !this->screen_is_shared;
    if (screen_is_shared) {
        ui->b_sharescreen->setText("Stop sharing");
        this->vid_timer->start();
    } else {
        ui->b_sharescreen->setText("Share screen");
        this->vid_timer->stop();
    }
}

void TeacherMainPage::on_cb_vidwindow_currentIndexChanged(int index)
{
    this->vid_timer->stop();
    this->cur_hwnd = this->window_title_list[index].second;
    this->screen_is_shared = false;
    ui->b_sharescreen->setText("Share screen");
}
