#pragma once
#include <string>
using namespace std;

class Record {
public:
    Record(const string&, const string&,
           const string&, const string&);
    ~Record();
    Record(const Record&) = delete;
    Record& operator = (const Record&) = delete;
    
    string username;
    string start_time;
    string quit_time;
    string att_ratio;
};
