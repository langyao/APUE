#include "apue.h"

int main(void)
{
    if(system("/bin/ed") < 0)
        err_sys("system() error");
    while(1);
    exit(0);
}
