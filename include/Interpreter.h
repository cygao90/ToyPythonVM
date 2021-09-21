#ifndef INTERPRETER_H 
#define INTERPRETER_H

#include "CodeObject.h"

class Interpreter {
private:
    PyList<PyObject*>* _stack;
    PyList<PyObject*>* _consts;

public:
    void run(CodeObject* codes);
};

#endif