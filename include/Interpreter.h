#ifndef INTERPRETER_H 
#define INTERPRETER_H

#include "CodeObject.h"
#include "FrameObject.h"

class Interpreter {
private:
    FrameObject* _frame;
    PyObject*    _ret_value;
    Map<string, PyObject*>* _builtins;
public:
    Interpreter();
    void run(CodeObject* codes);
    void eval_frame();
    void build_frame(PyObject* callable, PyList* args);
    void destroy_frame();
    void leave_frame();
};

#endif