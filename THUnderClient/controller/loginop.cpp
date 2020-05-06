#include "loginop.h"
#include "../view/loginpage.h"
#include <cstdio>
#include <string>

using std::to_string;
using std::string;

Loginop::Loginop() {
    this->failtime = 0;
}

Loginop::~Loginop() {;}

const QString Loginop::login(const string& username,
                             const string& pswd) {
    Client* pclt = new Client(username, pswd);
    if (*(pclt->type) == ADMIN) {
        Adminclient* adminclt = new Adminclient(pclt);
        Adminop* adminop = new Adminop(adminclt);
        AdminMainPage* adminmainpage = new AdminMainPage(nullptr, adminop);
        adminmainpage->setWindowTitle("Administrator Mode (THUnder Class)");
        adminmainpage->show();
        return ":HIDE:";
    }
    else if (*(pclt->type) == TEACHER) {
        //TeacherMainPage* teachermainpage = new TeacherMainPage();
        return ":HIDE:";
    }
    else if (*(pclt->type) == STU) {
        //StuMainPage* stumainpage = new StuMainPage();
        return ":HIDE:";
    }
    else {
        printf("fail:%d\n", failtime);
        this->failtime += 1;
        delete pclt;
        if (failtime >= 3) return ":SHUT:";
        else return "Username or password is wrong!\nYou have " +
                QString::fromStdString(to_string(3 - this->failtime) +
                                       " more times to try");
    }
}
