#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstring>
#include "test01.h"
using namespace std;

template <typename T>
T add_fun(const T &temp1, const T &temp2){
	return temp1+temp2;
}

static int static_global=1;//生命周期未改变，作用区域改变，只在当前文件
extern void fun2();
extern int testextern;
extern "C"{
	int extern_c=1;//基于C编译，例如函数重载
}
struct memorytest
{
	char c1; //4
	int i1;//4
	char c2[10];//12
};
class Base
{
public:
	virtual int chun_virtual()=0;
	void overwrite(){
		cout<<"this is base overwrite"<<endl;
	}
};
class B;
class A:public Base
{
private:
    char *p;
	unsigned int p_size;
	static int static_class_var;//可以不声明对象使用static成员，静态成员函数只能访问static,不占用空间
public:
	void overwrite(){
		cout<<"this is A overwrite"<<endl;
	}
	int chun_virtual(){
		cout<<"chun_virtual"<<endl;
	}
	static void static_class_func(){
		//static_class_var=1;
		cout<<static_class_var<<endl;
	}
	shared_ptr<B> pb_;
	//A() =default;//默认构造函数
	A(const A &)=delete;//禁止使用拷贝构造函数
	A(unsigned int n=1){
		p= new char[n];
		p_size = n;
	}
	~A(){
		if(p!=nullptr)	delete[] p;
		p=nullptr;
		cout<<"delete A"<<endl;
	}
	virtual void print(){
		cout<<"this is base A"<<endl;
	}
};
int A::static_class_var=998;
class C: public A{
private:
public:
	void print(){
		cout<<"this is C child of A"<<endl;
	}
};

class B
{
private:
	char* p;
public:
	weak_ptr<A> pa_;//解决sharedptr的内存泄露，两个互相引用
	B(){}
	~B(){
		cout<<"delete B"<<endl;
	}
};

void fun1()
{
	A *a1 = new A(100);
	A *a2 = a1;
}
void fun3(){
	int static_function =1;//statix作用于函数，改变生命周期，未改变作用区域
}
int main(){
    //1内存对齐
	memorytest test1;
	cout<<sizeof(test1)<<endl;//20
	//2内存泄露
	fun1();
	//3智能指针
	shared_ptr<A> pa  = make_shared<A>();
	shared_ptr<B> pb(new B());
	unique_ptr<A> pa1(new A());
	unique_ptr<A> pa2;
	//pa2=pa1;拥有权力
	pa2 = move(pa1);
	cout<<pa.use_count()<<endl;
	cout<<pb.use_count()<<endl;
	pa->pb_=pb;
	pb->pa_=pa;
	cout<<pa.use_count()<<endl;
	cout<<pb.use_count()<<endl;
	//4C++ 11
	int a=12;
	//自动推导
	auto b=a;
	decltype(a) c;
	vector<int> vec1 = {2,8,3,1,9};
	cout<<"vector capicity is "<<vec1.capacity()<<endl;
	vec1.emplace_back(45);
	cout<<"vector capicity is "<<vec1.capacity()<<endl;
	//lambda表达式,变量捕获列表如值捕获、引用捕获、隐士捕获=，&，参数列表，函数体
	sort(vec1.begin(),vec1.end(),[](int a, int b){
		return a>b;
	});
	//for range循环
	for(const auto &v:vec1){
		cout<<v<<endl;
	}
	//5封装，继承，多态
	//6 virtual function
	shared_ptr<A>  pa3 = make_shared<C>();
	pa3->print();
	cout<<"pa3 C use count "<<pa3.use_count() <<endl;
	//7作用区域
	//extern
	//fun2();
	//static
	A::static_class_func();
	//8 const 和define，类型检查，节省内存空间，红替换占用内存。difine与编译是展开
	//9 inline内敛函数，（1）消除函数调用开销，不需要保护现场（2）函数可以重复定义，编译是展开
	//10 new、delete和melloc、free，new是关键字，编译器自己分配内存，调用构造 函数初始化，返回对象类型指针，分配失败，bad_alloc异常，自由存储区
	//                                                                    malloc是库函数，指定内存大小，返回oid*指针，需要强制转换，分配失败，NULL指针，堆
	//11 C++和C的struct，C++的struct支持成员函数定义，有权限，不需要struct关键词，兼容C
	//union只有一个有效的成员，内存分配按照最大成员
	//struct默认public，class默认private
	//12 memcpy
	char p1[]="memcpy";
	char p2[10];
	memcpy(p2,p1,10);
	cout<<p2<<endl;
	//13 move
	//14指针大小，8字节
	int *pointer_size;
	cout<<sizeof(pointer_size)<<endl;
	//野指针，指向不确定（未初始化，）；悬空指针，内存释放，仍然指向这块内存，p=nullptr，解决
	//引用和指针，引用绑定的对象不可变，必须绑定对象，别名，不占内存，
	//const char *p，p指向的对象无法改变，常量指针
	const int c_var1=5;
	const int c_var2=8;
	const int *p=&c_var1;
	//*p=6;//error
	p=&c_var2;
	//char * const p，指针无法指向别处，指针常量
	int var_3=3;
	int var_4=4;
	int * const q = &var_3;
	//q=&var_4;//error
	//15模板template，泛型编程
	cout<<add_fun(var_3,var_4)<<endl;
	//16纯虚函数,在基类只有声明，没有定意义，在派生类，必须实现，
	//析沟函数定义为续汉书，否则只会调用基类析构函数
	shared_ptr<Base> base = make_shared<A>();
	base->chun_virtual();
	base->overwrite();
	shared_ptr<A> base_a =make_shared<A>();
	shared_ptr<A> base_a1 = make_shared<A>();
	cout<<&base_a<<"    "<<base_a1<<endl;
	base_a->overwrite();
	//虚函数通过虚函数表（存放徐函数的地址）实现。对象首地址存放指向虚函数表的指针（和对象绑定），通过续汉书表（和类绑定，即共用）查找对应的徐函数。
	//多继承，多覆盖
	std::cout<<endl<<"main fuction finished!"<<std::endl;
	return 0;
}
