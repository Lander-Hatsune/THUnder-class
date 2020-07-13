/*************************************************************************
[Filename]               loginop.h
[Modules & purpose]      support login service
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/

#pragma once
#include <string>
#include <QWidget>
#include "../definitions.h"

#include "../model/client.h"
#include "../model/adminclient.h"
#include "../model/teacherclient.h"
#include "../model/stuclient.h"

#include "../controller/adminop.h"
#include "../controller/teacherop.h"
#include "../controller/stuop.h"

#include "../view/adminmainpage.h"
#include "../view/teachermainpage.h"
#include "../view/stumainpage.h"

using std::string;

/*************************************************************************
[Class Name]        Loginop
[Function]          the controller between LoginMainPage and models
[Interfaces]        
- constructor Loginop: 
- deconstructor ~Login:
- login: New a client, tryna login and verify the info with the server,
  return an encoded command to instruct the LoginMainPage's next step
[Developer & date] 王文新, 2020/5
[Modification log] None
*************************************************************************/
class Loginop {
private:
    unsigned failtime;

public:
    Loginop();
    ~Loginop();
    Loginop(const Loginop&) = delete;
    Loginop& operator = (const Loginop&) = delete;
    
    const QString login(const string&, const string&, const string&);
};
