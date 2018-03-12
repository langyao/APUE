#include "apue.h"
#include <fcntl.h>

int main(int argc , char **argv)
{
#ifdef LINK
    if(link("hell.c","aa") < 0)
        err_sys("link error for hell.c");
#endif
#ifdef SLINK
    if(symlink(argv[1],argv[2]) < 0)
        err_sys("symlink error");
#endif

    exit(0);

}
