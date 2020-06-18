#include "teacherclient.h"
#include <iostream>
using namespace std;
Teacherclient::Teacherclient(Client* clt): Client(*clt) {
    delete clt;
}

Teacherclient::~Teacherclient() {;}

void Teacherclient::send_audiopiece(string& audio) {
    cout << "send audio: " << (AUDIO_MSG + audio).length() << endl;
    this->sock.SendLine(AUDIO_MSG + audio);
}

string Teacherclient::receive_msg() {
    return this->sock.ReceiveLine();
}

void Teacherclient::randcall() {
    this->sock.SendLine(RAND_CALL);
}

void Teacherclient::endcall() {
    this->sock.SendLine(RAND_CALL_OVER);
}

void Teacherclient::send_prob(string prob, string ans, string r_ans) {
    cout << "sent: " << PUSH_PROB + prob + ":" + ans + ":" + r_ans;
    for (int i = 0; i < prob.length(); i++) {
        if (prob[i] == '\n') prob[i] = ' ';
    }
    this->sock.SendLine(PUSH_PROB + prob + ":" + ans + ":" + r_ans);
}

void Teacherclient::pull_prob()
{
    cout << "pull" << endl;
    sock.SendLine(PULL_PROB);
}
