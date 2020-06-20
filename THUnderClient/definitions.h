/*************************************************************************
[Filename]               definitions.h
[Modules & purpose]      some general definition
[Developer & date]       ÍõÎÄÐÂ 2020/6
[Modification log]
*************************************************************************/
#pragma once
#include <string>
using std::string;

#define CLT_TYPE unsigned

const int ADMIN = 1;
const int TEACHER = 2;
const int STU = 3;
const int VALID = 0;
const int INVALID = 1;
const string HOST = "127.0.0.1";
const int PORT = 20018;

const string CHECK_TYPE = ":CC:";
const string ADD_CLIENT = ":CA:";
const string DEL_CLIENT = ":CD:";
const string CHANGE_USERNAME = ":CU:";
const string CHANGE_PSWD = ":CP:";

const string AUDIO_OPEN = ":AO:";
const string AUDIO_SHUT = ":AS:";
const string AUDIO_MSG = ":AU:";

const string VID_MSG = ":VD:";

const string RAND_CALL = ":RC:";
const string CALLED_USERNAME = ":RU:";
const string RAND_CALL_OVER = ":RO:";

const string PUSH_PROB = ":PP:";
const string ANS_PROB = ":PA:";
const string PULL_PROB = ":PL:";

const string ATTENTION = ":TA:";
const string ATT_DATA = ":TD:";

