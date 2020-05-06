#include "adminop.h"

Adminop::Adminop(const Client* clt) {
    this->clt = clt;
}

Adminop::~Adminop() {;}

void Adminop::add_client(const string& username,
                         const string& pswd) const {
    if (username.find(':') != -1ull ||
        pswd.find(':') != -1ull) {
        // text: cannot contain colon!
        return;
    }
    this->clt->sock.SendLine(ADD_CLIENT + username + ":" + pswd);
    string fb = this->clt.sock.ReceiveLine();
    if ((fb[0] - '0') == VALID) {
        // text: done!
    } else {
        // text: username repeated!
    }
}

void Adminop::del_client(const string& username) const {
    this->clt.sock.SendLine(DEL_CLIENT + username);
    string fb = this->clt.sock.ReceiveLine();
    if ((fb[0] - '0') == VALID) {
        // text: done!
    } else {
        // text: user doesnt exist!
    }
}

void Adminop::change_username(const string& username,
                              const string& new_username) const {
    this->clt.sock.SendLine(CHANGE_USERNAME +
                            username + ":" + new_username);
    string fb = this->clt.sock.ReceiveLine();
    if ((fb[0] - '0') == VALID) {
        // text: done!
    } else {
        // text: user doesnt exist!
    }
}

void Adminop::change_pswd(const string& username,
                          const string& new_pswd) const {
    this->clt.sock.SendLine(CHANGE_PSWD + username + ":" + new_pswd);
    string fb = this->clt.sock.ReceiveLine();
    if ((fb[0] - '0') == VALID) {
        // text: done!
    } else {
        // text: user doesnt exist!
    }
}
