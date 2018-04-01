#include "apue.h"
#include <pthread.h>


struct foo
{
    int a,b,c,d;
};

void* thr_func1(void *arg)
{
    printf("thread1 returning\n");
    return ((void*)0);
}

void print_foo(const char *s,struct foo *f)
{
    printf("%s\n",s);
    printf("structure at 0x%1x\n",f);
    printf("foo.a = %d\n",f->a);
    printf("foo.b = %d\n",f->b);
    printf("foo.c = %d\n",f->c);
    printf("foo.d = %d\n",f->d);
}


void* thr_func2(void *arg)
{
    struct foo f = {1,2,3,4};
    print_foo("thread2's exiting status:",&f);
    pthread_exit((void*)&f);
}

int main(void)
{
    pthread_t tid1;
    pthread_t tid2;
    void *ret;

    int err = 0;
    if((err = pthread_create(&tid2,NULL,thr_func2,NULL)) < 0)
            err_exit(err,"thread2 create error");

    if((err = pthread_join(tid2,&ret)) < 0)
        err_exit(err,"thread2 join error");
    sleep(1);

    if((err = pthread_create(&tid1,NULL,thr_func1,NULL)) < 0)
            err_exit(err,"thread1 create error");

    print_foo("parent:",(struct foo *)ret);

    return 0;


}
