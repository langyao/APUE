#include "apue.h"
#include <time.h>
#include <setjmp.h>
#include <signal.h>

static sigjmp_buf env;
static volatile sig_atomic_t canjmp;

Sigfunc* signal(int signo,Sigfunc* func)
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



Sigfunc* sig_alrm1()
{
    pr_mask("in sig_alrm:");
}

Sigfunc* sig_usr1()
{
    time_t starttime;
    if(canjmp != 1)
        return;
    alarm(3);
    starttime = time(NULL);
    for(;;)
        if(time(NULL) - starttime > 5 )
            break;

    pr_mask("finishing sig_usr1:");
    siglongjmp(env,1);
}
/*
int main(void)
{
    if(signal(SIGUSR1,sig_usr1) < 0)
        err_sys("signal for SIGUSR1 error");
    if(signal(SIGALRM,sig_alrm1) < 0)
        err_sys("signal for sigalrm error");

    pr_mask("starting main:");

    if(sigsetjmp(env,1))
    {
        pr_mask("ending main:");
        exit(0);
    }

    canjmp = 1;
    for(;;)
        pause();
}
*/
