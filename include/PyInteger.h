#ifndef PY_INTEGER_H
#define PY_INTEGER_H

#include "PyObject.h"

class PyInteger : public PyObject {
private:
    int _value;

public:
    PyInteger(int value) : _value(value) {}
    int value() { return _value; }
};

#endif