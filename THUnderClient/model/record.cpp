/*************************************************************************
[Filename]               record.cpp
[Modules & purpose]      record struct model
[Developer & date]       王文新 2020/6
[Modification log]
*************************************************************************/
#include "record.h"
using namespace std;

/*************************************************************************
Name:       Record
Function:   constructor
Params:     string * 4(input)
Return val: N/A
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
Record::Record(const string& username, const string& start_time,
               const string& quit_time, const string& att_ratio) {
    this->username = username;
    this->start_time = start_time;
    this->quit_time = quit_time;
    this->att_ratio = att_ratio;
}

/*************************************************************************
Name:       ~Record
Function:   deconstructor
Params:     none
Return val: void
Developer & date: 王文新, 2020/6
Modification log: None
*************************************************************************/
Record::~Record() {
    ;
}
