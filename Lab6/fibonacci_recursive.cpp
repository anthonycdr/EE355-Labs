#include <iostream>

using namespace std;

long long fib(int n){
   if (n <= 1){
      return n;
      }
   else{
      return fib(n-1) + fib(n-2);
      }
}
      
void check_fib(int inp){
   int n = 0;
   int f = 0;
   
   while(f < inp){
      f = fib(n);
      if (f == inp){
         cout << "1" << endl;
         return;
      }
      n++;
   }
   
   cout << "0" << endl;
   cout << f << endl;
}

int main(int argc, char* argv[]) {

    int inp = stoi(argv[1]);
    check_fib(inp);
    
    return 0;
}