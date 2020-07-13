/*************************************************************************
[Filename]               record.h
[Modules & purpose]      record struct model
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/
#pragma once
#include <string>
using namespace std;

/*************************************************************************
[Class Name]        Record
[Function]          a data structure for Record
[Interfaces]        
- constructor Record
- deconstructor ~Record
[Developer & date] 王文新, 2020/5
[Modification log] None
*************************************************************************/
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
