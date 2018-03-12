/*获取文件状态标志*/


#include "apue.h"
#include <fcntl.h>


//设置文件属性：文件状态标志位
void set_fl(int fd, int flags)
{
    int val;

    if((val = fcntl(fd,F_GETFL,0))< 0)
        err_sys("fcntl F_GETFL error");

    val |= flags;
    //val &= ~flags; clr_fl,清除设置的位

    if(fcntl(fd,F_SETFL,val) < 0)
        err_sys("fcntl F_SETFL error");
}

int main(int argc, char **argv)
{

    //开启同步写标志，每次write都要等待，直至数据都写到磁盘上再返回。
//    set_fl(atoi(argv[1]),O_SYNC);

    int val;
    if(argc != 2)
    {
        err_quit("usage:a.out <descriptor>");
    }

    if((val = fcntl(atoi(argv[1]),F_GETFL,0)) == -1)
        err_sys("fcntl error for fd %d",atoi(argv[1]));

    switch(val & O_ACCMODE)
    {
        case O_RDONLY:
            printf("read only");
            break;
        case O_WRONLY:
            printf("write only");
            break;
        case O_RDWR:
            printf("write and read");
            break;
        default:
            err_dump("unknown access mode");
    }

    if(val & O_APPEND)
        printf(",append");
    if(val & O_NONBLOCK)
        printf("nonblock");
    if(val & O_SYNC)
        printf(",synchronous writes");

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
    if(val & O_FSYNC)
        printf(",synchronous writes");
#endif

    printf("\n");

    exit(0);


}
