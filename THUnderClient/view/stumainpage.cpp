#include "stumainpage.h"
#include "ui_stumainpage.h"

StuMainPage::StuMainPage(QWidget *parent, Stuop* stuop) :
    QWidget(parent),
    ui(new Ui::StuMainPage)
{
    this->stuop = stuop;
    ui->setupUi(this);
    this->init_window();

    this->is_muted = true;
    connect(stuop, SIGNAL(ansprob(QString)), this, SLOT(new_ansprobwindow(QString)));
    connect(stuop, SIGNAL(is_muted(bool)), this, SLOT(is_muted_text(bool)));
    connect(stuop, SIGNAL(new_frame(QByteArray)), this, SLOT(show_frame(QByteArray)));
    connect(stuop, SIGNAL(get_attention(bool*)), this, SLOT(get_attention(bool*)));
    connect(stuop, SIGNAL(class_over()), this, SLOT(class_over()));
    this->ansprobwindow = nullptr;
}

StuMainPage::~StuMainPage()
{
    delete ui;
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
    stuop->switch_audio_device(ui->cb_audiodevice->itemData(index).value<QAudioDeviceInfo>());
}

void StuMainPage::new_ansprobwindow(QString msg)
{
    this->ansprobwindow = new AnsProbWindow(nullptr, this->stuop, msg.toStdString());
    ansprobwindow->setWindowTitle("Answer problem (student mode (THUnder class))");
    ansprobwindow->show();
}

void StuMainPage::get_attention(bool* is_active)
{
    *is_active = this->isActiveWindow();
}

void StuMainPage::is_muted_text(bool is_muted)
{
    if (!is_muted)
        ui->lbl_is_muted->setText("You are now UNMUTED");
    else
        ui->lbl_is_muted->setText("You are muted");
}

void StuMainPage::prob_pulled()
{
    if (ansprobwindow)
        ansprobwindow->close();
}

void StuMainPage::show_frame(QByteArray data)
{
    QImage* img = new QImage();
    img->loadFromData(data);
    QImage image = *img;
    image = image.scaled(1121, 691);
    ui->lbl_vid->setPixmap(QPixmap::fromImage(image));
}

void StuMainPage::class_over()
{
    this->close();
}




