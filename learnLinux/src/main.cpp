/*
g++  main.cpp -E -o test.i  //预编译，预处理
g++ test.i -S -o test.s  //生成汇编
g++ test.s -s -o test.o  //生成可执行文件
g++ main.cpp  -o test -DDEBUG //相当于主程序定义了#define DEBUG ,程序中#ifdef DEBUG
g++ main.cpp -o test  -Wall //all warning
g++ main.cpp -o test -On //n=0,不优化，1，2，3优化等级逐渐增高
-L
-fpic
-shared
-std=c11//C++标准
1.4静态库的制作
命名规则：libxxx.a
流程：.o文件-》ar rcs libxxx.a xxx.o xxx.o  //rcs，将文件插入备存文件中，建立北村文件，索引
*/


#include <iostream>

using namespace std;

int main()
{
    cout<<"hello world"<<endl;
    return 0;
}