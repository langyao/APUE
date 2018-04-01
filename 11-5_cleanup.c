#include "apue.h"
#include <pthread.h>

void cleanup(void *arg)
{
    printf("cleanup:%s\n",(char*)arg);
}

void* thr_func1(void *arg)
{
    printf("thread1 start\n");
    pthread_cleanup_push(cleanup,"thread1 1 first handler");
    pthread_cleanup_push(cleanup,"thread1 1 second handler");

    if(arg)
        return ((void*)1);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return ((void*)1);
}



void* thr_func2(void *arg)
{
    printf("thread2 start\n");
    pthread_cleanup_push(cleanup,"thread1 2 first handler");
    pthread_cleanup_push(cleanup,"thread1 2 second handler");

    if(arg)
        pthread_exit((void*)2);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit((void*)2);
}

int main(void)
{
    pthread_t tid1;
    pthread_t tid2;
    void *ret;

    int err = 0;

    if((err = pthread_create(&tid1,NULL,thr_func1,(void*)1)) < 0)
        err_exit(err,"thread1 create error");
    if((err = pthread_join(tid1,&ret)) < 0)
        err_exit(err,"thread1 join error");


    if((err = pthread_create(&tid2,NULL,thr_func2,(void*)2)) < 0)
        err_exit(err,"thread2 create error");

    if((err = pthread_join(tid2,&ret)) < 0)
        err_exit(err,"thread2 join error");

    return 0;


}
