#pragma once
#include "client.h"
#include "record.h"
#include <vector>
using namespace std;

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
