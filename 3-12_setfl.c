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


int main(void)
{
    //开启同步写标志，每次write都要等待，直至数据都写到磁盘上再返回。
    set_fl(STDOUT_FILENO,O_SYNC);

}
