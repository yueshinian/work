#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

/*
进程推出，但是仍然为其保留一些信息，主要是PCB控制块信息（进程号，推出状态，运行时间）
wait() 和waitpid()函数的功能，wait()阻塞，waitpid()不阻塞
pid_t wait(int *wstatus);
功能：等待子进程结束，回收资源
参数：进程退出时的状态信息，传入的是一个int类型的地址，传出参数。
返回值：成功返回进程id
调用wait的进程会被阻塞，直到子进程结束或者信号唤醒
无子进程需要回收时，返回-1
pid_t waitpid(pid_t pid, int *wstatus, int options);
*/

int main()
{
    pid_t  pid;
    for(int i=0;i<5;++i){
        pid = fork();
        if(pid==0) break;
    }
    if(pid>0){
        while(1){
            cout<<"parent: "<<getpid()<<endl;
            int st;
            int ret = wait(&st);
            cout<<"wait: "<<ret<<endl;
            if(ret==-1){
                break;
            }
            if(WIFEXITED(st)){
                cout<<"正常退出"<<WEXITSTATUS(st)<<endl;
            }
            sleep(1);
        }
    }else if(pid==0){
        //while(1){
            cout<<"child: "<<getpid()<<endl;
            sleep(1);
        //}
        exit(0);
    }else{
        perror("fork");
    }
    return 0;
}