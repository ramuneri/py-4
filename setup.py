from distutils.core import setup, Extension

# Define the C extension module
module = Extension('fib', sources=['fib.c'])

# Call the setup function to build and install the module
setup(name='Fibonacci',
      version='1.0',
      description='Fibonacci number calculation extension',
      ext_modules=[module])
