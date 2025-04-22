#include <iostream>
#include <vector>
#include <cstdlib> 

using namespace std;

void check_fib(int inp) {
    vector<long long> fib;
   fib.push_back(0);
   fib.push_back(1);
 

    while (fib.back() < inp) {
        fib.push_back(fib[fib.size() - 1] + fib[fib.size() - 2]);
        
        if (fib.back() == inp) {
            cout << "1" << endl;
            return;
        }
    }

    cout << "0" << endl;
    cout << fib.back() << endl;
}

int main(int argc, char* argv[]) {

    int inp = atoi(argv[1]);
    check_fib(inp);

    return 0;
}
