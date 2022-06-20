#include <iostream>
//open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//close
#include <stdio.h>
//perror
//read
#include <unistd.h>
//opedir
#include <dirent.h>
#include <string.h>
using namespace std;

/*
int open(const char *pathname, int flags);//打开已经存在文件（路径，操作权限（O_RANDLY,O_WRONLY,O_RDWR））
返回值，-1代表错误
#include <stdio.h>
void perror(const char *s);
int open(const char *pathname, int flags, mode_t mode);//flags=r,w,rw,O_CREAT创建文件,mode=权限0777会与umask与

ssize_t read(int fd, void *buf, size_t count);//文件描述符，数组形式的数据缓冲区，buf大小
ssize_t write(int fd, const void *buf, size_t count);//文件描述符，数组大小，buf大小
返回值：读取或者写入字节数量

off_t lseek(int fd, off_t offset, int whence);//文件描述符，偏移量，
SEEK_SET
              The file offset is set to offset bytes.

       SEEK_CUR
              The  file  offset  is  set  to  its current location plus offset
              bytes.

       SEEK_END
              The file offset is set to the  size  of  the  file  plus  offset
              bytes.
移动文件指针到文件头fd,0,SEEK_SET
获取文件指针位置fd,0,SEEK_CUR
获取指针文件末尾fd,0,SEEK_END
扩展文件长度fd,100,SEEK_END

int stat(const char *pathname, struct stat *statbuf);
nt fstat(int fd, struct stat *statbuf);
int lstat(const char *pathname, struct stat *statbuf);//获取文件相关信息，
return value:0/-1

int access(const char *pathname, int mode);//判断文件权限，（文件路径，要判断的权限R_OK,W_OK,X_OK.F_OK判断文件是否存在
return value:success is 0,fial is -1

int chmod(const char *pathname, mode_t mode);//mode八进制数
nt fchmod(int fd, mode_t mode);

int chown(const char *pathname, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);
int lchown(const char *pathname, uid_t owner, gid_t group);
//改变文件大小
int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);
//创建目录
int mkdir(const char *pathname, mode_t mode);//文件目录，权限rwx
return value: success is 0, fail is-1

int rmdir(const char *pathname);

int rename(const char *oldpath, const char *newpath);
//修改进程工作目录
int chdir(const char *path);
int fchdir(int fd);
//获取工作目录
char *getcwd(char *buf, size_t size);
char *getwd(char *buf);
char *get_current_dir_name(void);

DIR *opendir(const char *name);
//目录流信息
DIR *fdopendir(int fd);
//读取目录
struct dirent *readdir(DIR *dirp);
//close
 int closedir(DIR *dirp);

//复制文件描述符
int dup(int oldfd);//类似于新指针指向同一个文件，前拷贝
重定向文件描述符
int dup2(int oldfd, int newfd);
//复制文件描述符，类似dup；设置或者获取flags
int fcntl(int fd, int cmd, ... * arg *);
fd：文件描述符；
cmd：表示对文件描述符的操作
        F_DUPFD：复制文件描述符
        F_GETFL: 获取flag，和open时的flag一致
        F_SETFL:设置flag
                        O_APPEND:追加数据
                        O_NONBLOCK:设置成非阻塞
*/

int getPathName(const char* pathname)
{
    DIR* dir = opendir(pathname);
    if(dir==NULL){
        perror("opendir");
        exit(0);
    }
    struct dirent *ptr;
    int total = 0;
    while((ptr=readdir(dir))!=NULL){
        char *dname = ptr->d_name;
        if(strcmp(dname,".")==0 || strcmp(dname,"..")==0){
            continue;
        }
        if(ptr->d_type == DT_DIR){
            char newpath[256];
            sprintf(newpath,"%s/%s",pathname,dname);
            total+=getPathName(newpath);
        }else if(ptr->d_type==DT_REG){
            total++;
        }
    }
    closedir(dir);
    return total;
}

int main()
{
    int srcfd = open("../readme.txt",O_RDONLY);
    if(srcfd==-1){
        perror("open");
        return -1;
    }
    int targetfd = open("create.txt",O_RDWR | O_CREAT, 0777);
    if(targetfd==-1){
        perror("open");
        return -1;
    }
    char buf[1024]={0};
    int len = 0;
    while( (len = read(srcfd,buf,1024))>0){
        write(targetfd,buf,1024);
    }
    int ret = lseek(targetfd,1024,SEEK_END);
    write(targetfd," ",1);
    close(targetfd);
    close(srcfd);
    struct stat statbuf;
    stat("create.txt",&statbuf);
    cout<<statbuf.st_size<<endl;
    int res = access("create.txt",F_OK);
    if(res==-1){
        perror("access");
    }else{
        int res_mod = chmod("create.txt",0775);
        if(res_mod==-1){
            perror("chmod");
        }
    }
    int ret_trun = truncate("create.txt",65535);
    if(ret_trun==-1){
        perror("truncate");
    }
    stat("create.txt",&statbuf);
    cout<<statbuf.st_size<<endl;
    int ret_mkdir  = mkdir ("aaa",0777);
    if(ret_mkdir==-1){
        perror("mkdir");
    }
    cout<<"pathNum"<<getPathName("/home/yz/code/learnLinux/")<<endl;
    int fd129 = open("create.txt",O_RDWR | O_CREAT,0777);
    if(fd129==-1){
        perror("open");
        return -1;
    }
    int fd130 = dup(fd129);
    cout<<fd129<<" "<<fd130<<endl;
    int fd131 = open("b.txt",O_CREAT | O_RDWR,0777);
    if(fd131==-1){
        perror("open");
        return -1;
    }
    int fd132 = dup2(fd129,fd131);
    if(fd132==-1){
        perror("dup2");
        return -1;
    }
    char *str = "hello world";
    write(fd131,str,strlen(str));

    close(fd129);
    close(fd131);

    int fd133 = open("1.txt", O_CREAT | O_RDWR, 0777);
    if(fd133==-1){
        perror("open");
    }

    int flag = fcntl(fd133,F_GETFL);
    flag |= O_APPEND;
    int ret133 = fcntl(fd133,F_SETFL,flag);
    if(ret133==-1){
        perror("fcntl");
    }
    char *str133 = "hello world 133";
    write(fd133,str,strlen(str));
    close(fd133);
    return 0;
}

