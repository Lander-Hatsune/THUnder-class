#include "teacherclient.h"
#include <iostream>
#include <windows.h>
using namespace std;

vector<pair<string, HWND> > _window_list;

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
    /*
    for (int i = 0; i < prob.length(); i++) {
        if (prob[i] == '\n') prob[i] = ' ';
    }
    */
    this->sock.SendLine(PUSH_PROB + prob + ":" + ans + ":" + r_ans);
}

void Teacherclient::pull_prob()
{
    cout << "pull" << endl;
    sock.SendLine(PULL_PROB);
}


void Teacherclient::get_window_title_list(vector<pair<string, HWND> >& list)
{
    EnumWindows(enum_window_callback, 0);
    for (int i = 0; i < _window_list.size(); i++) {
        list.push_back(_window_list[i]);
    }
    printf("windows done\n");
}

WINBOOL Teacherclient::enum_window_callback(HWND hwnd, long long lparam)
{
    char buffer[128];
    GetWindowTextA(hwnd, (LPSTR)buffer, 120);
    string name = buffer;
    cout << name << endl;
    if (name.empty()) return true;
    _window_list.push_back(make_pair(name, hwnd));
    return true;
}



void Teacherclient::send_vid(string& msg)
{
    printf("sent vid %d\n", msg.length());
    sock.SendLine(VID_MSG + msg);
}

void Teacherclient::add_record(const string& username, const string& start_time,
                               const string& quit_time, const string& att_ratio)
{
    Record* rec = new Record(username, start_time, quit_time, att_ratio);
    this->records.push_back(rec);
}
