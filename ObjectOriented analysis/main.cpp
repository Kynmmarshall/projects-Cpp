
#include <iostream>

using namespace std;

void swapped(int *a,int *b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int main()
{
    int a = 2;
    int b = 4;

    a = a + b;

    b = a-b;
    a = a-b;
    cout<<"After a= "<<a <<" b= "<<b<<endl;
return 0;
}
