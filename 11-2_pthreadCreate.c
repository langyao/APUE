#include "apue.h"
#include <errno.h>
#include <pthread.h>
extern int errno;

pthread_t ntid;
void printids(const char *s)
{
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();

    printf("%s pid = %lu , tid = %lu,(0x%1x)\n",s
            ,(unsigned long)pid,(unsigned long)tid,(unsigned long)tid);
}

void* thr_fn(void* arg)
{
    printids("new thread:");
    return (void*)0;
}


int main(void)
{
    int error;

    if((error = pthread_create(&ntid,NULL,thr_fn,NULL)) < 0)
        err_quit("can not create new thread");

    printids("main thread:");
    sleep(1);

    return 0;
}
