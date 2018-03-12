#include "apue.h"

int main(void)
{
    char *ptr;
    size_t size;
    if(chdir("~/APUE/linkdir") < 0)
        err_sys("chdir failed");

    ptr = path_alloc(&size);

    if(getcwd(ptr,size) == NULL)
        err_sys("getcwd error");

    printf("cwd:%s\n",ptr);
    exit(0);
}
