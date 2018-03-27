#include "apue.h"
#include <time.h>
#include <signal.h>


Sigfunc* mysignal(int signo,Sigfunc* func)
{
    struct sigaction oact,act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = func;

    if(signo == SIGALRM)
    {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif
    }
    else
    {
        act.sa_flags |= SA_RESTART;
    }

    if(sigaction(signo,&act,&oact) < 0)
        return SIG_ERR;

    return oact.sa_handler;
}
void pr_mask(const char *s)
{
    sigset_t set;
    if(sigprocmask(0,NULL,&set) < 0)
        err_ret("sigprocmask error");

    printf("%s:",s);
    if(sigismember(&set,SIGINT))
        printf("SIGINT ");
    else if(sigismember(&set,SIGALRM))
        printf("SIGALRM ");
    else if(sigismember(&set,SIGUSR1))
        printf("SIGUSR1 ");
    else if(sigismember(&set,SIGUSR2))
        printf("SIGUSR2 ");
    else if(sigismember(&set,SIGQUIT))
        printf("SIGQUIT ");
    printf("\n");
}




Sigfunc* sig_int(int signo)
{
    pr_mask("sig_int");
}

int main(void)
{
    sigset_t oldset,newset,waitset;
    if(mysignal(SIGINT,sig_int) == SIG_ERR)
        err_sys("signal for sigalrm error");

    sigemptyset(&newset);
    sigaddset(&newset,SIGINT);

    sigemptyset(&waitset);
    sigaddset(&waitset,SIGUSR1);
    sigaddset(&waitset,SIGUSR2);
    sigaddset(&waitset,SIGQUIT);

    pr_mask("starting main");

    if(sigprocmask(SIG_BLOCK,&newset,&oldset) < 0)
        err_sys("sigprocmask error");

    pr_mask("in critical region");


    //wake up by all signal except sigusr1
    if(sigsuspend(&waitset) != -1)
        err_sys("sigsuspend error");

    if(sigprocmask(SIG_SETMASK,&oldset,NULL) < 0)
        err_sys("sigprocmask error");

    pr_mask("ending main");
}

