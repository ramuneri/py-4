#include <Python.h>
#include <math.h>

typedef struct {
    PyObject_HEAD
    double a, b, c;
} Triangle;


Triangle_dealloc(Triangle* self)
{
    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
Triangle_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Triangle *self = (Triangle*)type->tp_alloc(type, 0);
    if (self) {
        self->a = self->b = self->c = 0.0;
    }
    return (PyObject*)self;
}


static int
Triangle_init(Triangle *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"a","b","c", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "ddd", kwlist,
                                     &self->a, &self->b, &self->c))
        return -1;
    return 0;
}


static PyObject*
Triangle_area(Triangle* self, PyObject *Py_UNUSED(ignored))
{
    double s = (self->a + self->b + self->c) / 2.0;
    double area = sqrt(s * (s - self->a) * (s - self->b) * (s - self->c));
    return PyFloat_FromDouble(area);
}


static PyObject*
Triangle_perimeter(Triangle* self, PyObject *Py_UNUSED(ignored))
{
    double p = self->a + self->b + self->c;
    return PyFloat_FromDouble(p);
}


Triangle_square(PyObject *self, PyObject *args)
{
    double v;
    if (!PyArg_ParseTuple(args, "d", &v))
        return NULL;

    PyObject *mod = PyImport_ImportModule("embed");
    if (!mod) {
        PyErr_Print();
        return NULL;
    }
    
    PyObject *func = PyObject_GetAttrString(mod, "square");
    Py_DECREF(mod);
    if (!func || !PyCallable_Check(func)) {
        Py_XDECREF(func);
        PyErr_SetString(PyExc_AttributeError, "module 'embed' has no attribute 'square'");
        return NULL;
    }

    PyObject *arg = Py_BuildValue("(d)", v);
    PyObject *res = PyObject_CallObject(func, arg);
    Py_DECREF(arg);
    Py_DECREF(func);
    if (!res) {
        PyErr_Print();
        return NULL;
    }

    double d = PyFloat_AsDouble(res);
    Py_DECREF(res);
    return PyFloat_FromDouble(d);
}

static PyMethodDef Triangle_methods[] = {
    {"area",      (PyCFunction)Triangle_area,      METH_NOARGS,  "Return triangle area"},
    {"perimeter", (PyCFunction)Triangle_perimeter, METH_NOARGS,  "Return triangle perimeter"},
    {"square",    (PyCFunction)Triangle_square,    METH_VARARGS, "Return square of a number via embedded Python function"},
    {NULL}
};

static PyTypeObject TriangleType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name      = "geometry.Triangle",
    .tp_basicsize = sizeof(Triangle),
    .tp_itemsize  = 0,
    .tp_dealloc   = (destructor)Triangle_dealloc,
    .tp_flags     = Py_TPFLAGS_DEFAULT,
    .tp_doc       = "Triangle(a, b, c)\n\nCreate a triangle and compute its area and perimeter.\nMethods:\n  area()      -- returns area\n  perimeter() -- returns perimeter\n  square(x)   -- returns x*x via Python embed",
    .tp_methods   = Triangle_methods,
    .tp_init      = (initproc)Triangle_init,
    .tp_new       = Triangle_new,
};

static struct PyModuleDef geometrymodule = {
    PyModuleDef_HEAD_INIT,
    .m_name    = "geometry",
    .m_doc     = "Module that defines a Triangle type and embeds a Python function.",
    .m_size    = -1,
};

PyMODINIT_FUNC
PyInit_geometry(void)
{
    PyObject *m;
    if (PyType_Ready(&TriangleType) < 0)
        return NULL;

    m = PyModule_Create(&geometrymodule);
    if (!m)
        return NULL;

    Py_INCREF(&TriangleType);
    if (PyModule_AddObject(m, "Triangle", (PyObject *)&TriangleType) < 0) {
        Py_DECREF(&TriangleType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
