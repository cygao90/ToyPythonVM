#ifndef INTERPRETER_H 
#define INTERPRETER_H

#include "CodeObject.h"
#include "FrameObject.h"

class Interpreter {
private:
    FrameObject* _frame;
    PyObject*    _ret_value;
public:
    Interpreter();
    void run(CodeObject* codes);
    void eval_frame();
    void build_frame(PyObject* callable);
    void destroy_frame();
    void leave_frame();
};

#endif