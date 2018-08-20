#include "cpuid.h"
#include <python2.7/Python.h>

/* available functions for interface */
static PyObject* cpuid_vendor_check(PyObject *self, PyObject *noargs);
static PyObject* cpuid_microarch_check(PyObject *self, PyObject *noargs);

/* module specification */
static PyMethodDef module_methods[] = {
        {"cpuid_check", cpuid_vendor_check, METH_VARARGS, NULL},
        {"cpuid_microarch", cpuid_microarch_check, METH_VARARGS, NULL},
        {NULL, NULL, 0, NULL}
};


/* initialize the module */
PyMODINIT_FUNC initcpuid(void)
{
        (void) Py_InitModule("cpuid", module_methods);
}


/* cpuid_vendor_check: return C string of CPU vendor */
static PyObject*
cpuid_vendor_check(PyObject *self, PyObject *noargs)
{

    /* pass char of 13 bytes to private cpuid_vendor function */
    char vendor[13];
    cpuid_vendor(vendor);

    /* return string of vendor */
    return Py_BuildValue("s", vendor);
}


/* cpuid_microarch: return CPU microarchitecture */
static PyObject*
cpuid_microarch_check(PyObject *self, PyObject *noargs)
{
    // TODO
}




/* Example Python interface method
 * =======================================
 * This is an example of how we can harness the 
 * library in order to create other Python C API 
 * methods deployable in our Python code, reducing
 * overhead.
 */

static PyObject* my_cpuid_checker(PyObject *self, PyObject *noargs)
{
        /* check vendor: only Intel and AMD processors supported */
        char vendor[13];
        cpuid_vendor(vendor);

        if (strcmp(vendor, "GenuineIntel")) {
                PyErr_SetString(PyExc_RuntimeError, "invalid vendor string");
                return NULL;
        }

        /* TODO: check CPU microarch through unmask */

        /* returned if microarchitecture is not found */
        PyErr_SetString(PyExc_RuntimeError, "unsupported CPU microarchitecture");
        return NULL;
}

