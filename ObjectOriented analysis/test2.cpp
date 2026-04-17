
#include <iostream>

using namespace std;

int main()
{
    int a;
    int *m = &a;
    int **l = &m;
    int ***k = &l;
    int ****j = &k;
    int *****i = &j;
    int ******p = &i;




    cout<<"p = "<<*i<<" "<< j << " " << &k<<endl;
    cout<<"a= "<<a<<endl;
    return 0;
}
