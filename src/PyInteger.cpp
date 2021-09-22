#include "PyInteger.h"
#include "Universe.h"

PyObject* PyInteger::lt(PyObject* x) {
    if (_value < ((PyInteger*)x)->_value) {
        return Universe::Py_True;
    } else {
        return Universe::Py_False;
    }
}

PyObject* PyInteger::le(PyObject* x) {
    if (_value <= ((PyInteger*)x)->_value) {
        return Universe::Py_True;
    } else {
        return Universe::Py_False;
    }
}

PyObject* PyInteger::eq(PyObject* x) {
    if (_value == ((PyInteger*)x)->_value) {
        return Universe::Py_True;
    } else {
        return Universe::Py_False;
    }
}

PyObject* PyInteger::ne(PyObject* x) {
    if (_value != ((PyInteger*)x)->_value) {
        return Universe::Py_True;
    } else {
        return Universe::Py_False;
    }
}

PyObject* PyInteger::gt(PyObject* x) {
    if (_value > ((PyInteger*)x)->_value) {
        return Universe::Py_True;
    } else {
        return Universe::Py_False;
    }
}

PyObject* PyInteger::ge(PyObject* x) {
    if (_value >= ((PyInteger*)x)->_value) {
        return Universe::Py_True;
    } else {
        return Universe::Py_False;
    }
}

PyObject* PyInteger::add(PyObject* x) {
    return new PyInteger(_value + ((PyInteger*)x)->_value);
}