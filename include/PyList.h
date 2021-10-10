#ifndef LIST_H
#define LIST_H

#include "PyObject.h"
#include "ArrayList.h"

class ListKlass : public Klass {
private:
    ListKlass();
    static ListKlass* _instance;

public:
    static ListKlass* get_instace();

    virtual PyObject* in(PyObject* x, PyObject* y);
    virtual PyObject* not_in(PyObject* x, PyObject* y);

    virtual PyObject* print(PyObject* args);
    virtual PyObject* subscr(PyObject* x, PyObject* y);
};

class PyList : public PyObject {
friend class ListKlass;

private:
    ArrayList<PyObject*>* _inner_list;

public:
    PyList();
    ArrayList<PyObject*>* inner_list() { return _inner_list; }

    int size()                         { return _inner_list->size(); }
    void add(PyObject* obj)            { _inner_list->add(obj); }
    PyObject* get(int index)           { return _inner_list->get(index); }
    PyObject* pop()                    { return _inner_list->pop(); }
    void set(int index, PyObject* obj) { _inner_list->set(index, obj); }
    PyObject*& top()                    { return _inner_list->top(); }
    void insert(int index, PyObject* obj) { return _inner_list->insert(index, obj); }
};

PyObject* append(PyList* args);

#endif