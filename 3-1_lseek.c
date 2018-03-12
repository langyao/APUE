//test offset avaiable

#include "apue.h"

int main(void)
{
    if(lseek(STDIN_FILENO,0,SEEK_CUR) == -1)
        printf("seek err\n");
    else
        printf("seek OK\n");
    exit(0);
}
