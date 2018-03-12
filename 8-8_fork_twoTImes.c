#include "apue.h"
#include <sys/wait.h>

void pr_exit(int status)
{
    if(WIFEXITED(status))
        printf("normal termination, exit status = %d\n",
                WEXITSTATUS(status));
    else if(WIFSIGNALED(status))
        printf("abnormal termination,signal number = %d%s\n",
                WTERMSIG(status),
#ifdef WCOREDUMP
              WCOREDUMP(status) ?"core file generated":"");
#else
    "");
#endif
    else if(WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n",
                WSTOPSIG(status));
}

int main(void)
{
    pid_t pid;

    if((pid = fork()) < 0)
        err_sys("fork error");
    else if(pid == 0)
    {
        if((pid = fork()) < 0)
            err_sys("fork error");
        else if(pid > 0)
            exit(0);
        else
        {
            sleep(2);
            printf("second child process, parent child = %ld\n",(long)getppid());
            exit(0);
        }
    }

    if(waitpid(pid,NULL,0) != pid)
        err_sys("wait pid error");

    exit(0);
}
