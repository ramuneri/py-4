from distutils.core import setup, Extension

# C extension module
module = Extension('fib', sources=['fib.c'])

# Setup func to build and install the module
setup(name='Fibonacci',
      version='1.0',
      description='Fibonacci number calculation extension',
      ext_modules=[module])
