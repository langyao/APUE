#include "apue.h"
#include <fcntl.h>

int main(void)
{
    umask(0);
    if(creat("foo",0666) < 0)
        err_sys("creat foo err");


    umask(0017);

   if(creat("bar",0666) < 0)
      err_sys("create bar error");

    exit(0);

}
