#include "apue.h"
#include <time.h>
#include <pthread.h>

int main(void)
{
    struct timespec tout;
    struct tm *tmp;
    char buf[64];

    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&lock);

    clock_gettime(CLOCK_REALTIME,&tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf,sizeof(buf),"%r",tmp);
    printf("current time is %s\n",buf);
    tout.tv_sec += 10;

    int err = pthread_mutex_timedlock(&lock,&tout);
    clock_gettime(CLOCK_REALTIME,&tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf,sizeof(buf),"%r",tmp);
    printf("now time is %s\n",buf);

    if(err == 0)
        printf("mutex locked again");
    else
        printf("can not lock mutex again:%s\n",strerror(err));
    pthread_mutex_unlock(&lock);
    return 0;

}
