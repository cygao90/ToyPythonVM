#ifndef INTERPRETER_H 
#define INTERPRETER_H

#include "CodeObject.h"
#include "FrameObject.h"

class Interpreter {
private:
    FrameObject* _frame;
public:
    Interpreter();
    void run(CodeObject* codes);
};

#endif