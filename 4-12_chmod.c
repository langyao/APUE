#include "apue.h"
#include <fcntl.h>

int main(void)
{
    struct stat buf;

    //turn on set-group-ID and turn off group-executes


    if(stat("foo",&buf) < 0)
        err_sys("stat error for foo");

    buf.st_mode |= S_ISGID;
    buf.st_mode &= ~S_IXGRP;

    if(chmod("foo",buf.st_mode) < 0)
        err_sys("chmod error for foo");

    //set bar mode to "rw-r--r--"
    if(chmod("bar",S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
        err_sys("chmod error for bar");

    exit(0);


}
