#include <Python.h>

#include "axe.h"

static PyObject *axe_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    axe_hash((char *)PyBytes_AsString((PyObject*) input), (int)PyBytes_Size((PyObject*) input), output);
#else
    axe_hash((char *)PyString_AsString((PyObject*) input), (int)PyString_Size((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef AxeMethods[] = {
    { "getPoWHash", axe_getpowhash, METH_VARARGS, "Returns the proof of work hash using axe hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef AxeModule = {
    PyModuleDef_HEAD_INIT,
    "axe_hash",
    "...",
    -1,
    AxeMethods
};

PyMODINIT_FUNC PyInit_axe_hash(void) {
    return PyModule_Create(&AxeModule);
}

#else

PyMODINIT_FUNC initaxe_hash(void) {
    (void) Py_InitModule("axe_hash", AxeMethods);
}
#endif
