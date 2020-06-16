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

void Stuclient::send_audiopiece(string& audio) {
    //cout << "send: " << AUDIO_MSG + audio << endl;
    cout << "send audio: " << (AUDIO_MSG + audio).length() << endl;
    this->sock.SendLine(AUDIO_MSG + audio);
}
