//setvbuf to realize setbuf
#include "apue.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>

#if defined(_IO_UNBUFFERD)
int is_unbuffered(FILE *fp)
{
    return (fp->_flags & _IO_UNBUFFERED);
}

int is_linebuffered(FILE *fp)
{
    return (fp->_flags & _IO_LINE_BUF);
}

int buffer_size(FILE *fp)
{
    return (fp->_IO_buf_end - fp->_IO_buf_base);
}

#elif defined(_SNBF)

int is_unbuffered(FILE *fp)
{
    return (fp->_flags & _SNBF);
}


int is_linebuffered(FILE *fp)
{
    return (fp->_flags & _SLBF);
}

int buffer_size(FILE *fp)
{
    return (fp->_bf._size);
}

#elif defined(_IONBF)
#ifdef _LP64
#define _flag  __pad[4]
#define _ptr  __pad[1]
#define _base  __pad[2]
#endif


int is_unbuffered(FILE *fp)
{
    return (fp->_flag & _IONBF);
}


int is_linebuffered(FILE *fp)
{
    return (fp->_flag & _IOLBF);
}

int buffer_size(FILE *fp)
{
#ifdef _LP64
    return (fp->_base - fp->_ptr);
#else
    return BUFSIZ;
#endif
}

#else

#error unknown stdio implementation!

#endif



void mysetbuf(FILE *fp, char *buf)
{
    int error;
    if(buf == NULL)
        error = setvbuf(fp,buf,_IONBF,BUFSIZ);
    else if(fp == stdin || fp == stdout || fp == stderr)
        error = setvbuf(fp,buf,_IOLBF,BUFSIZ);
    else
        error = setvbuf(fp,buf,_IOFBF,BUFSIZ);

    if(error != 0)
        perror("setvbuf error");

}

void pr_stdio(const char *name,FILE *fp)
{
    printf("stream = %s, ",name);
    if(is_unbuffered(fp))
        printf("unbuffered\n");
    else if(is_linebuffered(fp))
        printf("linebuffered");
    else
        printf("fully buffered");
    printf(",buffer size = %d\n", buffer_size(fp));
}

int main()
{
    int fp;
    fp = fopen("hello.c","w+");
    if(getc(fp) == EOF)
        err_sys("getc error");
    pr_stdio("hello.c",fp);

    char buf[BUFSIZ];
    mysetbuf(fp,NULL);

    if(getc(fp) == EOF)
        err_sys("getc error");
    pr_stdio("hello.c",fp);

    exit(0);
}
