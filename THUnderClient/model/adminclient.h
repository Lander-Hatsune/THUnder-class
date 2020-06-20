/*************************************************************************
[Filename]               adminclient.h
[Modules & purpose]      adminclient model
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/
#pragma once
#include "client.h"
#include <string>
using std::to_string;

/*************************************************************************
[Class Name]        Adminclient
[Function]          the model of Admin
[Interfaces]        
- constructor Adminclient: 
- deconstructor ~Adminop:
- add_client: send the "add" command to server, return the feedback
- del_client: send the "delete" command to server, return the feedback
- change_username: send the "change username" command to server, return the feedback
- change_pswd: send the "change password" command to server, return the feedback
[Developer & date] 王文新, 2020/5
[Modification log] None
*************************************************************************/
class Adminclient: public Client {
public:
    Adminclient(Client* clt);
    ~Adminclient();
    Adminclient(const Adminclient&) = delete;
    Adminclient& operator = (const Adminclient&) = delete;

    unsigned add_client(const string&, const string&,
                        const CLT_TYPE& type);
    unsigned del_client(const string&);
    unsigned change_username(const string&, const string&);
    unsigned change_pswd(const string&, const string&);
};
