#include "dboperator.h"
#include <cstdio>

const char DBPATH[20] = "./Clients.db";

int main(void) {
    dboperator db(DBPATH);
    printf("start\n");
    int result = db.add_client("A", "asdffdsa", TEACHER);
    printf("%d\n", result);
    result = db.add_client("B", "asdf", ADMIN);
    printf("%d\n", result);
    result = db.del_client("B");
    printf("%d\n", result);
    result = db.change_username("A", "AA");
    printf("%d\n", result);
    result = db.change_pswd("AA", "ASDFFDSA");
    printf("%d\n", result);
    result = db.checkmatch("AA", "ASDFFDSA");
    printf("%d\n", result);
    printf("end");
    return 0;
}
