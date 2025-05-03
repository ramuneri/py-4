#include <Python.h>

static PyObject* fib(PyObject* self, PyObject* args) {
    int n;
    
    if (!PyArg_ParseTuple(args, "i", &n)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be an integer."); // error object
        return NULL;
    }
    
    if (n < 0) {
        PyErr_SetString(PyExc_ValueError, "Fibonacci number cannot be negative."); // error objects
        return NULL;
    }
    
    // Fibonacci calculation
    int a = 0, b = 1, next;
    if (n == 0) return PyLong_FromLong(a);
    if (n == 1) return PyLong_FromLong(b);
    
    // Iterative approach to calculate Fibonacci number
    for (int i = 2; i <= n; i++) {
        next = a + b;
        a = b;
        b = next;
    }
    
    // Return the n-th Fibonacci number as a Python long object
    return PyLong_FromLong(b);
}

// Method definition
static PyMethodDef FibonacciMethods[] = {
    {"fib", fib, METH_VARARGS, "Compute nth Fibonacci number"},
    {NULL, NULL, 0, NULL}
};

// Module definition
static struct PyModuleDef fibmodule = {
    PyModuleDef_HEAD_INIT,
    "fib",  // Module name
    "Fibonacci number calculation extension",  // Module description
    -1,  // Global state for the module
    FibonacciMethods  // Array of method definitions
};

// Module initialization function
PyMODINIT_FUNC PyInit_fib(void) {
    return PyModule_Create(&fibmodule);
}
