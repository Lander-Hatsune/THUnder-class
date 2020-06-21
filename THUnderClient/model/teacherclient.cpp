/*************************************************************************
[Filename]               teacherclient.cpp
[Modules & purpose]      teacherclient model
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/
#include "teacherclient.h"
using namespace std;

vector<pair<string, HWND> > _window_list;

/*************************************************************************
Name:       Teacherclient
Function:   constructor
Params:     none
Return val: N/A
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
Teacherclient::Teacherclient(Client* clt): Client(*clt) {
    delete clt;
}

/*************************************************************************
Name:       ~Teacherclient
Function:   deconstructor
Params:     none
Return val: N/A
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
Teacherclient::~Teacherclient() {;}

/*************************************************************************
Name:       send_audiopiece
Function:   send audio piece
Params:     string(input)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherclient::send_audiopiece(string& audio) {
    this->sock.SendLine(AUDIO_MSG + audio);
}

/*************************************************************************
Name:       receive_msg
Function:   fetch a piece of message from server
Params:     none
Return val: string: the message
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
string Teacherclient::receive_msg() {
    return this->sock.ReceiveLine();
}

/*************************************************************************
Name:       randcall
Function:   start a random roll call
Params:     none
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherclient::randcall() {
    this->sock.SendLine(RAND_CALL);
}

/*************************************************************************
Name:       endcall
Function:   end the started random call
Params:     none
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherclient::endcall() {
    this->sock.SendLine(RAND_CALL_OVER);
}

/*************************************************************************
Name:       send_prob
Function:   send problem
Params:     string * 3(input)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherclient::send_prob(string prob, string ans, string r_ans) {
    this->sock.SendLine(PUSH_PROB + prob + ":" + ans + ":" + r_ans);
}

/*************************************************************************
Name:       pull_prob
Function:   force reject answers
Params:     none
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherclient::pull_prob()
{
    sock.SendLine(PULL_PROB);
}

/*************************************************************************
Name:       get_window_title_list
Function:   get all the windows' titles into the vector
Params:     vector<pari<string, HWND> >&(input)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherclient::get_window_title_list(vector<pair<string, HWND> >& list)
{
    EnumWindows(enum_window_callback, 0);
    for (int i = 0; i < _window_list.size(); i++) {
        list.push_back(_window_list[i]);
    }
}

/*************************************************************************
Name:       enum_window_callback
Function:   Windows API callback
Params:     HWND(input)
Return val: WINBOOL: whether to continue
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
WINBOOL Teacherclient::enum_window_callback(HWND hwnd, long long lparam)
{
    char buffer[128];
    GetWindowTextA(hwnd, (LPSTR)buffer, 120);
    string name = buffer;
    if (name.empty()) return true;
    _window_list.push_back(make_pair(name, hwnd));
    return true;
}

/*************************************************************************
Name:       send_vid
Function:   send video message
Params:     string(input)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherclient::send_vid(string& msg)
{
    sock.SendLine(VID_MSG + msg);
}

/*************************************************************************
Name:       add_record
Function:   add a record
Params:     string * 4(input)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherclient::add_record(const string& username, const string& start_time,
                               const string& quit_time, const string& att_ratio)
{
    Record* rec = new Record(username, start_time, quit_time, att_ratio);
    this->records.push_back(rec);
}

/*************************************************************************
Name:       class_over
Function:   classover
Params:     none
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Teacherclient::class_over()
{
    this->sock.SendLine(CLASS_OVER);
}
