#include <iostream>
#include <memory>
#include <string.h>
#include <vector>
#include <algorithm>
#include <mutex>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <pthread.h>
#include <unordered_map>

using namespace std;

const int const1 = 1;
const int const2 = 2;
int global1,global2;
int global3=6;
class base{
public:
int  a;
int b;
    base(){}
     void printfunc(){
        cout<<"print base"<<endl;
    }
    virtual  ~base(){
        cout<<"delete base"<<endl;
    }
};

class a: public base{
public:
    a(){}
    void printfunc(){
        cout<<"print a"<<endl;
    }
    ~a(){
        cout<<"delete a"<<endl;
    }
};
//虚函数表八个字节
class testMemory:public base
{
public:
    virtual void printfunc(){
        cout<<"print a"<<endl;
    }
    virtual ~testMemory(){}
    virtual void print1(){}
};

union U
{
    char str[2];
    short num;
};

condition_variable cond;
atomic_int flag(10);
mutex mtx;
void func1(int num){
    unique_lock<mutex> lk(mtx);
    while(flag!=num)    cond.wait(lk);
    for(int i=0;i<num;++i){
        cout<<i<<' ';
    }
    cout<<endl;
    flag=(num==10)?100:10;
    cond.notify_all();
}

void func2()
{

}

int main()
{
    //shared_ptr<base> p = make_shared<a>();
    //p->printfunc();
    //base *p = new a;
    //delete p;
/*
   unsigned short num1 = 0x12FF;
    char * address = (char *)&num1;
    //cout<<"low is "<<(*address & 0xFF)<<endl;//FF低位，故是小端模式
    //printf("low bytes is %x , high bytes is %x \n",*address & 0xFF,  *(address + 1) & 0xFF );
    int arr[][3] = {1,2,3,4,5};
    //cout<<sizeof(arr)<<endl
     //   <<arr[1][2]<<endl;
    int arr2[5]={1,2,3,4,5};
    int *p = arr2;
    //cout<<sizeof(p)<<endl;
    U u;
    u.str[0]=0;
    u.str[1]=1;
    int a,b;
    base classb;
    cout<<(size_t)&u.str[0]<<" "<<(size_t)&u.str[1]<<" "<<(size_t)&a<<" "<<(size_t)&b<<" "<<(size_t)&classb<<" "<<(size_t)&arr2[0]<<" "
        <<(size_t)&arr2[1]<<endl;

    int a,b;
    cout<<(size_t)&const1<<" "<<(size_t)&const2<<endl;
    cout<<(size_t)&global3<<endl;
    cout<<(size_t)&global1<<" "<<(size_t)&global2<<endl;
    cout<<(size_t)&a<<" "<<(size_t)&b<<endl;
    
   string str;
   cin>>str;
   for(int i=0;i<str.length();++i){
       char c = str[i];
       if(c>='a' && c<='z')     str[i]-=32;
       if(c>='A' && c<='Z')     str[i]+=32;
   }
   
   cout<<str<<endl;
 
  //unsigned short a =-2;
   //cout<<sizeof(long    long)<<endl;
   int carray[100]={1,2,3,4};
   string str="aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa                                                                                              aaaaaaaa";
   testMemory carr;
   int a = sizeof(str);
    //cout<<a<<endl;
    int *m =(int *)malloc(100*sizeof(char)); 
    //m=carray;

    cout<<&m[0]<<' '<<&m[1]<<endl;
    m[1]=12;
    m[0]=999999999;
    cout<<&m[0]<<' '<<&m[1]<<endl;
    cout<<dec<<&m[1]-&m[0]<<endl;
    cout<<sizeof(char)<<endl;
    cout<<m[0]<<' '<<m[1]<<endl;

    //printf("%s  %s\n",&m[0],&m[1]);

    testMemory tm;
    cout<<sizeof(tm)<<endl;
    testMemory tm1(tm);
    U u;
    u.str[0]=0;
    u.str[1]=1;
    //cout<<&u.str[0]<<' '<<&u.str[1]<<endl;
    //cout<<u.num<<endl;
    double testref=1;
    testMemory &testref1=tm;
    cout<<sizeof(testref1)<<endl;
    //system("pause");
    
    vector<int> nums= {19,18,14,16,13,15,11,12,10,20};
    int min_val=INT32_MAX;
    int max_val=INT32_MIN;
    for(const int num:nums){
        min_val=min(min_val,num);
        max_val=max(max_val,num);
    }//n
    int num_bucket=(max_val-min_val)/nums.size()+1;
    vector<vector<int>> buckets(num_bucket);
    for(const int num:nums){
        int index=(num-min_val)/nums.size();
        buckets[index].emplace_back(num);
    }
    vector<int> res;
    for(auto bucket:buckets){
        if(bucket.size()==0)    continue;
        sort(bucket.begin(),bucket.end());//m*n/m*logn/m
        res.insert(res.end(),bucket.begin(),bucket.end());
    }

    for(const auto r:res){
        cout<<r<<' ';
    }
    cout<<endl;
*/
    /*
    std::thread child1(func1,10);
    std::thread child2(func1,10);
    func1(100);
    child1.join();
    child2.join();
    */
   char *pc="abcde";
   char arrc[5]="abcd";
   cout<<sizeof(pc)<<' '<<sizeof(arrc)<<' '<<strlen(pc)<<' '<<strlen(arrc)<<endl;
   cout<<pc<<endl;
   base *p2 = new a();
   //shared_ptr<base> p3(new base);
   cout<<sizeof(p2)<<endl;
    //std::thread thread1([](){cout<<"useing thread"<<endl;});
    //thread1.join();
    vector<vector<char>> map={{'0','E','E','0'},{'E','0','W','E'},{'0','E','0','0'}};
    int res=0;
    int rows=map.size();
    int cols=map[0].size();
    for(int i=0;i<rows;++i){
        for(int j=0;j<cols;++j){
            if(map[i][j]!='0')  continue;
            int count=0;
            int row,col;
            row=i,col=j;
            while(col-->0 ){
                 if(map[row][col]=='W'){
                     break;
                 }else if(map[row][col]=='0'){
                     continue;
                 }else if(map[row][col]=='E'){
                     ++count;
                 }
            }
            row=i,col=j;
            while(col++<cols-1 ){
                 if(map[row][col]=='W'){
                     break;
                 }else if(map[row][col]=='0'){
                     continue;
                 }else if(map[row][col]=='E'){
                     ++count;
                 }
            }
            row=i,col=j;
            while(row-->1 ){
                 if(map[row][col]=='W'){
                     break;
                 }else if(map[row][col]=='0'){
                     continue;
                 }else if(map[row][col]=='E'){
                     ++count;
                 }
            }
            row=i,col=j;
            while(row++<rows-1 ){
                 if(map[row][col]=='W'){
                     break;
                 }else if(map[row][col]=='0'){
                     continue;
                 }else if(map[row][col]=='E'){
                     ++count;
                 }
            }
            res=max(res,count);
        }
    }
    int ans=0;
    vector<vector<int>> dp(rows,vector<int>(cols));
    vector<vector<int>> dp1(rows,vector<int>(cols));
    vector<vector<int>> dp2(rows,vector<int>(cols));
    vector<vector<int>> dp3(rows,vector<int>(cols));
    vector<vector<int>> dp4(rows,vector<int>(cols));
    /*
    dp1[0][0]==(map[0][0]=='E')?1:0;
    dp2[0][0]=dp1[0][0];
    dp3[rows-1][cols-1]=(map[rows-1][cols-1]=='E')?1:0;
    dp4[rows-1][cols-1]=dp3[rows-1][cols-1];
    */
    for(int i=0;i<rows;++i){
        for(int j=0;j<cols;++j){
            if(i>0){
                char c1=map[i-1][j];
                if(c1=='W'){
                    dp1[i][j]+=0;
                }else if(c1=='E'){
                    dp1[i][j]+=(dp1[i-1][j]+1);
                }else{
                    dp1[i][j]+=dp1[i-1][j];
                }
            } 
        }
    }
     for(int i=0;i<rows;++i){
        for(int j=0;j<cols;++j){
             if(j>0){
                char c1=map[i][j-1];
                if(c1=='W'){
                    dp2[i][j]+=0;
                }else if(c1=='E'){
                    dp2[i][j]+=(dp2[i][j-1]+1);
                }else{
                    dp2[i][j]+=dp2[i][j-1];
                }
            }
        }
    }
    for(int i=rows-1;i>=0;--i){
        for(int j=cols-1;j>=0;--j){
            if(i<rows-1){
                char c1=map[i+1][j];
                if(c1=='W'){
                    dp3[i][j]+=0;
                }else if(c1=='E'){
                    dp3[i][j]+=(dp3[i+1][j]+1);
                }else{
                    dp3[i][j]+=dp3[i+1][j];
                }
            } 
        }
    }
     for(int i=rows-1;i>=0;--i){
        for(int j=cols-1;j>=0;--j){
             if(j<cols-1){
                char c1=map[i][j+1];
                if(c1=='W'){
                    dp4[i][j]+=0;
                }else if(c1=='E'){
                    dp4[i][j]+=(dp4[i][j+1]+1);
                }else{
                    dp4[i][j]+=dp4[i][j+1];
                }
            }
        }
    }
    for(int i=0;i<rows;++i){
        for(int j=0;j<cols;++j){
            if(map[i][j]=='0')  ans=max(ans,dp1[i][j]+dp2[i][j]+dp3[i][j]+dp4[i][j]);
        }
    }
    cout<<"res is "<<res<<endl;
    cout<<"ans is "<<ans<<endl;
    unordered_map<int,int> hashmap;
    for(int i=0;i<7;++i){
        hashmap[i]=i;
    }
    
    std::cout<<hashmap.bucket_count()<<std::endl;
    return 0;
}