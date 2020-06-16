#include "loginop.h"
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
    try {
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
            printf("fail:%d\n", failtime);
            this->failtime += 1;
            delete pclt;
            if (failtime >= 3) return ":SHUT:";
            else return "Username or password is wrong!\nYou have " +
                    QString::fromStdString(to_string(3 - this->failtime) +
                                           " more times to try");
        }
    } catch (...) {
        printf("failed to connect to the server\n");
        Sleep(5000);
    }


}
