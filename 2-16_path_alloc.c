#include "apue.h"
#include <errno.h>
#include <limits.h>

#ifdef PATH_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif

static long posix_version = 0;
static long xsi_version = 0;

/* if PATH_MAX is indeterminate, no guarantee this is adequate */
#define PATH_MAX_GUESS 1024


char *path_alloc(size_t *sizep)
{
    char *ptr;
    size_t size;

    if(posix_version == 0)
        posix_version = sysconf(_SC_VERSION);
    if(xsi_version == 0)
        xsi_version = sysconf(_SC_XOPEN_VERSION);

    if(pathmax == 0)
    {
        errno = 0;
        //pathconf:依赖于文件系统类型，返回的值可能是未定的，如果<0,且errno ==9 则表明其pathmax是unLimited,
        if((pathmax = pathconf("/",_PC_PATH_MAX)) < 0)
        {
            if(errno == 0)
                pathmax = PATH_MAX_GUESS;
            else
                err_sys("pathconf error for _PC_PATH_MAX");
        }
        else
            pathmax++;  //add one since it's relative to root;
    }

    /*
     * before POSIX.1-2001.we arenot guaranteed thar PATH_MAX includes
     * the terminating null byte. Same goes for XPG3
     */

    if((posix_version <20112L) && (xsi_version < 4))
        size = pathmax + 1;
    else
        size = pathmax;

    if((ptr = malloc(size)) == NULL)
        err_sys("malloc error for pathname");
    if(sizep != NULL)
        *sizep = size;

    return ptr;

}
