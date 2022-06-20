makefile自动编译，多个文件，先后顺序，检查重复编译
app: add.cpp mult.o #规则，生成文件和依赖
    g++ add.cpp mult.o -o app#命令
mult.o:mult.cpp#检查不到mult.o向下查找
    g++ -c mult.cpp -o mult.o
自定义变量，预定义变量，获取变量的值
var=hello $(var)