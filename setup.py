from setuptools import setup, Extension  # Use setuptools instead of distutils

# C extension modules
fib_module = Extension('fib', sources=['fib.c'])
triangle_module = Extension('geometry', sources=['triangle.c'])

# Setup function to build and install the module
setup(
    name='Extensions',
    version='1.0',
    description='Fibonacci and triangle calculation extension',
    long_description="This package provides C extensions for calculating Fibonacci numbers and properties of triangles (area and perimeter).",
    ext_modules=[fib_module, triangle_module],
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
    ],
)
