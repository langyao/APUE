#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>



int main(void)
{
	int fd;
	int a[1] = {0};
	if((fd = open("test.txt",O_CREAT | O_RDWR | O_TRUNC,0666)) < 0)
	{
		perror("open error");
		return -1;
	}
	write(fd,a,sizeof(int));
    printf("a[0]:%d\n",a[0]);

	TELL_WAIT();

    pid_t pid;
    if((pid = fork()) < 0)
    {
        perror("open error");
        return -1;
    }
    else if(pid == 0)
    {
        while(a[0] < 11)
        {
            WAIT_PARENT();
            int n = lseek(fd,-sizeof(int),SEEK_CUR);
             read(fd,a,sizeof(int));
            a[0]++;
            lseek(fd,-sizeof(int),SEEK_CUR);
            write(fd,a,sizeof(int));
            printf("child is writing:%d\n",a[0]);
            TELL_PARENT(getppid());
        }
    }
    else
    {
        while(a[0] < 10)
        {
            int n = lseek(fd,-sizeof(int),SEEK_CUR);
            read(fd,a,sizeof(a[0]));
            a[0]++;
            lseek(fd,-sizeof(int),SEEK_CUR);
            write(fd,a,sizeof(int));
            printf("parent is writing:%d\n",a[0]);
            TELL_CHILD(pid);
            WAIT_CHILD();
        }
    }


    return 0;

}
