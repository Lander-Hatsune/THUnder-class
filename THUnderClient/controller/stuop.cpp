#include "stuop.h"

Stuop::Stuop(Stuclient* stuclient) {
    this->stuclient = stuclient;
}

Stuop::~Stuop() {;}

void Stuop::send_audiopiece(string& audio) {
    this->stuclient->send_audiopiece(audio);
}

void Stuop::send_ans(const std::string& ans, const unsigned& time)
{
    this->stuclient->send_ans(ans, time);
}

void Stuop::send_attention(bool activated)
{
    stuclient->send_attention(activated);
}

string Stuop::receive_msg() {
    return this->stuclient->receive_msg();
}
