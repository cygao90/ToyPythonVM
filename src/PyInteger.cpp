#include "PyInteger.h"
#include "Universe.h"

IntegerKlass* IntegerKlass::_instance = NULL;

IntegerKlass::IntegerKlass() {

}

IntegerKlass* IntegerKlass::get_instance() {
    if (_instance == NULL) {
        _instance = new IntegerKlass();
    }
    return _instance;
}

PyInteger::PyInteger(int value) : _value(value) {
    set_klass(IntegerKlass::get_instance());
}

PyObject* IntegerKlass::lt(PyObject* x, PyObject* y) {
    if (x->klass() != y->klass()) {
        return Universe::Py_False;
    }

    PyInteger* ix = (PyInteger*)x;
    PyInteger* iy = (PyInteger*)y;

    assert(ix && (ix->klass() == (Klass*)this));
    assert(iy && (iy->klass() == (Klass*)this));

    if (ix->value() < iy->value()) {
        return Universe::Py_True;
    } else {
        return Universe::Py_False;
    }
}

PyObject* IntegerKlass::le(PyObject* x, PyObject* y) {
    if (x->klass() != y->klass()) {
        return Universe::Py_False;
    }

    PyInteger* ix = (PyInteger*)x;
    PyInteger* iy = (PyInteger*)y;

    assert(ix && (ix->klass() == (Klass*)this));
    assert(iy && (iy->klass() == (Klass*)this));

    if (ix->value() <= iy->value()) {
        return Universe::Py_True;
    } else {
        return Universe::Py_False;
    }
}

PyObject* IntegerKlass::eq(PyObject* x, PyObject* y) {
    if (x->klass() != y->klass()) {
        return Universe::Py_False;
    }

    PyInteger* ix = (PyInteger*)x;
    PyInteger* iy = (PyInteger*)y;

    assert(ix && (ix->klass() == (Klass*)this));
    assert(iy && (iy->klass() == (Klass*)this));

    if (ix->value() == iy->value()) {
        return Universe::Py_True;
    } else {
        return Universe::Py_False;
    }    
}

PyObject* IntegerKlass::ne(PyObject* x, PyObject* y) {
    if (x->klass() != y->klass()) {
        return Universe::Py_False;
    }

    PyInteger* ix = (PyInteger*)x;
    PyInteger* iy = (PyInteger*)y;

    assert(ix && (ix->klass() == (Klass*)this));
    assert(iy && (iy->klass() == (Klass*)this));

    if (ix->value() != iy->value()) {
        return Universe::Py_True;
    } else {
        return Universe::Py_False;
    }   
}

PyObject* IntegerKlass::gt(PyObject* x, PyObject* y) {
    if (x->klass() != y->klass()) {
        return Universe::Py_False;
    }

    PyInteger* ix = (PyInteger*)x;
    PyInteger* iy = (PyInteger*)y;

    assert(ix && (ix->klass() == (Klass*)this));
    assert(iy && (iy->klass() == (Klass*)this));

    if (ix->value() > iy->value()) {
        return Universe::Py_True;
    } else {
        return Universe::Py_False;
    }    
}

PyObject* IntegerKlass::ge(PyObject* x, PyObject* y) {
    if (x->klass() != y->klass()) {
        return Universe::Py_False;
    }

    PyInteger* ix = (PyInteger*)x;
    PyInteger* iy = (PyInteger*)y;

    assert(ix && (ix->klass() == (Klass*)this));
    assert(iy && (iy->klass() == (Klass*)this));

    if (ix->value() >= iy->value()) {
        return Universe::Py_True;
    } else {
        return Universe::Py_False;
    }   
}

PyObject* IntegerKlass::add(PyObject* x, PyObject* y) {
    if (x->klass() != y->klass()) {
        return Universe::Py_False;
    }

    PyInteger* ix = (PyInteger*)x;
    PyInteger* iy = (PyInteger*)y;

    assert(ix && (ix->klass() == (Klass*)this));
    assert(iy && (iy->klass() == (Klass*)this));

    return new PyInteger(ix->value() + iy->value());
} 

PyObject* IntegerKlass::sub(PyObject* x, PyObject* y) {
    if (x->klass() != y->klass()) {
        return Universe::Py_False;
    }

    PyInteger* ix = (PyInteger*)x;
    PyInteger* iy = (PyInteger*)y;

    assert(ix && (ix->klass() == (Klass*)this));
    assert(iy && (iy->klass() == (Klass*)this));

    return new PyInteger(ix->value() - iy->value());
} 

PyObject* IntegerKlass::mul(PyObject* x, PyObject* y) {
    if (x->klass() != y->klass()) {
        return Universe::Py_False;
    }

    PyInteger* ix = (PyInteger*)x;
    PyInteger* iy = (PyInteger*)y;

    assert(ix && (ix->klass() == (Klass*)this));
    assert(iy && (iy->klass() == (Klass*)this));

    return new PyInteger(ix->value() * iy->value());
} 

PyObject* IntegerKlass::div(PyObject* x, PyObject* y) {
    if (x->klass() != y->klass()) {
        return Universe::Py_False;
    }

    PyInteger* ix = (PyInteger*)x;
    PyInteger* iy = (PyInteger*)y;

    assert(ix && (ix->klass() == (Klass*)this));
    assert(iy && (iy->klass() == (Klass*)this));

    return new PyInteger(ix->value() / iy->value());
} 

PyObject* IntegerKlass::mod(PyObject* x, PyObject* y) {
    if (x->klass() != y->klass()) {
        return Universe::Py_False;
    }

    PyInteger* ix = (PyInteger*)x;
    PyInteger* iy = (PyInteger*)y;

    assert(ix && (ix->klass() == (Klass*)this));
    assert(iy && (iy->klass() == (Klass*)this));

    return new PyInteger(ix->value() % iy->value());
} 