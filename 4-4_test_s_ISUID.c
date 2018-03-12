#include "apue.h"

int main(int argc, char **argv)
{
    struct stat buf;
    if(lstat(argv[1],&buf) <  0)
    {
        err_sys("lstat error");
    }

    printf("S_ISUID:%x\n",S_ISUID);
    printf("S_ISGID:%x\n",S_ISGID);
    printf("S_IFMT:%x\n",S_IFMT);
    printf("S_ISDIR:%x\n",S_IFDIR);
    printf("S_IfLNK:%x\n",S_IFLNK);
    printf("S_IRUSR:%x\n",S_IRUSR);
    if(buf.st_mode & S_ISUID == S_ISUID)
    {
        printf("将进程的有效用户ID设置为了用户组ID\n");
    }
    else
        printf("no set\n");


    if(buf.st_mode & S_IRUSR == S_IRUSR)
    {
        printf("yonghu read\n");
    }
    else
        printf(" read not permit\n");
    exit(0);
}
