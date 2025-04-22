While the Mandelbrot set is defined recursively as Z_(n) = Z²_(n-1) + c, the implementation here uses iteration rather than explicit recursion for efficiency:

def mandelbrot_iteration(c, max_iter):
    z = 0
    for n in range(max_iter):
        if abs(z) > 2:
            return n
        z = z*z + c
    return max_iter
    
This function implements the recursive Mandelbrot formula Z_(n+1) = Z_(n)² + c iteratively, where c is a complex number.

The 3D visualization displays:

X-axis: Real component of c
Y-axis: Imaginary component of c
Z-axis: Number of iterations before divergence 

I didn't add a picture to this as I realised I will need a MatLab extension that I dont think the VB has.

References
"Mandelbrot Set with Python" - https://levelup.gitconnected.com/mandelbrot-set-with-python-983e9fc47f56
"Matplotlib 3D plotting" - https://matplotlib.org/stable/tutorials/toolkits/mplot3d.html
