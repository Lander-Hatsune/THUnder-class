/*************************************************************************
[Filename]               stuclient.h
[Modules & purpose]      stuclient model
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/
#pragma once
#include "client.h"

/*************************************************************************
[Class Name]        Stuclient
[Function]          the model of stuclient
[Interfaces]        
- constructor Stuclient
- deconstructor ~Stuclient
- send_audiopiece: send audio piece
- receive_msg: fetch a piece of message from server
- send_ans: send the answer to server
- send_attention: seng the attention data to server
[Developer & date] 王文新, 2020/6
[Modification log] None
*************************************************************************/
class Stuclient: public Client {
public:
    Stuclient(Client* clt);
    ~Stuclient();
    void send_audiopiece(string&);
    string receive_msg();
    void send_ans(const string&, const unsigned&);
    void send_attention(bool activated);
};
