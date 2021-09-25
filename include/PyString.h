#ifndef PY_STRING_H
#define PY_STRING_H

#include <string>
#include "PyObject.h"

using std::string;

class StringKlass : public Klass {
private:
    StringKlass();
    static StringKlass* _instance;

public:
    static StringKlass* get_instance();
    void initialize();

    virtual PyObject* add(PyObject* x, PyObject* y);    

    virtual PyObject* lt(PyObject* x, PyObject* y);     
    virtual PyObject* le(PyObject* x, PyObject* y);     
    virtual PyObject* eq(PyObject* x, PyObject* y);     
    virtual PyObject* ne(PyObject* x, PyObject* y);     
    virtual PyObject* gt(PyObject* x, PyObject* y);     
    virtual PyObject* ge(PyObject* x, PyObject* y);     
};

class PyString : public PyObject {
private:
    string _value;

public:

    void print() { std::cout << _value << "\n"; }

    PyString(const string s);

    string& value() { return _value; } 
    int length() { return _value.size(); }
};

#endif