#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
using namespace std;
/*
211
管道是一个内存内核中维护的一个缓冲器，能力有限，不同操作系统大小不同
具有文件特质：读写操作，匿名管道没有文件实体，又名管道有文件实体
一个管道是一个字节流，可以读取任意大小顺序块，
管道传递的数据时有顺序，环形队列
半双工，一端用于读取，一段用与写入，数据传递单向
读取数据一次性读取，无法随即访问
只能在具有公共祖先的进程之间使用
                原因：共享文件案描述符
212
int pipe(int pipefd[2]);
                pipefd：传出数据，pipefd[0]是读端，pipefd[1]是写端
                返回值：成功0，失败-1
214
假设都是阻塞IO
1写端都关闭，进程读取返回值是0，len=read()==0,
2如果写端没有关闭，也没有写数据，数据读取完毕后，read会阻塞，
3如果所有指向读端的文件描述符都关闭了，写端写入，进程会收到一个信号SIGPIPE，进程异常终止
4存在读端，但是没有读取，此时写入数据，写满时，write只有空闲才可以再写入
*/

int main()
{
    int pipefd[2];
    int ret = pipe(pipefd);
    if(ret==-1){
        perror("pipe");
        exit(0);
    }
    //pipe size
    long size  = fpathconf(pipefd[0],_PC_PIPE_BUF);
    cout<<"pipe size is "<<size<<endl;
     pid_t pid = fork();
    if(pid>0){
        cout<<"parent: "<<getpid()<<endl;
        char buf[1024]={0};
        //while(1){
            close(pipefd[1]);
            int len =0;
            /*
            read非阻塞设置
            */
           //int flags =  fcntl(pipefd[0],F_GETFL);
           //flags |= O_NONBLOCK;
           //fcntl(pipefd[0],F_SETFL,flags);
            while( (len= read(pipefd[0],buf,sizeof(buf)))>0){
                printf("%s",buf);
            }
            // char *str1 = "hello child";
            // write(pipefd[1],str1,strlen(str1));
        //}
    }else if(pid==0){
        cout<<"child: "<<getpid()<<endl;
        //while(1){
            close(pipefd[0]);
            dup2(pipefd[1],STDOUT_FILENO);
            execlp("ps","ps","aux",NULL);
            //char *str = "hello parent";
            //write(pipefd[1],str,strlen(str));
            sleep(10);
        //}
    }else{
        perror("fork");
        exit(0);
    }
    return 0;
}

