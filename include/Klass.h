#ifndef KLASS_H
#define KLASS_H

#include <iostream>
#include <string>
#include "Map.h"

using std::string;

class PyObject;
class PyString;

class Klass {
private:
    PyString* _name;
    Map<string, PyObject*>* _klass_dict;

public:
    Klass() {}

    void set_name(PyString* x) { _name = x; }
    PyString* name()           { return _name; }

    void set_klass_dict(Map<string, PyObject*>* dict) { _klass_dict = dict; }
    Map<string, PyObject*>* klass_dict() { return _klass_dict; }

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

    virtual PyObject* len(PyObject* args)              { return NULL; }
    virtual PyObject* print(PyObject* args)            { return NULL; }
    virtual PyObject* subscr(PyObject* x, PyObject* y) { return NULL; }
};

#endif