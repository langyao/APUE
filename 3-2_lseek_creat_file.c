//创建空洞文件，注意空洞部分并不在磁盘上占用存储区
//


#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(int argc, char **argv)
{
    int fd;
    if((fd = open(argv[1],O_CREAT | O_RDWR | O_TRUNC,0777)) < 0)
        err_sys("open error");

    if( write(fd,buf1,10) != 10)
        err_sys("buf1 write error");

    if(lseek(fd,413265401,SEEK_SET) == -1)
        err_sys("seek error");

    if( write(fd,buf2,10) != 10)
        err_sys("buf2 write error");

    exit(0);

}

