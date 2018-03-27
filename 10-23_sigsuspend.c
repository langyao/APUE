#include "apue.h"
#include <signal.h>

volatile sig_atomic_t quitflag;

static void sig_int(int signo)
{
    if(signo == SIGINT)
        printf("interrupt\n");
    else if(signo == SIGQUIT)
        quitflag = 1;
}

int main(void)
{
    sigset_t old,new,wait;
    if(signal(SIGINT,sig_int) == SIG_ERR)
        err_sys("signal sigint error");
    if(signal(SIGQUIT,sig_int) == SIG_ERR)
        err_sys("signal sigquit error");

    sigemptyset(&new);
    sigemptyset(&wait);
    sigaddset(&new,SIGQUIT);

    if(sigprocmask(SIG_BLOCK,&new,&old) < 0)
        err_sys("sigprocmask error");

    while(quitflag == 0)
        sigsuspend(&wait);

    quitflag = 0;
    if(sigprocmask(SIG_SETMASK,&old,NULL) < 0)
        err_sys("sigprocmask error");
    exit(0);
}
