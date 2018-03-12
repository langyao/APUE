#include "apue.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{

    struct stat buf;
    if(stat(argv[1],&buf) < 0)
        err_sys("stat error for %s",argv[1]);


    int fd = open(argv[1],O_RDWR | O_TRUNC);
    if(fd < 0)
        err_sys("open %s error",argv[1]);


    struct timespec times[2];
    times[0].tv_sec = buf.st_atime;
    times[0].tv_nsec = 0;
  //  times[1].tv_sec = buf.st_mtime;
  //  times[1].tv_nsec = 0;

    if(futimens(fd,times) < 0)
    {
        err_sys("futimens error");
    }

}

