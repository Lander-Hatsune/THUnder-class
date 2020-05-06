#include "dboperator.h"
#include "Socket/Socket.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <process.h>
#include <vector>
#include <iostream>
using namespace std;

const int PORT = 4000;
const int MAX_CLT_NUMBER = 50;
const string CHECK_TYPE = ":CT:";
const string ADD_CLIENT = ":AC:";
const string DEL_CLIENT = ":DC:";
const string CHANGE_USERNAME = ":CU:";
const string CHANGE_PSWD = ":CP:";
dboperator db(DBPATH);


unsigned __stdcall Answer(void* x) {
    Socket* sock = (Socket*) x;
    while (true) {
        string str = sock->ReceiveLine();
        if (str.empty() || str == "\n") break;
        str = str.substr(0, str.length() - 1);
        cout << "received:" << str << endl;
        if (str.substr(0, 4) == CHECK_TYPE) {
            str = str.substr(4);
            unsigned divpos = str.rfind(":");
            string username = str.substr(0, divpos);
            string pswd = str.substr(divpos + 1);
            CLT_TYPE type = db.checktype(username.c_str(), pswd.c_str());
            printf("sent:%d\n", type);
            sock->SendLine(to_string(type));
        }
        else if (str.substr(0, 4) == ADD_CLIENT) {
            str = str.substr(4);
            CLT_TYPE type = str[str.length() - 1] - '0';
            str = str.substr(0, str.length() - 2);
            unsigned divpos = str.rfind(":");
            string username = str.substr(0, divpos);
            string pswd = str.substr(divpos + 1);
            unsigned isvalid = db.add_client(username.c_str(),
                                             pswd.c_str(), type);
            printf("sent:%d\n", isvalid);
            sock->SendLine(to_string(isvalid));            
        }
        else if (str.substr(0, 4) == DEL_CLIENT) {
            string username = str.substr(4);
            unsigned isvalid = db.del_client(username.c_str());
            printf("sent:%d\n", isvalid);
            sock->SendLine(to_string(isvalid));
        }
        else if (str.substr(0, 4) == CHANGE_USERNAME) {
            str = str.substr(4);
            unsigned divpos = str.rfind(":");
            string username = str.substr(0, divpos);
            string new_username = str.substr(divpos + 1);
            unsigned ret = db.change_username(username.c_str(),
                                                  new_username.c_str());
            printf("sent:%d\n", ret);
            sock->SendLine(to_string(ret));
        }
        else if (str.substr(0, 4) == CHANGE_PSWD) {
            str = str.substr(4);
            unsigned divpos = str.rfind(":");
            string username = str.substr(0, divpos);
            string new_pswd = str.substr(divpos + 1);
            unsigned isvalid = db.change_pswd(username.c_str(),
                                              new_pswd.c_str());
            printf("sent:%d\n", isvalid);
            sock->SendLine(to_string(isvalid));
        }
    }
}

int main(void) {
    SocketServer server(PORT, 50);
    vector<Socket*> clients;
    while (true) {
        Socket* sock = server.Accept();
        printf("new client\n");
        clients.push_back(sock);
        unsigned ret;
        _beginthreadex(0, 0, Answer, (void*) sock, 0, &ret);
    }
    return 0;
}