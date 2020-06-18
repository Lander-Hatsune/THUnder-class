#pragma once
#include <QByteArray>
#include <vector>
#include "../definitions.h"
#include "../model/teacherclient.h"
#include <windows.h>
using namespace std;

class Teacherop {
private:
    Teacherclient* teacherclient;
    
public:
    Teacherop(Teacherclient*);
    ~Teacherop();
    Teacherop(const Teacherop&) = delete;
    Teacherop& operator = (const Teacherop&) = delete;
    
    void send_audiopiece(string&);
    string receive_msg();
    void randcall();
    void endcall();
    void send_prob(string, string, string);
    void pull_prob();

    void get_window_title_list(vector<pair<QString, HWND> >&);
    void send_vid(QByteArray&);

    void add_record(const string&, const string&,
                    const string&, const string&);
    void get_records(vector<Record*>&);
};
