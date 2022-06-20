/*
动态库libxxx.so
g++ -c -fpic  a.cpp b.cpp c.cpp //得到和位置无关的代码
g++ -shared a.o b.o c.o -o libabc.so //得到动态库
g++ main.cpp -o app -L ../library/lib/ -l calc
ldd app
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/yz/code/learnLinux/lesson06/library/lib/
/etc/ld.so.
/usr/lib/
./app 
*/
#include <iostream>
#include "../library/include/head.h"

int main()
{
    std::cout<<add(1,2)<<std::endl;
}