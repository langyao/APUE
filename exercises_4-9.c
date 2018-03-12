#include "apue.h"

int main(void)
{
    char buf[4096];
    int len = sizeof(buf);

    char c;
    int n;

    while((n = read(STDIN_FILENO,&c,1)) > 0)
    {
        if(c == '\0')
            continue;
        if( write(STDOUT_FILENO,&c,1) !=  1)
            err_sys("write error");
    }
    exit(0);
}
