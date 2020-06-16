#include "stuop.h"

Stuop::Stuop(Stuclient* stuclient) {
    this->stuclient = stuclient;
}

Stuop::~Stuop() {;}

void Stuop::send_audiopiece(string& audio) {
    this->stuclient->send_audiopiece(audio);
}

string Stuop::receive_msg() {
    return this->stuclient->receive_msg();
}
