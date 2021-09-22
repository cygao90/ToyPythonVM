#ifndef PY_STRING_H
#define PY_STRING_H

#include <string>
#include "PyObject.h"

using std::string;

class PyString : public PyObject {
private:
    string _value;

public:

    void get_value() { std::cout << _value << "\n"; }

    PyString(const string s) : _value(s) {}

    string& value() { return _value; } 
    int length() { return _value.size(); }
};

#endif