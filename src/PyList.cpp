#include "PyList.h"

PyList::PyList() {
    _inner_list = new ArrayList<PyObject*>();
}