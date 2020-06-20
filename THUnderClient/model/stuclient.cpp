/*************************************************************************
[Filename]               stuclient.cpp
[Modules & purpose]      stuclient model
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/
#include "stuclient.h"
using namespace std;

/*************************************************************************
Name:       Stuclient
Function:   constructor
Params:     none
Return val: N/A
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
Stuclient::Stuclient(Client* clt): Client(*clt) {
    delete clt;
}

/*************************************************************************
Name:       ~Stuclient
Function:   deconstructor
Params:     none
Return val: N/A
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
Stuclient::~Stuclient() {;}

/*************************************************************************
Name:       receive_msg
Function:   fetch a piece of message from server
Params:     none
Return val: string: the message
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
string Stuclient::receive_msg() {
    return this->sock.ReceiveLine();
}

/*************************************************************************
Name:       send_ans
Function:   send the answer to server
Params:     string(input), unsigned(input)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Stuclient::send_ans(const string& ans, const unsigned& time)
{
    this->sock.SendLine(ANS_PROB + ans + ":" + to_string(time));
}

/*************************************************************************
Name:       send_attention
Function:   send the attention data to server
Params:     bool(input)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Stuclient::send_attention(bool activated)
{
    this->sock.SendLine(ATTENTION + to_string(activated));
}

/*************************************************************************
Name:       send_audiopiece
Function:   send audio piece
Params:     string(input)
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
void Stuclient::send_audiopiece(string& audio) {
    this->sock.SendLine(AUDIO_MSG + audio);
}
