#include<iostream>
 
using namespace std;
 
long factorial(int n);
 
int main()
{
    int n;
    cout<<"Please enter n:"<<endl;
    cin>>n;
    long val=factorial(n);
    cout<<"n factorial is: "<<val<<endl;

    return 0;
}
 
long factorial(int n)
{
    if(n <= 0)
        return 1;
    else
        return n * factorial(n-1);
}