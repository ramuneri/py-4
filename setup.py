from setuptools import setup, Extension

# Fibonacci extension module
fib_module = Extension(
    name='fib',
    sources=['fib.c']
)

# Triangle (geometry) extension module
geometry_module = Extension(
    name='geometry',
    sources=['triangle.c']
)

setup(
    name='Extensions',
    version='1.0',
    description='C extensions for Fibonacci and Triangle',
    ext_modules=[fib_module, geometry_module],
)
