#include <Python.h>
#include <math.h>

// Define the Triangle object structure
typedef struct {
    PyObject_HEAD
    double a, b, c;  // sides of the triangle
} Triangle;

// Create a new Triangle object
static PyObject* Triangle_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    Triangle *self;

    // Allocate memory for the new object
    self = (Triangle *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->a = 0;
        self->b = 0;
        self->c = 0;
    }
    return (PyObject *)self;
}

// Initialize the Triangle object (set side lengths)
static int Triangle_init(Triangle *self, PyObject *args, PyObject *kwds) {
    if (!PyArg_ParseTuple(args, "ddd", &self->a, &self->b, &self->c)) {
        return -1;  // Return error if parsing fails
    }
    return 0;
}

// Calculate the area of the triangle using Heron's formula
static PyObject* Triangle_area(Triangle* self) {
    double s = (self->a + self->b + self->c) / 2;
    double area = sqrt(s * (s - self->a) * (s - self->b) * (s - self->c));
    return PyFloat_FromDouble(area);  // Return area as a Python float
}

// Calculate the perimeter of the triangle
static PyObject* Triangle_perimeter(Triangle* self) {
    double perimeter = self->a + self->b + self->c;
    return PyFloat_FromDouble(perimeter);  // Return perimeter as a Python float
}

// Define the methods of the Triangle class
static PyMethodDef Triangle_methods[] = {
    {"area", (PyCFunction)Triangle_area, METH_NOARGS, "Calculate the area of the triangle"},
    {"perimeter", (PyCFunction)Triangle_perimeter, METH_NOARGS, "Calculate the perimeter of the triangle"},
    {NULL, NULL, 0, NULL}  // End of methods
};

// Define the Triangle type
static PyTypeObject TriangleType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "geometry.Triangle",       // Name of the class
    sizeof(Triangle),          // Size of the object
    0,                         // Item size
    (destructor)PyObject_Del,  // Deallocation function
    0,                         // Methods for the type
    0,                         // Slots for the type
    0,                         // Inheritance info
    0,                         // Documentation string
    0,                         // Miscellaneous info
    0,                         // Destroy methods
    0,                         // Traverse methods
    0,                         // Dealloc functions
    0,                         // Name for the type
    0,                         // Docstring for the type
    Triangle_methods,          // Methods for the type
    NULL                       // Additional stuff
};

// Module definition
static struct PyModuleDef geometrymodule = {
    PyModuleDef_HEAD_INIT,
    "geometry",  // Module name
    "Triangle module with area and perimeter", // Description
    -1, // Keep the module alive
    NULL
};

// Module initialization function
PyMODINIT_FUNC PyInit_geometry(void) {
    PyObject* m;

    if (PyType_Ready(&TriangleType) < 0) {
        return NULL;  // Return NULL if the type cannot be initialized
    }

    // Create the module
    m = PyModule_Create(&geometrymodule);
    if (m == NULL) {
        return NULL;  // Return NULL if the module cannot be created
    }

    // Add the Triangle class to the module
    Py_INCREF(&TriangleType);  // Increase reference count
    PyModule_AddObject(m, "Triangle", (PyObject *)&TriangleType);  // Add the Triangle class to the module

    return m;
}
