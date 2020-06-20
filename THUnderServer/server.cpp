#include "server.h"
#include <process.h>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<User*> Class_Members;

Server::Server(int port, int maxnum):
    SocketServer(port, maxnum) {
    ;
}
Server::~Server() {;}

void Server::accept() {
    Socket* s = this->Accept();
    unsigned ret;
    _beginthreadex(0, 0, this->Answer, (void*)s, 0, &ret);
}

unsigned __stdcall Server::Answer(void* x) {

    dboperator db = dboperator();
    srand(time(NULL));

    Socket* the_sock = (Socket*) x;

    string str;
    str = the_sock->ReceiveLine();
    cout << "received:" << str << endl;
    str = str.substr(4);
    unsigned divpos = str.rfind(":");

    string the_username = str.substr(0, divpos);
    string the_pswd = str.substr(divpos + 1);
    unsigned the_type =
        db.checktype(the_username.c_str(), the_pswd.c_str());
    unsigned the_number = Class_Members.size();

    printf("sent:%d\n", the_type);
    the_sock->SendLine(to_string(the_type));

    User* member = new User(the_username, the_pswd,
                            the_type, the_number, the_sock);
    printf("new member, type %d, or %d\n", the_type, *(member->type_w));
    if (the_type == 0) {
        delete member;
    }
    else if (the_type != 1) {
        printf("pushed into vector\n");
        Class_Members.push_back(member);
    }

    
    /*
    printf("check all members:\n");
    for (int i = 0; i < Class_Members.size(); i++) {
        if (Class_Members[i] == nullptr) {
            printf("number %d is offline\n", i);
        } else {
            cout << "number: " << *(Class_Members[i]->number_w) << ", ";
            cout << "username: " << *(Class_Members[i]->username_w) << ", ";
            cout << "type: " << *(Class_Members[i]->type_w) << endl;
        }
    }
    */

    unsigned the_enter_time = time(NULL);
    unsigned the_attention_bottom = 0;
    unsigned the_attention_top = 0;
    
    unsigned lastcalled = -1;    
    while (true) {
        string str = the_sock->ReceiveLine();
        printf("received %d: ", str.length());
        if (str.empty()) break;
        if (str.length() < 4) continue;
        
        //str = str.substr(0, str.length() - 1);
        string msghead = str.substr(0, 4);
        cout << msghead << endl;
        
        if (msghead == ADD_CLIENT) {
            str = str.substr(4);
            unsigned type = str[str.length() - 1] - '0';
            str = str.substr(0, str.length() - 2);
            unsigned divpos = str.rfind(":");
            string username = str.substr(0, divpos);
            string pswd = str.substr(divpos + 1);
            unsigned isvalid = db.add_client(username.c_str(),
                                             pswd.c_str(), type);
            printf("sent:%d\n", isvalid);
            the_sock->SendLine(to_string(isvalid));            
        }
        else if (msghead == DEL_CLIENT) {
            str = str.substr(4);
            string username = str;
            unsigned isvalid = db.del_client(username.c_str());
            printf("sent:%d\n", isvalid);
            the_sock->SendLine(to_string(isvalid));
        }
        else if (msghead == CHANGE_USERNAME) {
            str = str.substr(4);
            unsigned divpos = str.rfind(":");
            string username = str.substr(0, divpos);
            string new_username = str.substr(divpos + 1);
            unsigned ret = db.change_username(username.c_str(),
                                              new_username.c_str());
            printf("sent:%d\n", ret);
            the_sock->SendLine(to_string(ret));
        }
        else if (msghead == CHANGE_PSWD) {
            str = str.substr(4);
            unsigned divpos = str.rfind(":");
            string username = str.substr(0, divpos);
            string new_pswd = str.substr(divpos + 1);
            unsigned isvalid = db.change_pswd(username.c_str(),
                                              new_pswd.c_str());
            printf("sent:%d\n", isvalid);
            the_sock->SendLine(to_string(isvalid));
        }
        else if (msghead == RAND_CALL) {
            unsigned num = rand() % Class_Members.size();
            while (Class_Members[num] == nullptr || num == the_number)
                num = rand() % Class_Members.size();
            printf("rand call: %d\n", num);
            cout << "username: "
                 << *Class_Members[num]->username_w << endl;
            Sleep(10);
            Class_Members[num]->sendmsg(AUDIO_OPEN);
            the_sock->SendLine(CALLED_USERNAME
                               + *Class_Members[num]->username_w);
            lastcalled = num;
        }
        else if (msghead == RAND_CALL_OVER) {
            if (lastcalled < 0 || lastcalled >= Class_Members.size()) {
                printf("unable to shut the called student %d\n",
                       lastcalled);
                Sleep(10);
            }
            Class_Members[lastcalled]->sendmsg(AUDIO_SHUT);
            printf("shut %d\n", lastcalled);
            Sleep(10);            
            lastcalled = -1;
        }
        else if (msghead == AUDIO_MSG) {
            printf("audio message!\n");
            Sleep(10);            

            for (int i = 0; i < Class_Members.size(); i++) {
                if (Class_Members[i] == nullptr ||
                    the_number == *(Class_Members[i]->number_w))
                    continue;
                else Class_Members[i]->sendmsg(str);
                printf("send to %d\n", i);
                Sleep(10);                
            }
        }
        else if (msghead == VID_MSG) {
            str = str.substr(4);
            printf("received vid %d\n", str.length());
            for (int i = 0; i < Class_Members.size(); i++) {
                if (Class_Members[i] == nullptr ||
                    the_number == *(Class_Members[i]->number_w))
                    continue;
                else Class_Members[i]->sendmsg(VID_MSG + str);
            }
        }
        else if (msghead == PUSH_PROB) {
            printf("problem sent %d\n", str.length());
            cout << str << endl;
            for (int i = 0; i < Class_Members.size(); i++) {
                if (Class_Members[i] == nullptr ||
                    the_number == *(Class_Members[i]->number_w))
                    continue;
                else Class_Members[i]->sendmsg(str);
            }
        }
        else if (msghead == ANS_PROB) {
            printf("got an answer\n");
            str = str.substr(4);
            for (int i = 0; i < Class_Members.size(); i++) {
                if (Class_Members[i] == nullptr ||
                    *(Class_Members[i]->type_w) != TEACHER)
                    continue;
                printf("found teacher");
                Class_Members[i]->sendmsg(ANS_PROB + the_username
                                          + ":" + str);
            }
        }
        else if (msghead == PULL_PROB) {
            printf("pull prob sent\n");
            for (int i = 0; i < Class_Members.size(); i++) {
                if (Class_Members[i] == nullptr ||
                    *(Class_Members[i]->number_w) == the_number)
                    continue;
                Class_Members[i]->sendmsg(PULL_PROB);
            }
        }
        else if (msghead == ATTENTION) {
            the_attention_bottom += 1;
            str = str.substr(4);
            if (str[0] == '1') {
                the_attention_top += 1;
            }
        }
    }

    unsigned the_quit_time = time(NULL);
    for (int i = 0; i < Class_Members.size(); i++) {
        if (the_type == TEACHER) break;
        if (Class_Members[i] == nullptr ||
            *(Class_Members[i]->type_w) != TEACHER)
            continue;
        printf("found teacher");
        string att_data = ATT_DATA + the_username +
            ":" + to_string(the_enter_time) +
            ":" + to_string(the_quit_time) +
            ":" + to_string((double)the_attention_top / the_attention_bottom);
        Class_Members[i]->sendmsg(att_data);
    }
    
    delete member;
    Class_Members[the_number] = nullptr;
    printf("connection %d offline\n", the_number);
    Sleep(10);    
}

