#include <Python.h>

static PyObject* fiba(PyObject* self, PyObject* args) {
    int n;
    
    if (!PyArg_ParseTuple(args, "i", &n)) {
        return NULL;
    }
    
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

static PyMethodDef FibonacciMethods[] = {
    {"fiba", fiba, METH_VARARGS, "Compute nth Fibonacci number"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef fibmodule = {
    PyModuleDef_HEAD_INIT,
    "fiba",   // Module name
    "Fibonacci number calculation extension", // Docstring
    -1, // Size of per-interpreter state
    FibonacciMethods
};

// Module initialization function
PyMODINIT_FUNC PyInit_fib(void) {
    return PyModule_Create(&fibmodule);
}
