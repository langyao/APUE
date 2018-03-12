#include "apue.h"

#define BSZ 48

int main()
{
    FILE *fp;
    char buf[BSZ];

    memset(buf,'a',BSZ - 2);
    buf[BSZ - 2] = '\0';
    buf[BSZ-1] = 'X';
    if((fp = fmemopen(buf,BSZ,"w+")) == NULL)  //fmemopen在缓冲区开始处放置null字节
        err_sys("fmemopen error");

    printf("initial buffer contents: %s\n",buf);
    fprintf(fp,"hello world");

    printf("before flush: %s\n",buf);  //冲洗前不会有变化
    fflush(fp);
    printf("after fflush:%s\n",buf);
    printf("len of string in buf = %ld\n",(long)strlen(buf));





    memset(buf,'b',BSZ - 2);
    buf[BSZ - 2] = '\0';
    buf[BSZ-1] = 'X';

    fprintf(fp,"hello world");
    fseek(fp,0,SEEK_SET);
    printf("after fseek: %s\n",buf);  //冲洗前不会有变化
    printf("len of string in buf = %ld\n",(long)strlen(buf));





    memset(buf,'c',BSZ - 2);
    buf[BSZ - 2] = '\0';
    buf[BSZ-1] = 'X';

    fprintf(fp,"hello world");
    fclose(fp);

    printf("after fclose:%s\n",buf);
    printf("len of string in buf = %ld\n",(long)strlen(buf));
    return (0);
}
