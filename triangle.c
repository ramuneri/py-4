#include <Python.h>
#include <math.h>

typedef struct {
    PyObject_HEAD
    double a, b, c;
} Triangle;


static void
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


static PyMethodDef Triangle_methods[] = {
    {"area",      (PyCFunction)Triangle_area,      METH_NOARGS,  "Return triangle area"},
    {"perimeter", (PyCFunction)Triangle_perimeter, METH_NOARGS,  "Return triangle perimeter"},
    {NULL}
};


static PyTypeObject TriangleType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name      = "geometry.Triangle",
    .tp_basicsize = sizeof(Triangle),
    .tp_itemsize  = 0,
    .tp_dealloc   = (destructor)Triangle_dealloc,
    .tp_flags     = Py_TPFLAGS_DEFAULT,
    .tp_doc       = "Triangle(a, b, c)\n\n"
                    "Methods:\n"
                    "  area()      -- returns area\n"
                    "  perimeter() -- returns perimeter\n",
    .tp_methods   = Triangle_methods,
    .tp_init      = (initproc)Triangle_init,
    .tp_new       = Triangle_new,
};


static PyModuleDef geometrymodule = {
    PyModuleDef_HEAD_INIT,
    .m_name    = "geometry",
    .m_doc     = "Module that defines a Triangle type.",
    .m_size    = -1,
};


PyMODINIT_FUNC
PyInit_geometry(void)
{
    PyObject *m;
    if (PyType_Ready(&TriangleType) < 0)
        return NULL;

    m = PyModule_Create(&geometrymodule);
    if (!m) return NULL;

    Py_INCREF(&TriangleType);
    if (PyModule_AddObject(m, "Triangle", (PyObject *)&TriangleType) < 0) {
        Py_DECREF(&TriangleType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
