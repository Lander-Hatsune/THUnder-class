#include "loginop.h"
#include "../view/loginpage.h"
#include <cstdio>

using std::string;

loginop::loginop() {
    this->_failtime = 0;
    this->failtime = &this->_failtime;
}

loginop::~loginop() {;}

unsigned loginop::login(const string& username,
                        const string& pswd) {
    Client* pclt = new Client(username, pswd);
    switch (*pclt->type) {
    case ADMIN:
        Adminop* adminop = new Adminop(*pclt);
        AdminMainPage* adminmainpage = new AdminMainPage(adminop);
        adminmainpage->setWindowTitle("Administrator Mode (THUnder Class)");
        adminmainpage->show();
        return 0;
    case TEACHER:
        //TeacherMainPage* teachermainpage = new TeacherMainPage();
        return 0;
    case STU:
        //StuMainPage* stumainpage = new StuMainPage();
        return 0;
    default:
        this->_failtime += 1;
        delete pclt;
        return 1;
    }
}
