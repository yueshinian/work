#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

/*
set follow-fork-mode child
set detach-on-fork off //阻塞其他进程执行
info inferiors
inferiors 进程编号，不是pid//先continue，后next
detach inferiors 进程编号 //脱离gdb调试，变为非阻塞
*/

int main()
{
    cout<<"start"<<endl;

    pid_t pid = fork();
    if(pid==0){
        cout<<"child process: "<< getpid()<<endl;
        int i=0;
        for(;i<10;++i){
            cout<<"child"<<i<<endl;
            sleep(1);
        }
    }else if(pid>0){
        cout<<"parent process: "<<getpid()<<endl;
        int j=0;
        for(;j<10;++j){
            cout<<"parent"<<j<<endl;
            sleep(1);
        }
    }else {
        perror("fork");
    }
    return 0;
}