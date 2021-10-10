#include "PyList.h"
#include "PyString.h"
#include "PyInteger.h"
#include "FunctionObject.h"

ListKlass* ListKlass::_instance = NULL;

PyList::PyList() {
    _inner_list = new ArrayList<PyObject*>();
    set_klass(ListKlass::get_instace());
}

ListKlass::ListKlass() {
    Map<string, PyObject*>* _klass_dict = new Map<string, PyObject*>();
    _klass_dict->insert("append", new FunctionObject(append));
    set_klass_dict(_klass_dict);
    set_name(new PyString("List"));
}

ListKlass* ListKlass::get_instace() {
    if (_instance == NULL) {
        _instance = new ListKlass();
    }
    return _instance;
}

PyObject* ListKlass::in(PyObject* x, PyObject* y) {
    assert(x && x->klass() == (Klass*)this);

    PyList* lx = (PyList*)x;
    int size = lx->size();
    for (int i = 0; i < size; i++) {
        if (lx->get(i)->klass() == y->klass() && lx->get(i)->eq(y) == Universe::Py_True) {
            return Universe::Py_True;
        }
    }
    return Universe::Py_False;
}

PyObject* ListKlass::not_in(PyObject* x, PyObject* y) {
    if (in(x, y) == Universe::Py_False) {
        return Universe::Py_True;
    } else {
        return Universe::Py_False;
    }
}

PyObject* ListKlass::print(PyObject* x) {
    PyList* l = (PyList*)x;
    printf("[");
    for (int i = 0; i < l->size() - 1; i++) {
        l->get(i)->print(l->get(i));
        printf(", ");
    }
    l->get(l->size() - 1)->print(l->get(l->size() - 1)); // TODO: argument
    printf("]");
    return NULL;
}

PyObject* ListKlass::subscr(PyObject* x, PyObject* y) {
    assert(x && x->klass() == this);
    assert(y && y->klass() == IntegerKlass::get_instance());

    return ((PyList*)x)->get(((PyInteger*)y)->value());
}

PyObject* append(PyList* args) {
    ((PyList*)args->get(0))->add(args->get(1));
    return Universe::Py_None;
}