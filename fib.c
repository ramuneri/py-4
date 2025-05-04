#include <Python.h>

// Function to calculate the nth Fibonacci number
static PyObject* fib(PyObject* self, PyObject* args) {
    int n;
    
    // Parse the input argument as an integer
    if (!PyArg_ParseTuple(args, "i", &n)) {
        return NULL;  // Return NULL if parsing fails
    }
    
    // Basic Fibonacci logic
    int a = 0, b = 1, next;
    if (n == 0) return PyLong_FromLong(a);
    if (n == 1) return PyLong_FromLong(b);
    
    for (int i = 2; i <= n; i++) {
        next = a + b;
        a = b;
        b = next;
    }
    
    return PyLong_FromLong(b);  // Return the nth Fibonacci number
}

// Define the methods in the module
static PyMethodDef FibonacciMethods[] = {
    {"fib", fib, METH_VARARGS, "Compute nth Fibonacci number"},
    {NULL, NULL, 0, NULL}  // End of methods
};

// Module definition
static struct PyModuleDef fibmodule = {
    PyModuleDef_HEAD_INIT,
    "fib",      // Module name
    "Fibonacci number calculation extension",  // Description
    -1,         // Keep the module alive
    FibonacciMethods
};

// Module initialization function
PyMODINIT_FUNC PyInit_fib(void) {
    return PyModule_Create(&fibmodule);
}
