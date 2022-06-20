/*
信号：事件发生时对进程的通知机制，软件中断，异步通信
通常都是源于内核，各类事件如下：
    前台进程，用户输入特殊字符，如ctrl+C，中断信号
    硬件异常，0除，使用非法内存
    系统状态变化，比如alarm定时器，子进程退出
    运行kill命令或kill函数
信号目的：
    让进程知道已经发生了一个特定的事情；
    强迫进程执行中断处理程序。
信号特点：
    使用简单
    不能携带大量信息
    满足某个特定条件才能发送
    优先级比较高
查看信号列表：
    kill -l
    前31个信号为常规信号，其余为实时信号,未定义，使用时定义，前面31个应用较多
5个默认动作
    term-终止进程
    ign-忽略
    core-终止并写入文件案
    stop-暂停当前进程
    cont-继续执行当前被暂停的进程
3个状态：
    产生，未决，递达
SIGNKILL和SIGNSTOP不可以被阻塞，只能送达
core-file core
*/

/*
int kill(pid_t pid, int sig);
    功能：给任何进程或者进程组发送信号
    参数：
        pid：>0，进程名，==0，当前进程组
        0不发送任何
int raise(int sig);
功能：当前进程

void abort(void);
功能:结束当前进程

unsigned int alarm(unsigned int seconds);
功能：设置定时器，结束进程，非阻塞
实际时间：内核时间（定时器时间）+用户时间+消耗的时间，进行IO操作的时候比较耗费时间
参数：单位s，0无效
返回值：定时器剩余时间。
重复调用会覆盖之前的定时器，且返回值为上一个定时器剩余时间。
*/

/*
int getitimer(int which, struct itimerval *curr_value);
int setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value);
功能：设置定时器，精读us，周期定时
参数：which，计时方式，ITIMER_REAL,ITIMER_VIRTUAL,ITIMER_PROF,，真实时间SIGALARM用户时间
            new_value
            struct itimerval {
               struct timeval it_interval; Interval for periodic timer 每个阶段的时间，间隔时间 
               struct timeval it_value;     Time until next expiration  延迟多长时间执行定时器
           };

           struct timeval {
               time_t      tv_sec;          seconds 
               suseconds_t tv_usec;         microseconds 
           };
           old_value：记录上一次的时间
返回值：成功0，失败-1

*/

/*
信号捕捉
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
功能：设置某个信号的捕捉行为
参数：signum：要捕捉的信号,无法出卓SIG_KILL和SIG_STOP
            处理方式：SIG_IGN忽略
                                    SIG_DEL使用信号默认的行为
                                    回调函数，内核调用
返回值：失败返回SIG_ERR
*/

/*
信号集：PCB区域阻塞信号集和未决信号集，未决：开始到产生，阻塞：暂停;存储在64位图中
信号未处理前都在未决信号集，不断查询阻塞信号集，看是阻塞还是执行
e.g.用户通过ctrl+c，产生2号信号，
        信号产生但是没有被处理，
        被存储在第二个标志位，1，未决状态，去查找阻塞信号集，0是非阻塞，信号被处理，；1是阻塞，直至等代被处理
阻塞信号集，默认不阻塞，
自定义信号集处理
int sigemptyset(sigset_t *set)
        功能：清空信号集，重置为0
        参数：传出参数，需要操作的信号集
        返回值：成功与否
int sigaddset(*set, int signum)
        功能：阻塞信号
int sigdelset(*set, int signum)
        功能：设置非阻塞
int sigismember(*set, int signum)
        功能：判断某个信号是否阻塞
        返回值：1阻塞0非阻塞-1错误
*/

/*
内核信号集处理
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
    功能：自定义信号集设置到内核中
    参数：how
            SIG_BLOCK：阻塞，mask | set
            SIG_UNBLOCK：非阻塞 mask&=~set
            SIG_SETMASK:自定义信号集替换
            set:传入参数，自定义信号集
            oldset:之前的信号集，可以使NULL
    返回值：成功与否
int sigpending(*set)
    功能：获取内核中的未决信号集，set传出参数
*/
#include <iostream>
#include <string>
#include <cstring>

#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h>

void myalarm(int num)
{
    std::cout << "捕捉到了信号： " << num << std::endl;
}

int main()
{
    /*
    core异常查看
    //char *buf;
    //strcpy(buf,"hello world");
    */
    /*
   定时器
    int seconds = alarm(5);
    std::cout<<"alarm = "<<seconds<<std::endl;
    */
    /*
    pid_t pid = fork();
    if(pid>0){
        sleep(6);
        std::cout<<"finish process"<<std::endl;
        kill(pid,9);
    }else if(pid==0){
        for(int i=0;i<10;++i){
            std::cout<<"child "<<i<<std::endl;
            sleep(1);
        }
    }else {
        exit(0);
    }
    */
    //定时器setitimer以及定时器捕捉signal
    /*
    signal(SIGALRM,myalarm);
   struct itimerval new_value;
    new_value.it_interval.tv_sec = 2;
    new_value.it_interval.tv_usec = 0;
    new_value.it_value.tv_sec=3;
    new_value.it_value.tv_usec = 0;
   int ret = setitimer(ITIMER_REAL, &new_value,NULL);
   if(ret==-1){
       perror("setitimer");
       exit(0);
   }
   getchar();
   */
    //信号集操作,自定义信号集
    /*
    sigset_t set;
    sigemptyset(&set);
    int ret = sigismember(&set, SIGINT);
    if (ret == -1)
    {
        exit(0);
    }
    else if (ret == 0)
    {
        std::cout << "非阻塞" << std::endl;
    }
    else if (ret == 1)
    {
        std::cout << "阻塞" << std::endl;
    }
    //添加信号到信号集
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);

    ret = sigismember(&set, SIGINT);
    if (ret == -1)
    {
        exit(0);
    }
    else if (ret == 0)
    {
        std::cout << "非阻塞" << std::endl;
    }
    else if (ret == 1)
    {
        std::cout << "阻塞" << std::endl;
    }

    sigdelset(&set, SIGINT);

    ret = sigismember(&set, SIGINT);
    if (ret == -1)
    {
        exit(0);
    }
    else if (ret == 0)
    {
        std::cout << "非阻塞" << std::endl;
    }
    else if (ret == 1)
    {
        std::cout << "阻塞" << std::endl;
    }
    */
   //把所有的常规信号(1-31)的未决状态打印到屏幕
   sigset_t set;
   sigemptyset(&set);
   sigaddset(&set,SIGINT);
   sigaddset(&set,SIGQUIT);
   
   sigprocmask(SIG_BLOCK,&set,NULL);
   int num = 0;
   while(1){
       sigset_t pendingset;
       sigemptyset(&pendingset);
       sigpending(&pendingset);
       for(int i=1;i<32;++i){
           if(sigismember(&pendingset,i)==1){
               std::cout<<"1";
           }else if(sigismember(&pendingset,i)==0){
               std::cout<<"0";
           }else {
               exit(0);
           }
       }
       sleep(1);
       std::cout<<std::endl;
       ++num;
       if(num==10){
           sigprocmask(SIG_UNBLOCK,&set,NULL);
       }
   }
    return 0;
}