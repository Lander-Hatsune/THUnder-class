#include "teacherop.h"

Teacherop::Teacherop(Teacherclient* teacherclient) {
    this->teacherclient = teacherclient;
}

Teacherop::~Teacherop() {;}
    
void Teacherop::send_audiopiece(string& audio) {
    this->teacherclient->send_audiopiece(audio);
}

string Teacherop::receive_msg() {
    return this->teacherclient->receive_msg();
}

void Teacherop::randcall() {
    this->teacherclient->randcall();
}

void Teacherop::endcall() {
    this->teacherclient->endcall();
}
