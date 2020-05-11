#pragma once
#include <QString>
#include "../definitions.h"
#include "../model/adminclient.h"

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

