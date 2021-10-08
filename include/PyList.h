#ifndef LIST_H
#define LIST_H

#include "PyObject.h"
#include "ArrayList.h"

class PyList : public PyObject {
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
};

#endif