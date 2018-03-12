//递归降序遍历目录


#include "apue.h"
#include <dirent.h>
#include <limits.h>

typedef int Myfunc(const char *pathname, const struct stat *statptr, int type);

static Myfunc myfunc;

static int myftw(char*, Myfunc*);
static int dopath(Myfunc *);
static long nreg,ndir,nblk,nchar,nfifo,nslink,nsock,ntot;

enum
{
    FTW_F,  //file other than directory
    FTW_D,   //directory
    FTW_DNR, //directory thar can not be read
    FTW_NS   //file that cna not stat

};

static char *fullpath;
static size_t pathlen;

int main(int argc,char *argv[])
{
    int ret;
    if(argc < 2)
    {
        err_quit("usage: ftw <starting pathname>");
    }

    ret = myftw(argv[1],myfunc);

    ntot =  nreg + ndir + nblk + nchar + nfifo + nslink + nsock;

    if(ntot == 0)
        ntot = 1;

    printf("regular files = %7ld, %5.2f %%\n",nreg,nreg*100.0/ntot);
    printf("directories   = %7ld, %5.2f %%\n",ndir,ndir*100.0/ntot);
    printf("block special = %7ld, %5.2f %%\n",nblk,nblk*100.0/ntot);
    printf("char special  = %7ld, %5.2f %%\n",nchar,nchar*100.0/ntot);
    printf("symbolic link = %7ld, %5.2f %%\n",nslink,nslink*100.0/ntot);
    printf("socks         = %7ld, %5.2f %%\n",nsock,nsock*100.0/ntot);
    printf("fifos         = %7ld, %5.2f %%\n",nfifo,nfifo*100.0/ntot);


    exit(ret);

}

static int myftw(char *pathname,Myfunc *func)
{
    //系统中最长文件路径长度
    fullpath = path_alloc(&pathlen);

    if(pathlen < strlen(pathname) )
    {
        pathlen = strlen(pathname)*2;
        if((fullpath = realloc(fullpath,pathlen)) == NULL)
            err_sys("realloc error");
    }
    strcpy(fullpath,pathname);
    return dopath(func);

}

static int dopath(Myfunc *func)
{
    struct stat buf;
    struct dirent *dirp;
    DIR *dp;
    int ret,n;

    if(lstat(fullpath,&buf) <  0)
    {
        return func(fullpath,&buf,FTW_NS);
    }

    if(S_ISDIR(buf.st_mode) == 0) //not a directory
        return func(fullpath,&buf,FTW_F);

    //目录文件+1
    if((ret = func(fullpath,&buf,FTW_D)) !=  0)
        return ret;


    //tell the length
    n = strlen(fullpath);
    if(n + NAME_MAX + 2 > pathlen)
    {
        pathlen *= 2;
        if((fullpath = realloc(fullpath,pathlen)) == NULL)
            err_sys("realloc failed");
    }

    fullpath[n++] = '/';
    fullpath[n] = 0;

    if((dp = opendir(fullpath)) == NULL)
        return func(fullpath,&buf,FTW_DNR); // can not read directory

    while((dirp = readdir(dp)) != NULL)
    {
        if(strcmp(".",dirp->d_name) == 0 || strcmp("..",dirp->d_name) == 0)
            continue;
        strcpy(&fullpath[n],dirp->d_name);
        if((ret = dopath(func)) != 0)
            break;
    }

    fullpath[n-1] = '\0';

    if(closedir(dp) < 0)
        err_ret("can not close directory %s",fullpath);

    return ret;
}

static int myfunc(const char *pathname, const struct stat *statptr, int type)
{

    switch(type)
    {
        case FTW_F:
            printf("%s\n",pathname);
            switch(statptr->st_mode & S_IFMT)
            {
                case S_IFREG:
                    nreg++;break;
                case S_IFBLK:
                    nblk++;break;
                case S_IFCHR:
                    nchar++;break;
                case S_IFIFO:
                    nfifo++;break;
                case S_IFSOCK:
                    nsock++;break;
                case S_IFLNK:
                    nslink++;break;
                case S_IFDIR:
                    err_dump("for S_IFDIR for %s",pathname);
            }
            break;
        case FTW_D:
            ndir++;
            break;
        case FTW_DNR:
            err_ret("can not read directory %s",pathname);
            break;
        case FTW_NS:
            err_ret("stat error for %s",pathname);
            break;
        default:
            err_dump("unknown type %d for pathname %s",type,pathname);
    }
    return 0;
}
