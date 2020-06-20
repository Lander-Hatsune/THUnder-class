/*************************************************************************
[Filename]               adminop.h
[Modules & purpose]      connect Adminclient & AdminMainPage
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/
#pragma once
#include <QString>
#include "../definitions.h"
#include "../model/adminclient.h"

/*************************************************************************
[Class Name]        Adminop
[Function]          the controller between AdminMainPage and AdminClient
[Interfaces]        
- constructor Adminop: copy the Adminclient* param
- deconstructor ~Adminop:
- add_clientop: send the "add" command to Adminclient, return the feedback
- del_clientop: send the "delete" command to Adminclient, return the feedback
- change_usernameop: send the "change username" command to Adminclient, return the feedback
- change_pswdop: send the "change password" command to Adminclient, return the feedback
[Developer & date] 王文新, 2020/5
[Modification log] None
*************************************************************************/
class Adminop {
private:
    Adminclient* adminclt;

public:
    Adminop(Adminclient* adminclt);
    ~Adminop();
    Adminop(const Adminop&) = delete;
    Adminop& operator = (const Adminop&) = delete;
    const QString add_clientop(const string&, const string&,
                               const CLT_TYPE&);
    const QString del_clientop(const string&);
    const QString change_usernameop(const string&, const string&);
    const QString change_pswdop(const string&, const string&);
};

