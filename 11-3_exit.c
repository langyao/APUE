#include "apue.h"
#include <pthread.h>

void* thr_func1(void *arg)
{
    printf("thread1 returning\n");
    return ((void*)0);
}

void* thr_func2(void *arg)
{
    printf("thread2 exiting\n");
    pthread_exit((void*)2);
}

int main(void)
{
    pthread_t tid1;
    pthread_t tid2;
    void *ret;

    int err = 0;
    if((err = pthread_create(&tid1,NULL,thr_func1,NULL)) < 0)
            err_exit(err,"thread1 create error");

    if((err = pthread_join(tid1,&ret)) < 0)
        err_exit(err,"thread1 join error");
    printf("thread1's exiting status:%ld\n",(long)(ret));


    if((err = pthread_create(&tid2,NULL,thr_func2,NULL)) < 0)
            err_exit(err,"thread2 create error");

    if((err = pthread_join(tid2,&ret)) < 0)
        err_exit(err,"thread2 join error");
    printf("thread2's exiting status:%ld\n",(long)(ret));

    return 0;


}
