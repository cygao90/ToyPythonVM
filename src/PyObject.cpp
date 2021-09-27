#include "PyObject.h"
#include "PyList.h"

PyObject* PyObject::add(PyObject* x) {
    return klass()->add(this, x);
}

PyObject* PyObject::sub(PyObject* x) {
    return klass()->sub(this, x);
}

PyObject* PyObject::mul(PyObject* x) {
    return klass()->mul(this, x);
}

PyObject* PyObject::div(PyObject* x) {
    return klass()->div(this, x);
}

PyObject* PyObject::mod(PyObject* x) {
    return klass()->mod(this, x);
}

PyObject* PyObject::lt(PyObject* x) {
    return klass()->lt(this, x);
}

PyObject* PyObject::le(PyObject* x) {
    return klass()->le(this, x);
}

PyObject* PyObject::eq(PyObject* x) {
    return klass()->eq(this, x);
}

PyObject* PyObject::ne(PyObject* x) {
    return klass()->ne(this, x);
}

PyObject* PyObject::gt(PyObject* x) {
    return klass()->gt(this, x);
}

PyObject* PyObject::ge(PyObject* x) {
    return klass()->ge(this, x);
}

PyObject* PyObject::in(PyObject* x) {
    return klass()->in(this, x);
}

PyObject* PyObject::not_in(PyObject* x) {
    return klass()->not_in(this, x);
}

PyObject* PyObject::is(PyObject* x) {
    return klass()->is(this, x);
}

PyObject* PyObject::is_not(PyObject* x) {
    return klass()->is_not(this, x);
}

PyObject* PyObject::len(PyObject* args) {
    return klass()->len(this);
}

PyObject* PyObject::print(PyObject* args) {
    return klass()->print(this);
}