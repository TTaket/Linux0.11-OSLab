#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "../include/asm/segment.h"



char username[24];


int sys_iam(const char * name) {
    char tmp[26];
    short break_flag = 0, i = 0;
    for (i = 0; i < 26; ++i) {
        tmp[i] = get_fs_byte(name + i);
        if (tmp[i] == '\0') {
            break_flag = 1;
            break;
        }
    }
    if (!break_flag || i > 23) {
        return -(EINVAL);
    }
    char* dest = username;
    strcpy(dest, tmp);
    return i;
}

int sys_whoami(char* name,unsigned  int size) {
    short length = strlen(username);
    if (length > size) {
        return -(EINVAL);
    }
    short i = 0;
    for (i; i < size; ++i) {
        put_fs_byte(username[i], name + i);
        if (username[i] == '\0') {
            break;
        }
    }
    return i;
}
