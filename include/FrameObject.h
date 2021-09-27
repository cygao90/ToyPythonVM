#ifndef FRAME_OBJECT_H
#define FRAME_OBJECT_H

#include "FunctionObject.h"
#include "CodeObject.h"
#include "Map.h"

class FunctionObject;
class FrameObject {
public:
    FrameObject(CodeObject* codes);
    FrameObject(FunctionObject* func, PyList<PyObject*>* args);
    ~FrameObject();

    PyList<PyObject*>* _stack;

    PyList<PyObject*>* _consts;
    PyList<PyObject*>* _names;

    Map<PyObject*, PyObject*>* _locals;
    PyList<PyObject*>* _fast_locals;

    CodeObject* _codes;
    int         _pc;
    FrameObject* _sender;

public:
    void set_pc(int x)      { _pc = x; }
    int get_pc() const      { return _pc; }

    PyList<PyObject*>* stack() const          { return _stack; }
    PyList<PyObject*>* consts() const         { return _consts; }
    PyList<PyObject*>* names() const          { return _names; }
    Map<PyObject*, PyObject*>* locals() const { return _locals; }
    FrameObject* sender() const               { return _sender; }
    bool is_first_frame()                     { return _sender == NULL; }
    void set_sender(FrameObject* x)           { _sender = x; }

    bool has_more_codes();
    unsigned char get_op_code();
    unsigned char get_op_arg();
};

#endif