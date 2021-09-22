#ifndef FRAME_OBJECT_H
#define FRAME_OBJECT_H

#include "CodeObject.h"
#include "Map.h"

class FrameObject {
public:
    FrameObject(CodeObject* codes);
    FrameObject();

    PyList<PyObject*>* _stack;

    PyList<PyObject*>* _consts;
    PyList<PyObject*>* _names;

    Map<PyObject*, PyObject*>* _locals;

    CodeObject* _codes;
    int         _pc;

public:
    void set_pc(int x)      { _pc = x; }
    int get_pc() const      { return _pc; }

    PyList<PyObject*>* stack() const          { return _stack; }
    PyList<PyObject*>* consts() const         { return _consts; }
    PyList<PyObject*>* names() const          { return _names; }
    Map<PyObject*, PyObject*>* locals() const { return _locals; }

    bool has_more_codes();
    unsigned char get_op_code();
    unsigned char get_op_arg();
};

#endif