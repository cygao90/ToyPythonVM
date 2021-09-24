#ifndef KLASS_H
#define KLASS_H

#include <iostream>

class PyObject;
class PyString;

class Klass {
private:
    PyString* _name;

public:
    Klass() {}

    void set_name(PyString* x) { _name = x; }
    PyString* name()           { return _name; }

    virtual PyObject* add(PyObject* x, PyObject* y)    { return NULL; }
    virtual PyObject* sub(PyObject* x, PyObject* y)    { return NULL; }
    virtual PyObject* mul(PyObject* x, PyObject* y)    { return NULL; }
    virtual PyObject* div(PyObject* x, PyObject* y)    { return NULL; }
    virtual PyObject* mod(PyObject* x, PyObject* y)    { return NULL; }

    virtual PyObject* lt(PyObject* x, PyObject* y)     { return NULL; }
    virtual PyObject* le(PyObject* x, PyObject* y)     { return NULL; }
    virtual PyObject* eq(PyObject* x, PyObject* y)     { return NULL; }
    virtual PyObject* ne(PyObject* x, PyObject* y)     { return NULL; }
    virtual PyObject* gt(PyObject* x, PyObject* y)     { return NULL; }
    virtual PyObject* ge(PyObject* x, PyObject* y)     { return NULL; }
    virtual PyObject* in(PyObject* x, PyObject* y)     { return NULL; }
    virtual PyObject* not_in(PyObject* x, PyObject* y) { return NULL; }
    virtual PyObject* is(PyObject* x, PyObject* y)     { return NULL; }
    virtual PyObject* is_not(PyObject* x, PyObject* y) { return NULL; }
};

#endif