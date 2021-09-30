#include "Universe.h"
#include "PyString.h"
#include "PyInteger.h"
#include "FunctionObject.h"
#include "Map.h"
#include <stddef.h>

PyInteger* Universe::Py_False = NULL;

PyInteger* Universe::Py_True = NULL;

PyObject* Universe::Py_None = NULL;

void Universe::genesis() {
    Py_False = new PyInteger(0);
    Py_True = new PyInteger(1);
    Py_None = new PyObject();

    Map<string, PyObject*>* klass_dict = new Map<string, PyObject*>();
    StringKlass::get_instance()->set_klass_dict(klass_dict);
    klass_dict->insert("upper", new FunctionObject(string_upper));
}

void Universe::destroy() {

}