Bug Identification
Here's the step-by-step process:

Step 1: Compiling with debug symbols

g++ -g brokengdb1.cpp -o brokengdb1

Step 2: Starting GDB

gdb ./brokengdb1

Step 3: Setting a breakpoint at the factorial function

(gdb) break factorial
Breakpoint 1 at 0x400a3c: file brokengdb1.cpp, line 21.

Step 4: Running the program

(gdb) run
Starting program: /home/student/brokengdb1 
Please enter n:
5
Breakpoint 1, factorial (n=5) at brokengdb1.cpp:21
21	    if(n)


Step 5: Examining the factorial function execution

When we entered the factorial function the first time:
(gdb) print n
$1 = 5
(gdb) step
The key issue became apparent as we traced through multiple recursive calls:
(gdb) step
22	        return  factorial(n--)*n;
(gdb) print n
$2 = 5

The function was called recursively but the value of n wasn't decreasing. This indicated an infinite recursion that would eventually cause a stack overflow.

Step 6: Analyzing the problematic line

(gdb) list

17	 
18	long factorial(int n)
19	{
20	    
21	    if(n)
22	        return  factorial(n--)*n;
23	    else return 1;
24	    
25	    
26	}


From the results that gbd has given we can recognize that the bug is in line 21: return factorial(n--)*n;
The post-decrement operator (n--) doesn't decrease the value of n before it's passed to the recursive call, instead it just passes the original n value to the factorial() and decrements it after, however the decremented value will never be used as it happens after the function is called. 
