#include "apue.h"

int main(int argc, char *argv[])
{
    int i;
    char **ptr;
    extern char **environ;

    for(i = 0; i < argc; ++i)
    {
        printf("agrv[i] = %s\n",argv[i]);
    }

    i = 0;
    for(ptr = environ; *ptr != NULL;++ptr)
    {
        printf("environ[i++] = %s\n",*ptr);
    }

    exit(0);
}
