#include "teacherop.h"

Teacherop::Teacherop(Teacherclient* teacherclient) {
    this->teacherclient = teacherclient;
}

Teacherop::~Teacherop() {;}
    
void Teacherop::send_audiopiece(string& audio) {
    this->teacherclient->send_audiopiece(audio);
}
    
QByteArray Teacherop::receive_audiopiece() {
    string audio = this->teacherclient->receive_audiopiece();
    return QByteArray::fromStdString(audio);
}
