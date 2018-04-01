#include "apue.h"
#include <sys/time.h>
#include <time.h>

int main(void)
{
    struct tm *p;
    time_t t;
    int i = 1;
    while(1)
    {
        sleep(60);
        if(i++%5 == 0)
        {
            time(&t);
            printf("date and time:%s\n",ctime(&t));
            p = gmtime(&t);
            printf("tm_sec:%d\n",p->tm_sec);
        }

    }
}
