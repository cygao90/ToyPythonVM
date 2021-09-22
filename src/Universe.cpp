#include "Universe.h"

PyInteger* Universe::Py_False = NULL;

PyInteger* Universe::Py_True = NULL;

PyObject* Universe::Py_None = NULL;

void Universe::genesis() {
    Py_False = new PyInteger(0);
    Py_True = new PyInteger(1);
    Py_None = new PyObject();
}

void Universe::destroy() {

}