#include "stuclient.h"
#include <iostream>
using namespace std;

Stuclient::Stuclient(Client* clt): Client(*clt) {
    delete clt;
}

Stuclient::~Stuclient() {;}

string Stuclient::receive_msg() {
    return this->sock.ReceiveLine();
}

void Stuclient::send_ans(const string& ans, const unsigned& time)
{
    this->sock.SendLine(ANS_PROB + ans + ":" + to_string(time));
}

void Stuclient::send_attention(bool activated)
{
    this->sock.SendLine(ATTENTION + to_string(activated));
}

void Stuclient::send_audiopiece(string& audio) {
    //cout << "send: " << AUDIO_MSG + audio << endl;
    cout << "send audio: " << (AUDIO_MSG + audio).length() << endl;
    this->sock.SendLine(AUDIO_MSG + audio);
}
