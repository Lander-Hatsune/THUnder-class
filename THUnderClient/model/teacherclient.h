/*************************************************************************
[Filename]               teacherclient.h
[Modules & purpose]      teacherclient model
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/
#pragma once
#include "client.h"
#include "record.h"
#include <vector>
#include <windows.h>
using namespace std;

/*************************************************************************
[Class Name]        Teacherclient
[Function]          the model of teacherclient
[Interfaces]        
- constructor Teacherclient
- deconstructor ~Teacherclient
- send_audiopiece: send audio piece
- receive_msg: fetch a piece of message from server
- randcall: start a random roll call
- endcall: end the started random call
- send_prob: send problem
- pull_prob: pull problem
- get_window_title_list: get all the windows' titles into the vector
- enum_window_callback: Windows API callback
- send_vid: send video message
- add_record: add a record
[Developer & date] 王文新, 2020/6
[Modification log] None
*************************************************************************/
class Teacherclient: public Client {
public:
    Teacherclient(Client* clt);
    ~Teacherclient();
    void send_audiopiece(string& audio);
    string receive_msg();
    void randcall();
    void endcall();
    void send_prob(string, string, string);
    void pull_prob();
    void get_window_title_list(vector<pair<string, HWND> >& list);
    static BOOL CALLBACK enum_window_callback(HWND hwnd, long long lparam);
    void send_vid(string&);
    void add_record(const string&, const string&,
                    const string&, const string&);
protected:
    vector<Record*> records;
    friend class Teacherop;
};
