#include "PyList.h"
#include "PyString.h"
#include "PyInteger.h"

ListKlass* ListKlass::_instance = NULL;

PyList::PyList() {
    _inner_list = new ArrayList<PyObject*>();
    set_klass(ListKlass::get_instace());
}

ListKlass::ListKlass() {
    set_name(new PyString("List"));
}

ListKlass* ListKlass::get_instace() {
    if (_instance == NULL) {
        _instance = new ListKlass();
    }
    return _instance;
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