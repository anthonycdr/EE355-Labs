ASAN vs GDB
Code Example

#include <iostream>
using namespace std;

int* create_arr() {
    int* arr = new int[5];
    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
    }
    return arr;
}

void use_arr(int* arr) {
    delete[] arr; 
    cout << "Value at index 2: " << arr[2] << endl;
}

int main() {
    int* mine = create_arr();
    use_arr(mine);
    return 0;
}

Running with ASAN

g++ -fsanitize=address -g asan.cpp -o asan
./asan

ASAN Output:
==4069==ERROR: AddressSanitizer: heap-use-after-free on address 0x60300000efe8 at pc 0x000000400d42 bp 0x7ffd216214d0 sp 0x7ffd216214c0
READ of size 4 at 0x60300000efe8 thread T0
    #0 0x400d41 in useArray(int*) /home/student/asan.cpp:14
    #1 0x400d8e in main /home/student/asan.cpp:19
    #2 0x7f4cecfe583f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2083f)
    #3 0x400b88 in _start (/home/student/asan+0x400b88)
    
Running with GDB
g++ -g asan.cpp -o gdb
gdb ./gdb
In GDB:
The program ran without any obvious errors when I used 'run', which makes it hard to determine if there was really an error in the code or not. GDB also requires manual memory inspection which might be annoying to some people.

Why ASAN is Better
ASAN immediately indentifies the error and shows exactly in which line where the memory was freed and used, so no manyal memory tracking is needed. ASAN I believe also detects error everytime unlike GDB.

References
AddressSanitizer: https://github.com/google/sanitizers/wiki/AddressSanitizer
