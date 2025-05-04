#include <Python.h>

static PyObject* fib(PyObject* self, PyObject* args) {
    int n;

    // Error object 1
    if (!PyArg_ParseTuple(args, "i", &n)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be an integer.");
        return NULL;
    }

    // Error object 2
    if (n < 0) {
        PyErr_SetString(PyExc_ValueError, "Fibonacci number cannot be negative.");
        return NULL;
    }

    // Fib
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

// Define the methods for the Fibonacci module
static PyMethodDef FibonacciMethods[] = {
    {"fib", fib, METH_VARARGS, "Compute nth Fibonacci number"},
    {NULL, NULL, 0, NULL} 
};

// Module definition
static struct PyModuleDef fibmodule = {
    PyModuleDef_HEAD_INIT,
    "fib",
    "Fibonacci number calculation extension",
    -1, // Keep the module alive
    FibonacciMethods
};

// Module initialization function
PyMODINIT_FUNC PyInit_fib(void) {
    return PyModule_Create(&fibmodule);
}
