GDB断点调试
prepare:关闭优化，-O，打开调试-g，打开waring-Wall
example：g++ -g -Wall main.cpp -o main //可以映射源代码对应信息
gdb main
set args 10 20
show args
help
//查看代码
list
list 10//行号
list main
list 文件名：行号
list 文件名：函数
show list 
show listsize
set listsize 20
//断点
break 文件名：函数/行号
info break
delete 断点编号
disable 断点编号
enable 断点编号
break main.cpp:10 if i=3  //条件断点
start //第一行
run //遇到断点才会停
continue //下一个断点
next //下一行
step //但不调试，进入函数体
finish //跳出函数体
until //跳出循环
print var_name
ptype var_name
display var_name
undisplay var



