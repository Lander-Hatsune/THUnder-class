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
const int PORT = 4000;

const string CHECK_TYPE = ":CT:";
const string ADD_CLIENT = ":AC:";
const string DEL_CLIENT = ":DC:";
const string CHANGE_USERNAME = ":CU:";
const string CHANGE_PSWD = ":CP:";

const string AUDIO_OPEN = ":AO:";
const string AUDIO_SHUT = ":AS:";
const string AUDIO_MSG = ":AU:";

const string VID_MSG = ":VD:";

const string RAND_CALL = ":RC:";
const string CALLED_USERNAME = ":CU:";
const string RAND_CALL_OVER = ":RO:";

