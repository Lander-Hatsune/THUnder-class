#include "record.h"
#include <string>
using namespace std;

Record::Record(const string& username, const string& start_time,
               const string& quit_time, const string& att_ratio) {
    this->username = username;
    this->start_time = start_time;
    this->quit_time = quit_time;
    this->att_ratio = att_ratio;
}
Record::~Record() {
    ;
}
