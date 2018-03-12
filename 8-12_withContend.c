#include "apue.h"
#include <sys/wait.h>

static void charactatime(char *str)
{
    setbuf(stdout,NULL);
    char *ptr;
    int c ;
    for(ptr = str; (c = *ptr++) != 0; )
        putc(c,stdout);
}

int main(void)
{
    pid_t pid;

    if((pid = fork()) < 0)
        err_sys("fork error");
    else if(pid ==  0)
    {
        charactatime("output from child\n");
    }
    else
        charactatime("output from parent\n");

    exit(0);
}
