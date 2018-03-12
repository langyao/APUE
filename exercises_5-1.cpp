#include "apue.h"


void setbuf(FILE *restrict fp, char *restrict buf)
{
    int mode;
    if(buf == NULL)
    {
        mode = _IONBF;
    }
    else
    {
        mode  = _IOFBF;
    }
    setvbuf(fp,buf,mode,BUFSIZ);
}

int main(void)
{
    FILE *fd = fopen(fp,);

}
