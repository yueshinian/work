#include <iostream>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

/*
exec函数族，在进程内部执行一个可执行文件，并用其来代替当前进程内容（用户区），
用户区代码段、数据段和堆栈都被取代，
不太合理，所以在子进程执行，不会覆盖原父进程内容，
执行成功后不会返回值，出错返回值-1，设置error
标准C库函数
int execl(const char *path, const char *arg, ...(char  *) NULL *);
    - 参数：
        path-路径
        arg-执行程序需要的参数，第一个参数无作用，用名字代替，第二个参数开始用作用，以NULL结尾
int execlp(const char *file, const char *arg, ...(char  *) NULL );
    -参数
        file:文件名，可诶从环境变量中查找，可以直接写ps
        后参数一致
*/

int main()
{
    pid_t pid = fork();
    if(pid==0){
        cout<<"child process: "<<getpid()<<endl;
        //execl("test1","test1",NULL);
        //execl("/bin/ps","ps","aux",NULL);
    }else if(pid>0){
        cout<<"parent process: "<<getpid()<<endl;
        sleep(1);
    }else {
        perror("fork");
    }
    for(int i=0;i<10;++i){
        cout<<i<<" "<<getpid()<<endl;
    }
    return 0;
}