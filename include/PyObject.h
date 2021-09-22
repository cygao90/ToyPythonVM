#ifndef PY_OBJECT_H
#define PY_OBJECT_H

#include <iostream>

class PyObject {
public:

    /* tmp */
    virtual void get_value() {}
    /* tmp */

    virtual PyObject* add(PyObject* x) { return NULL; }

    virtual PyObject* lt(PyObject* x) { return NULL; }
    virtual PyObject* le(PyObject* x) { return NULL; }
    virtual PyObject* eq(PyObject* x) { return NULL; }
    virtual PyObject* ne(PyObject* x) { return NULL; }
    virtual PyObject* gt(PyObject* x) { return NULL; }
    virtual PyObject* ge(PyObject* x) { return NULL; }
    virtual PyObject* in(PyObject* x) { return NULL; }
    virtual PyObject* not_in(PyObject* x) { return NULL; }
    virtual PyObject* is(PyObject* x) { return NULL; }
    virtual PyObject* is_not(PyObject* x) { return NULL; }
};

#endif