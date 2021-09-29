#ifndef UNIVERSE_H
#define UNIVERSE_H

class PyInteger;
class PyObject;

class Universe {
public:
    static PyInteger* Py_True;
    static PyInteger* Py_False;
    static PyObject*  Py_None;

    static void genesis();
    static void destroy();
};

#endif