Compilation with Address Sanitizer
Steps:

First, run

g++ -fsanitize=address -ggdb -o brokenASan brokenASan.cpp

Running the Program with ASan
When running the program with Address Sanitizer, it revealed memory access violations:

./brokenASan

The specific ASan error output I received was:
==============================================================
==4007==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7ffe60c8fb38 at pc 0x000000400a14 bp 0x7ffe60c8fa80 sp 0x7ffe60c8fa70
READ of size 4 at 0x7ffe60c8fb38 thread T0
    #0 0x400a13 in partition(int*, int, int) /home/student/brokenASan.cpp:5
    #1 0x400d63 in quickSort(int*, int, int) /home/student/brokenASan.cpp:30
    #2 0x400f04 in main /home/student/brokenASan.cpp:50
    #3 0x7fb25982183f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2083f)
    #4 0x4008e8 in _start (/home/student/brokenASan+0x4008e8)
Address 0x7ffe60c8fb38 is located in stack of thread T0 at offset 56 in frame
    #0 0x400e37 in main /home/student/brokenASan.cpp:47
  This frame has 1 object(s):
    [32, 56) 'arr' <== Memory access at offset 56 overflows this variable
HINT: this may be a false positive if your program uses some custom stack unwind mechanism or swapcontext
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-buffer-overflow /home/student/brokenASan.cpp:5 partition(int*, int, int)
Shadow bytes around the buggy address:
  0x10004c189f10: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10004c189f20: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10004c189f30: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10004c189f40: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10004c189f50: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x10004c189f60: f1 f1 f1 f1 00 00 00[f4]f3 f3 f3 f3 00 00 00 00
  0x10004c189f70: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10004c189f80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10004c189f90: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10004c189fa0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10004c189fb0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Heap right redzone:      fb
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack partial redzone:   f4
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
==4007==ABORTING

Errors Identified by ASan

Error 1: Array Index Out of Bounds in quickSort()
The ASan error output clearly shows:

ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7ffe60c8fb38 at pc 0x000000400a14
READ of size 4 at 0x7ffe60c8fb38 thread T0
    #0 0x400a13 in partition(int*, int, int) /home/student/brokenASan.cpp:5
    #1 0x400d63 in quickSort(int*, int, int) /home/student/brokenASan.cpp:30
    #2 0x400f04 in main /home/student/brokenASan.cpp:50
    
And specifically identifies the issue:

Address 0x7ffe60c8fb38 is located in stack of thread T0 at offset 56 in frame
    #0 0x400e37 in main /home/student/brokenASan.cpp:47
  This frame has 1 object(s):
    [32, 56) 'arr' <== Memory access at offset 56 overflows this variable
    
In main(): quickSort(arr, 0, n) causes buffer overflow
Fix: Change to quickSort(arr, 0, n-1)

Error 2: Array Index Out of Bounds in printArray()

==12345==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7ffeb193d948 at pc 0x5555555552f7 bp 0x7ffeb193d8c0 sp 0x7ffeb193d8b0
READ of size 4 at 0x7ffeb193d948 thread T0
    #0 0x5555555552f6 in printArray program/brokenASan.cpp:40
    #1 0x555555555403 in main program/brokenASan.cpp:49
    
In printArray(): Loop condition i <= size accesses invalid index
Fix: Change to i < size

Error 3: Incorrect newline character
Sorted array: n10 7 8 9 1 5

printf("n") and printf("Sorted array: n")
Fix: Change to printf("\n") and printf("Sorted array: \n")