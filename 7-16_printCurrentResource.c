#include "apue.h"
#include <sys/resource.h>

#define doit(name) pr_limits(#name,name)

static void pr_limits(char*,int);


int main(void)
{
#ifdef RLIMIT_AS //进程总的可用存储空间
    doit(RLIMIT_AS);
#endif

    doit(RLIMIT_CORE);  //core文件的最大字节数
    doit(RLIMIT_CPU);  //CPU时间的最大量值
    doit(RLIMIT_DATA); //数据段的最大字节长度 (初始化 非初始化 以及堆的总和)
    doit(RLIMIT_FSIZE); //可以创建的最大文件字节数

#ifdef RLIMIT_MEMLOCK
    doit(RLIMIT_MEMLOCK);  //锁定在存储空间中的最大字节数
#endif

#ifdef RLIMIT_MSGQUEUE
    doit(RLIMIT_MSGQUEUE); //进程为POSIX消息队列可分配的最大字节数
#endif

#ifdef RLIMIT_NICE
        doit(RLIMIT_NICE);  //为了影响进程的调度优先级，nice值可设置的最大限度
#endif

    doit(RLIMIT_NOFILE); //每个进程能打开的最大文件数 sysconf在参数_SC_OPEN_MAX中返回的值

#ifdef RLIMIT_NPROC
    doit(RLIMIT_NPROC); //每个实际用户ID可拥有的最大子进程数 syscinf在参数_SC_CHILD_MAX中返回值
#endif

#ifdef RLIMIT_NPTS
    doit(RLIMIT_NPTS);  //用户可同时打开的伪终端的最大数量
#endif

#ifdef RLIMIT_RSS
    doit(RLIMIT_RSS); //最大驻内存集字节长度
#endif

#ifdef RLIMIT_SBSIZE
    doit(RLIMIT_SBSIZE); //用户占据的套接字缓冲区的最大长度（字节）
#endif

#ifdef RLIMIT_SIGPENGDING
    doit(RLIMIT_SIGPENGDING); //一个进程可排队的信号最大数量
#endif

#ifdef RLIMIT_STACK
    doit(RLIMIT_STACK); //栈的最大字节长度
#endif

#ifdef RLIMIT_SWAP
    doit(RLIMIT_SWAP); //用户可消耗的交换空间的最大字节数
#endif

#ifdef RLIMIT_VMEM
    doit(RLIMIT_VMEM); //同RLIMIT_AS
#endif

    exit(0);
}

static void pr_limits(char *name, int resource)
{
    struct rlimit limit;
    unsigned long long lim;

    if(getrlimit(resource,&limit) < 0)
        err_sys("getrlimit error for %s",name);

    printf("%-15s ",name);

    if(limit.rlim_cur == RLIM_INFINITY)
        printf("(infinate) ");
    else
    {
        lim = limit.rlim_cur;
        printf("%10lld ",lim);
    }

    if(limit.rlim_max == RLIM_INFINITY)
        printf("(infinate)");
    else
    {
        lim = limit.rlim_max;
        printf("%10lld",lim);
    }

    putchar((int)'\n');

}

