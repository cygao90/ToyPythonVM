#include "PyInteger.h"

PyObject* PyInteger::lt(PyObject* x) {
    if (_value < ((PyInteger*)x)->_value) {
        return new PyInteger(1);
    } else {
        return new PyInteger(0);
    }
}

PyObject* PyInteger::le(PyObject* x) {
    if (_value <= ((PyInteger*)x)->_value) {
        return new PyInteger(1);
    } else {
        return new PyInteger(0);
    }
}

PyObject* PyInteger::eq(PyObject* x) {
    if (_value == ((PyInteger*)x)->_value) {
        return new PyInteger(1);
    } else {
        return new PyInteger(0);
    }
}

PyObject* PyInteger::ne(PyObject* x) {
    if (_value != ((PyInteger*)x)->_value) {
        return new PyInteger(1);
    } else {
        return new PyInteger(0);
    }
}

PyObject* PyInteger::gt(PyObject* x) {
    if (_value > ((PyInteger*)x)->_value) {
        return new PyInteger(1);
    } else {
        return new PyInteger(0);
    }
}

PyObject* PyInteger::ge(PyObject* x) {
    if (_value >= ((PyInteger*)x)->_value) {
        return new PyInteger(1);
    } else {
        return new PyInteger(0);
    }
}