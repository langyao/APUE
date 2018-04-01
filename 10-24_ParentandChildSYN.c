#include "apue.h"
#include <sys/wait.h>
#include <signal.h>


static volatile sig_atomic_t sigflag;
static sigset_t newmask,oldmask,zeromask;

static void charactatime(char *str)
{
    setbuf(stdout,NULL);
    char *ptr;
    int c ;
    for(ptr = str; (c = *ptr++) != 0; )
        putc(c,stdout);
}

static void  sig_usr(int signo)
{
 //   if(signo == SIGUSR1 || signo == SIGUSR2)
        sigflag = 1;
}

void TELL_WAIT()
{
    if(signal(SIGUSR1,sig_usr) == SIG_ERR)
        err_sys("signal sigusr1 error");
    if(signal(SIGUSR2,sig_usr) == SIG_ERR)
        err_sys("signal sigusr2 error");
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGUSR1);
    sigaddset(&newmask,SIGUSR2);

    if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
        err_sys("sigprocmask error");
}


void WAIT_PARENT()
{
    while(sigflag == 0)
        sigsuspend(&zeromask);

    sigflag = 0;

    if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
        err_sys("sigprocmask wait_parent error");
}

void TELL_CHILD(pid_t pid)
{
    kill(pid,SIGUSR1);
}

void TELL_PARENT(pid_t pid)
{
    kill(pid,SIGUSR2);
}
void WAIT_CHILD()
{
    while(sigflag == 0)
        sigsuspend(&zeromask);
    sigflag = 0;

    if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
        err_sys("sigprocmask wait_parent error");
}

/*
int main(void)
{
    pid_t pid;

    TELL_WAIT();
    if((pid = fork()) < 0)
        err_sys("fork error");
    else if(pid ==  0)
    {
        WAIT_PARENT();
        charactatime("output from child\n");
    }
    else
    {
        charactatime("output from parent\n");
        TELL_CHILD(pid);
    }


    exit(0);
}
*/
