#include "teachermainpage.h"
#include "ui_teachermainpage.h"
#include "recordwindow.h"
using namespace std;


TeacherMainPage::TeacherMainPage(QWidget *parent, Teacherop* teacherop) :
    QWidget(parent),
    ui(new Ui::TeacherMainPage)
{
    this->teacherop = teacherop;
    ui->setupUi(this);
    this->init_window();
    this->is_class_begin = false;

    this->screen_is_shared = false;

    this->window_title_list.push_back(make_pair("desktop", this->teacherop->cur_hwnd));

    connect(this->teacherop, SIGNAL(called_username(QString)), this, SLOT(show_called_username(QString)));
}

TeacherMainPage::~TeacherMainPage()
{
    delete ui;
}

void TeacherMainPage::on_b_togglestate_clicked()
{
    this->is_class_begin = !is_class_begin;
    if (is_class_begin) {
        ui->b_togglestate->setText("Class over");
        this->teacherop->broadcast_start();
    } else {
        this->teacherop->sharing_stop();
        this->teacherop->broadcast_end();
        this->hide();
        vector<Record*> records;
        teacherop->get_records(records);
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

void TeacherMainPage::on_cb_audiodevice_currentIndexChanged(int index)
{
    this->teacherop->switch_audio(ui->cb_audiodevice->itemData(index).value<QAudioDeviceInfo>());
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
    pushprobdialog->show();
}

void TeacherMainPage::on_b_sharescreen_clicked()
{
    this->screen_is_shared = !this->screen_is_shared;
    if (screen_is_shared) {
        ui->b_sharescreen->setText("Stop sharing");
        this->teacherop->sharing_start();
    } else {
        ui->b_sharescreen->setText("Share screen");
        this->teacherop->sharing_stop();
    }
}

void TeacherMainPage::on_cb_vidwindow_currentIndexChanged(int index)
{
    this->teacherop->switch_window(this->window_title_list[index].second);
    this->screen_is_shared = false;
    ui->b_sharescreen->setText("Share screen");
}

void TeacherMainPage::show_called_username(QString show_called_username)
{
    this->ui->lbl_called->setText(show_called_username);
}
