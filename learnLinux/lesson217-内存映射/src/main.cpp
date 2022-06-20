#include <iostream>
#include <unistd.h>
#include <sys/types.h>
 #include <sys/mman.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <cstring>
 #include <sys/wait.h>
/*
将磁盘指定数据映射到内存，用户通过修改内存就可以修改磁盘数据，效率高于有名管道mkfifo
非阻塞方式
//将一个文件或者内存映射到内存中
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
    参数：
        addr:NULL,内核指定
        -length: 映射的数据长度，大于0。建议使用文件长度，但是最少分页的大小
            获取文件的长度：stat，lseek
        prot：映射区分配内存的权限
            PORT_EXEC,PORT_READ,PROT_WRITE,PROT_NONE，一般读写权限
        flags：
            MAP_SHARED：内存磁盘自动同步修改
            MAP_PRIVATE：不同步，读时共享，写时复制
        fd：需要映射的文件描述符
            通过open得到，大小不能为0，prot的权限要小于open的权限
        offset：偏移量，一般不用，必须是4k的整数倍
返回值：返回内存映射的首地址，失败返回void*，MAP_FAILED
//解除映射 
int munmap(void *addr, size_t length);
参数：addr，要释放的内存的首地址
lenght：要释放的内存大小，和mmap大小一致
*/

/*
1。ptr++，操作可以，但是不建议，但是释放不能正确释放，munmap(ptr,size)。++操作之前保存地址。
2。open时O_RDONLY,但是PROT_READ,PROT_WRTE，错误，返回MAP_FAILED
3.文件偏移量是1000会怎么样，必须时4k的整数倍，错误返回，所以最小4k
4。调用失败的情况，size大小为0，权限大于open
5.open一个新文件，lseek（），truncate（）扩展大小 
6.mmap关闭文件后的影响，对mmap么有影响
7.对ptr越界操作，操作的非法内存，会出现段错误。
*/
int main()
{
    int fd = open("readme.txt",O_RDWR);
    if(fd==-1){
        perror("open");
        exit(0);
    }
    int size = lseek(fd,0,SEEK_END);
    if(size<=0){
        std::cout<<"shared txt size is 0!"<<std::endl;
    }
    void *ptr = mmap(NULL,size,PROT_READ| PROT_WRITE,MAP_SHARED,fd,0);
    if(ptr==MAP_FAILED){
        perror("mmap");
        exit(0);
    }

    pid_t pid =  fork();
    if(pid>0){
        strcpy((char *)ptr,"hello world！！！");
        wait(NULL);
    }else if(pid==0){
        char buf[1024] ={0};
        strcpy(buf,(char *)ptr);
        printf("%s\n",buf);
    }
    munmap(ptr,size);

    int fd1 = open("source.txt",O_CREAT | O_RDWR);
    if(fd1==-1){
        perror("open");
        exit(-1);
    }
    char *str1 = "hello 218";
    write(fd1,str1,strlen(str1));
    int len1 = lseek(fd1,0,SEEK_END) ;
    void* ptr1 = mmap(NULL,len1,PROT_READ | PROT_WRITE,MAP_SHARED,fd1,0);
    char buf1[1024]={0};
    strncpy(buf1,(char *)ptr1,len1-1);

    int fd2 = open("target.txt",O_CREAT | O_RDWR);
    truncate("target.txt",len1);
    void* ptr2 = mmap(NULL,len1,PROT_READ | PROT_WRITE,  MAP_SHARED,fd2,0);
    strncpy((char *)ptr2,buf1,sizeof(buf1)-1);

    munmap(ptr1,len1);
    munmap(ptr2,len1);
    close(fd1);
    close(fd2);
    /*
    匿名映射:不需要文件实体，但是只能用在父子进程之间
    只需要fd=-1
    */

    return 0;
}