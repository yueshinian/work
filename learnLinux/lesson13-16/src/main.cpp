#include <iostream>

using namespace std;

int test(int n)
{
    int result = 0;
    for(int i=0;i<n;++i){
        result+=i;
    }
    return result;
}

int main()
{
    for(int i=0;i<10;++i){
        int result = test(i);
        cout<<result<<endl;
    }
    return 0;
}