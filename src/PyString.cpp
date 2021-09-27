#include "PyString.h"
#include "Universe.h"

StringKlass* StringKlass::_instance = NULL;

StringKlass::StringKlass() {

}

StringKlass* StringKlass::get_instance() {
    if (_instance == NULL) {
        _instance = new StringKlass();
    }
    return _instance;
}

PyString::PyString(const string s) : _value(s) {
    set_klass(StringKlass::get_instance());
}

PyObject* StringKlass::lt(PyObject* x, PyObject* y) {
    if (x->klass() != y->klass()) {
        return Universe::Py_False;
    }

    PyString* ix = (PyString*)x;
    PyString* iy = (PyString*)y;

    assert(ix && (ix->klass() == (Klass*)this));
    assert(iy && (iy->klass() == (Klass*)this));

    if (ix->value() < iy->value()) {
        return Universe::Py_True;
    } else {
        return Universe::Py_False;
    }
}

PyObject* StringKlass::le(PyObject* x, PyObject* y) {
    if (x->klass() != y->klass()) {
        return Universe::Py_False;
    }

    PyString* ix = (PyString*)x;
    PyString* iy = (PyString*)y;

    assert(ix && (ix->klass() == (Klass*)this));
    assert(iy && (iy->klass() == (Klass*)this));

    if (ix->value() <= iy->value()) {
        return Universe::Py_True;
    } else {
        return Universe::Py_False;
    }
}

PyObject* StringKlass::eq(PyObject* x, PyObject* y) {
    if (x->klass() != y->klass()) {
        return Universe::Py_False;
    }

    PyString* ix = (PyString*)x;
    PyString* iy = (PyString*)y;

    assert(ix && (ix->klass() == (Klass*)this));
    assert(iy && (iy->klass() == (Klass*)this));

    if (ix->value() == iy->value()) {
        return Universe::Py_True;
    } else {
        return Universe::Py_False;
    }    
}

PyObject* StringKlass::ne(PyObject* x, PyObject* y) {
    if (x->klass() != y->klass()) {
        return Universe::Py_False;
    }

    PyString* ix = (PyString*)x;
    PyString* iy = (PyString*)y;

    assert(ix && (ix->klass() == (Klass*)this));
    assert(iy && (iy->klass() == (Klass*)this));

    if (ix->value() != iy->value()) {
        return Universe::Py_True;
    } else {
        return Universe::Py_False;
    }   
}

PyObject* StringKlass::gt(PyObject* x, PyObject* y) {
    if (x->klass() != y->klass()) {
        return Universe::Py_False;
    }

    PyString* ix = (PyString*)x;
    PyString* iy = (PyString*)y;

    assert(ix && (ix->klass() == (Klass*)this));
    assert(iy && (iy->klass() == (Klass*)this));

    if (ix->value() > iy->value()) {
        return Universe::Py_True;
    } else {
        return Universe::Py_False;
    }    
}

PyObject* StringKlass::ge(PyObject* x, PyObject* y) {
    if (x->klass() != y->klass()) {
        return Universe::Py_False;
    }

    PyString* ix = (PyString*)x;
    PyString* iy = (PyString*)y;

    assert(ix && (ix->klass() == (Klass*)this));
    assert(iy && (iy->klass() == (Klass*)this));

    if (ix->value() >= iy->value()) {
        return Universe::Py_True;
    } else {
        return Universe::Py_False;
    }   
}

PyObject* StringKlass::add(PyObject* x, PyObject* y) {
    if (x->klass() != y->klass()) {
        return Universe::Py_False;
    }

    PyString* ix = (PyString*)x;
    PyString* iy = (PyString*)y;

    assert(ix && (ix->klass() == (Klass*)this));
    assert(iy && (iy->klass() == (Klass*)this));

    return new PyString(ix->value() + iy->value());
} 

// PyObject* StringKlass::sub(PyObject* x, PyObject* y) {
//     if (x->klass() != y->klass()) {
//         return Universe::Py_False;
//     }

//     PyString* ix = (PyString*)x;
//     PyString* iy = (PyString*)y;

//     assert(ix && (ix->klass() == (Klass*)this));
//     assert(iy && (iy->klass() == (Klass*)this));

//     return new PyString(ix->value() - iy->value());
// } 

// PyObject* StringKlass::mul(PyObject* x, PyObject* y) {
//     if (x->klass() != y->klass()) {
//         return Universe::Py_False;
//     }

//     PyString* ix = (PyString*)x;
//     PyString* iy = (PyString*)y;

//     assert(ix && (ix->klass() == (Klass*)this));
//     assert(iy && (iy->klass() == (Klass*)this));

//     return new PyString(ix->value() * iy->value());
// } 

// PyObject* StringKlass::div(PyObject* x, PyObject* y) {
//     if (x->klass() != y->klass()) {
//         return Universe::Py_False;
//     }

//     PyString* ix = (PyString*)x;
//     PyString* iy = (PyString*)y;

//     assert(ix && (ix->klass() == (Klass*)this));
//     assert(iy && (iy->klass() == (Klass*)this));

//     return new PyString(ix->value() / iy->value());
// } 

// PyObject* StringKlass::mod(PyObject* x, PyObject* y) {
//     if (x->klass() != y->klass()) {
//         return Universe::Py_False;
//     }

//     PyString* ix = (PyString*)x;
//     PyString* iy = (PyString*)y;

//     assert(ix && (ix->klass() == (Klass*)this));
//     assert(iy && (iy->klass() == (Klass*)this));

//     return new PyString(ix->value() % iy->value());
// } 

PyObject* StringKlass::len(PyObject* x) {
    return new PyInteger(((PyString*)x)->length());
}