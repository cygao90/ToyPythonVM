#ifndef PY_OBJECT_H
#define PY_OBJECT_H

#include <assert.h>
#include "Klass.h"

class PyObject {
private:
    Klass* _klass;

public:
    Klass* klass() { assert(_klass != NULL); return _klass; }
    void set_klass(Klass* x) { _klass = x; }

    PyObject* add(PyObject* x); 
    PyObject* sub(PyObject* x); 
    PyObject* mul(PyObject* x); 
    PyObject* div(PyObject* x); 
    PyObject* mod(PyObject* x); 

    PyObject* lt(PyObject* x); 
    PyObject* le(PyObject* x); 
    PyObject* eq(PyObject* x); 
    PyObject* ne(PyObject* x); 
    PyObject* gt(PyObject* x); 
    PyObject* ge(PyObject* x); 
    PyObject* in(PyObject* x); 
    PyObject* not_in(PyObject* x); 
    PyObject* is(PyObject* x); 
    PyObject* is_not(PyObject* x); 

    PyObject* len(PyObject* args);
    PyObject* print(PyObject* args);
};

#endif