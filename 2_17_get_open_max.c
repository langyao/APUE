#include "apue.h"
#include <errno.h>
#include <limits.h>
#include <sys/resource.h>

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif

#define OPEN_MAX_GUESS 256

/*long open_max(void)
{
    if(openmax == 0)
    {
        errno = 0;
        if((openmax = sysconf(_SC_OPEN_MAX)) < 0)
        {
            if(errno == 0)
                openmax = OPEN_MAX_GUESS;
            else
                err_sys("sysconf error for _SC_OPEN_MAX");
        }
    }
    return openmax;
}
*/

//因为有些操作系统将sysconf的返回值设为LONG_MAX,这个值很大，对程序可不友好
long open_max(void)
{
    struct rlimit rl;
    if((openmax = sysconf(_SC_OPEN_MAX)) < 0 || openmax == LONG_MAX)
    {
        if(getrlimit(RLIMIT_NOFILE,&rl)< 0)
            err_sys("can not get file limit");
        if(rl.rlim_max == RLIM_INFINITY)
            openmax = OPEN_MAX_GUESS;
        else
            openmax = rl.rlim_max;

    }
    return openmax;
}

int main(void)
{
    printf("openmax:%ld\n",open_max());
}
