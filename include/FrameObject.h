#ifndef FRAME_OBJECT_H
#define FRAME_OBJECT_H

#include "FunctionObject.h"
#include "CodeObject.h"
#include "Map.h"

class FunctionObject;
class FrameObject {
public:
    FrameObject(CodeObject* codes);
    FrameObject(FunctionObject* func, PyList* args);
    ~FrameObject();

    PyList* _stack;

    PyList* _consts;
    PyList* _names;

    Map<PyObject*, PyObject*>* _locals;
    Map<PyObject*, PyObject*>* _globals;
    PyList* _fast_locals;

    CodeObject* _codes;
    int         _pc;
    FrameObject* _sender;

public:
    void set_pc(int x)      { _pc = x; }
    int get_pc() const      { return _pc; }

    PyList* stack() const          { return _stack; }
    PyList* consts() const         { return _consts; }
    PyList* names() const          { return _names; }
    Map<PyObject*, PyObject*>* locals() const { return _locals; }
    Map<PyObject*, PyObject*>* globals() const { return _globals; }
    FrameObject* sender() const               { return _sender; }
    bool is_first_frame()                     { return _sender == NULL; }
    void set_sender(FrameObject* x)           { _sender = x; }

    bool has_more_codes();
    unsigned char get_op_code();
    unsigned char get_op_arg();
};

#endif