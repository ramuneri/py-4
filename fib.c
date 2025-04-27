#include <Python.h>

static PyObject* fib(PyObject* self, PyObject* args) {
    int n;
    
    // Parse the input argument
    if (!PyArg_ParseTuple(args, "i", &n)) {
        return NULL;
    }
    
    // Compute the Fibonacci number
    int a = 0, b = 1, next;
    if (n == 0) return PyLong_FromLong(a);
    if (n == 1) return PyLong_FromLong(b);
    
    for (int i = 2; i <= n; i++) {
        next = a + b;
        a = b;
        b = next;
    }
    
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
    "fib",   // Module name
    "Fibonacci number calculation extension", // Docstring
    -1, // Size of per-interpreter state
    FibonacciMethods
};

// Module initialization function
PyMODINIT_FUNC PyInit_fib(void) {
    return PyModule_Create(&fibmodule);
}
