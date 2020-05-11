#include "teacherclient.h"

Teacherclient::Teacherclient(Client* clt): Client(*clt) {
    delete clt;
}

Teacherclient::~Teacherclient() {;}

void Teacherclient::send_audiopiece(string& audio) {
    this->audiosock.SendLine(audio);
}

string Teacherclient::receive_audiopiece() {
    string audio = this->audiosock.ReceiveLine();
    audio = audio.substr(0, audio.length() - 1);
    return audio;
}
