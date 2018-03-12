#include "apue.h"

int globvar = 6;
char buf[] = "a write to stdout\n";

int main(void)
{
    int var;
    pid_t  pid;

    var = 88;
    if(write(STDOUT_FILENO,buf,sizeof(buf) - 1) != sizeof(buf) -1 )
        err_sys("write buf error");

    printf("before fork\n");

    if((pid = fork()) < 0)
        err_sys("fork error");
    else if(pid == 0)
    {
        var++;
        globvar++;
        exit(0);

    }
    else
    {
        sleep(2);
        while(1);

    }

    printf("pid = %ld, globvar = %d, var = %d\n",(long)getpid(),globvar,var);
    exit(0);

}
