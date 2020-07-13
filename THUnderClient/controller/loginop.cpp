/*************************************************************************
[Filename]               loginop.cpp
[Modules & purpose]      support login service
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/

#include "loginop.h"

using std::to_string;
using std::string;
/*************************************************************************
Name:       Loginop
Function:   construtcor
Params:     None
Return val: N/A
Developer & date: 王文新, 2020/5
Modification log: None
*************************************************************************/
Loginop::Loginop() {
    this->failtime = 0;
}

/*************************************************************************
Name:       ~Loginop
Function:   deconstructor
Params:     None
Return val: N/A
Developer & date: 王文新, 2020/5
Modification log: None
*************************************************************************/
Loginop::~Loginop() {;}

/*************************************************************************
Name:       login
Function:   New a client, tryna login and verify the info with the server,
  return an encoded command to instruct the LoginMainPage's next step
Params:     username(input), pswd(input), ip(input)
Return val: const QString, the instruction to switch widget or show alert
Developer & date: 王文新, 2020/5
Modification log: None
*************************************************************************/
const QString Loginop::login(const string& username,
                             const string& pswd,
                             const string& ip) {
    try {
        Client* pclt = nullptr;
        if (!ip.empty()) pclt = new Client(username, pswd, ip);
        else pclt = new Client(username, pswd);
        if (*(pclt->type) == ADMIN) {
            Adminclient* adminclt = new Adminclient(pclt);
            Adminop* adminop = new Adminop(adminclt);
            AdminMainPage* adminmainpage = new AdminMainPage(nullptr, adminop);
            adminmainpage->setWindowTitle("Administrator Mode (THUnder Class)");
            adminmainpage->show();
            return ":HIDE:";
        }
        else if (*(pclt->type) == TEACHER) {
            Teacherclient* teacherclt = new Teacherclient(pclt);
            Teacherop* teacherop = new Teacherop(teacherclt);
            TeacherMainPage* teachermainpage = new TeacherMainPage(nullptr, teacherop);
            teachermainpage->show();
            teachermainpage->setWindowTitle("Teacher Mode (THUnder Class)");
            return ":HIDE:";
        }
        else if (*(pclt->type) == STU) {
            Stuclient* stuclt = new Stuclient(pclt);
            Stuop* stuop = new Stuop(stuclt);
            StuMainPage* stumainpage = new StuMainPage(nullptr, stuop);
            stumainpage->show();
            stumainpage->setWindowTitle("Student Mode (THUnder Class)");
            return ":HIDE:";
        }
        else {
            this->failtime += 1;
            delete pclt;
            if (failtime >= 3) return ":SHUT:";
            else return "Username or password is wrong!\nYou have " +
                    QString::fromStdString(to_string(3 - this->failtime) +
                                           " more times to try");
        }
    } catch (...) {
        return "failed to connect to the server";
    }


}
