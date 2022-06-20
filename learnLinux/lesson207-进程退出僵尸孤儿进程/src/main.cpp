#include <iostream>

#include <unistd.h>
#include <sys/types.h>

using namespace std;

/*
stdio.h-------exit(int status)//刷新IO缓冲区
unistd.h------_exit(int status)
status:进程推出时的状态

孤儿进程：父进程结束，子进程运行中，把孤儿进程的父进程设置为init，init会循环wait（）等待
没什么危害
僵尸进程：子进程结束，父进程对子进程没有进行资源回收
危害：占用进程id号，达到上限，kill -9无法杀死
*/

int main()
{
    pid_t pid = fork();
    if(pid>0){
        cout<<"parent"<<getpid()<<endl;
        while(1){
            cout<<"parent"<<endl;
            sleep(1);
        }
    }else if(pid==0){
        cout<<"child"<<getpid()<<endl;
        //sleep(2);
        cout<<"finished"<<getppid()<<endl;
    }
    return 0;
}