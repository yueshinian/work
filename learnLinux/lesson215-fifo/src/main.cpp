#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
/*
有名管道，路径名关联，通过文件交流
命令：mkfifo 文件名
int mkfifo(const char *pathname, mode_t mode);
    参数：路径，权限
    返回值：-1
*/

int main()
{
    int ret = access("fifo",F_OK);
    if(ret==-1){
        ret = mkfifo("fifo",0777);
        if(ret==-1){
            perror("mkfifo");
            exit(0);
        }
    }

    int fd = open("fifo",O_WRONLY);
    if(fd==-1){
        perror("open");
        exit(0);
    }
    for(int i=0;i<10;++i){
        char* str = "hello read!";
        write(fd,str,strlen(str));
        sleep(1);
    }
    close(fd);
    return 0;
}