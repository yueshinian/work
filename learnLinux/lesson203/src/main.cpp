/*
int main()
{
   pid_t pid = fork();
   if(pid>0){
       printf("is patent.its pid is %d father pid is %d\n",getpid(),getppid());
       //大于0，返回的是创建的子进程的pid号，当前是父进程
   }else if(pid==0){
       //当前是子进程
       printf("is child.its pid is %d father pid is %d\n",getpid(),getppid());
   }

    //父子进程都可执行
    for(int i=0;i<10;++i){
        printf("current pid is %d\n",getpid());
        sleep(1);
    }
    return 0;
}
*/
/*
父进程执行2-19
子进程5-19，执行fork之后的函数，复制父进程的地址空间
相同：用户区相同，内核区不同，即pid不同，原因：变量初始值相同，后续操作互不相同。
但是会共享文件内存空间，因为是物理 内存，文件指针会增加，写时拷贝
区别：pid不同，信号集不同
相同：用户区的数据，文件描述符表，读时共享，写时拷贝
*/


#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
    /*
    创建子进程
    pid_t fork(void);
    return value:
                    在父进程中返回创建的子进程ID，在子进程中返回0，区分父子进程，
                    父进程创建失败返回-1，达到上限，内存不足
    */
   pid_t pid = fork();
   if(pid>0){
       printf("is patent.its pid is %d father pid is %d\n",getpid(),getppid());
       //大于0，返回的是创建的子进程的pid号，当前是父进程
   }else if(pid==0){
       //当前是子进程
       printf("is child.its pid is %d father pid is %d\n",getpid(),getppid());
   }

    //父子进程都可执行
    for(int i=0;i<10;++i){
        printf("current pid is %d\n",getpid());
        sleep(1);
    }
    return 0;
}