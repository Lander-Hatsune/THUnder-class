#ifndef STUMAINPAGE_H
#define STUMAINPAGE_H

#include <QWidget>
#include <QAudioInput>
#include <QAudioOutput>
#include <QByteArray>
#include <QString>
#include <windows.h>
#include <QTimer>
#include <QImage>
#include "ansprobwindow.h"
#include "../controller/stuop.h"

namespace Ui {
class StuMainPage;
}

class StuMainPage : public QWidget
{
    Q_OBJECT

public:
    explicit StuMainPage(QWidget *parent = nullptr, Stuop* stuop = nullptr);
    ~StuMainPage();



private slots:
    void on_cb_audiodevice_currentIndexChanged(int index);
    void new_ansprobwindow(QString msg);
    void get_attention(bool*);
    void is_muted_text(bool);
    void prob_pulled();
    void show_frame(QByteArray);
    void class_over();

private:
    void init_window();

    Ui::StuMainPage *ui;
    Stuop* stuop;

    bool is_muted;
    AnsProbWindow* ansprobwindow;
};

#endif // STUMAINPAGE_H
