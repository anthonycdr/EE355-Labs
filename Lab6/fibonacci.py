import sys
import subprocess

def check_fibonacci(n):
    proc = subprocess.Popen(['./fibonacci_dp.o', str(n)], 
                           stdout=subprocess.PIPE, 
                           stderr=subprocess.PIPE,
                           universal_newlines=True)
    
    out, err = proc.communicate()
    lines = out.strip().split('\n')
    
    if len(lines) == 1 and lines[0] == '1':
        print("Congratulations! You have the Fibonacci {}".format(n))
    elif len(lines) == 2 and lines[0] == '0':
        next_fib = lines[1]
        print("Sorry! {} is not a Fibonacci number but the next Fibonacci number to it is {}".format(n, next_fib))

if __name__ == "__main__":
    n = int(sys.argv[1])
    check_fibonacci(n)