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
注意事项：
                    1.只读打开会阻塞，直到写打开
                    2写打开会阻塞，直到读打开
读管道：
                管道有数据，read返回个数
                管道无数据，写端关闭，read返回0
                管道无数据，写端打开ia，read阻塞

写管道：
                管道读端全部关闭，异常退出
                管道读端打开，管道满，阻塞
                                                未满，极速写入
*/

int main()
{
    int ret = open("fifo",O_RDONLY);
    if(ret==-1){
        perror("open");
        exit(1);
    }

    int  len=0;
    char buf [1024]={0};
    while(true){
        bzero(buf,sizeof(buf));
        len=read(ret,buf,sizeof(buf)-1);
        if(len==0){
            break;
        }
        printf("read receive: %s\n",buf);
    }
    close(ret);
    return 0;
}