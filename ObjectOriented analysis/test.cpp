
#include <iostream>

using namespace std;

void swap(int a,int b){
    int tmp;
    tmp = a;
    a = b;
    b = tmp;

    return a , b;
}

int main()
{
    int a = 2;
    int b = 4;

    swap(a,b);

    cout<<"a= "<<a <<"b= "<<b<<endl;
return 0;
}
