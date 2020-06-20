#include "adminclient.h"
Adminclient::Adminclient(Client* clt): Client(*clt) {
    delete clt;
}

Adminclient::~Adminclient() {;}

unsigned Adminclient::add_client(const string& username,
                                 const string& pswd,
                                 const CLT_TYPE& type) {
    if (username.find(':') != -1ull ||
        pswd.find(':') != -1ull) {
        return 2;// illegal username or pswd
    }
    this->sock.SendLine(ADD_CLIENT + username + ":" +
                        pswd + ":" +
                        to_string(type));
    while (true) {
        string fb = this->sock.ReceiveLine();
        if (fb.empty()) continue;
        else return fb[0] - '0';// 1: username repeated
    }
}

unsigned Adminclient::del_client(const string& username) {
    if (username.find(':') != -1ull) {
        return 1;// user not found
    }
    this->sock.SendLine(DEL_CLIENT + username);
    while (true) {
        string fb = this->sock.ReceiveLine();
        if (fb.empty()) continue;
        return fb[0] - '0';// 1: user not found
    }
}

unsigned Adminclient::change_username(const string& username,
                                      const string& new_username) {
    if (username.find(':') != -1ull ||
        new_username.find(':') != -1ull) {
        return 3;// illegal username or new_username
    }
    this->sock.SendLine(CHANGE_USERNAME +
                        username + ":" + new_username);
    while (true) {
        string fb = this->sock.ReceiveLine();
        if (fb.empty()) continue;
        return fb[0] - '0';// 1: user not found, 2: new username exist
    }
}

unsigned Adminclient::change_pswd(const string& username,
                                  const string& new_pswd) {
    if (username.find(':') != -1ull ||
        new_pswd.find(':') != -1ull) {
        return 2;// illegal username or pswd
    }
    this->sock.SendLine(CHANGE_PSWD + username + ":" + new_pswd);
    while (true) {
        string fb = this->sock.ReceiveLine();
        if (fb.empty()) continue;
        return fb[0] - '0';// 1: user not found
    }
}
