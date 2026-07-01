#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <math.h>

/*
 * compute_stats(data: list[float]) -> (mean, variance, std_dev, min, max)
 * Computes statistics in a single pass using the Welford online algorithm.
 */
static PyObject *py_compute_stats(PyObject *self, PyObject *args) {
    PyObject *list;

    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &list)) {
        return NULL;
    }

    Py_ssize_t n = PyList_Size(list);
    if (n == 0) {
        PyErr_SetString(PyExc_ValueError, "Empty list");
        return NULL;
    }

    double mean = 0.0, M2 = 0.0;
    double minimum = 1e300, maximum = -1e300;

    for (Py_ssize_t i = 0; i < n; i++) {
        PyObject *item = PyList_GET_ITEM(list, i);
        double x = PyFloat_AsDouble(item);
        if (PyErr_Occurred()) return NULL;

        /* Welford's online mean & variance */
        double delta = x - mean;
        mean += delta / (i + 1);
        double delta2 = x - mean;
        M2 += delta * delta2;

        if (x < minimum) minimum = x;
        if (x > maximum) maximum = x;
    }

    double variance = M2 / n;
    double std_dev  = sqrt(variance);

    return Py_BuildValue("ddddd", mean, variance, std_dev, minimum, maximum);
}

static PyMethodDef StatsMethods[] = {
    {"compute_stats", py_compute_stats, METH_VARARGS,
     "Compute mean, variance, std_dev, min, max of a float list."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef statsmodule = {
    PyModuleDef_HEAD_INIT, "statsmodule", NULL, -1, StatsMethods
};

PyMODINIT_FUNC PyInit_statsmodule(void) {
    return PyModule_Create(&statsmodule);
}
