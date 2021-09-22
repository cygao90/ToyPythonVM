#include "FrameObject.h"

FrameObject::FrameObject(CodeObject* codes) {
    _consts = codes->co_consts;
    _names  = codes->co_names;

    _locals = new Map<PyObject*, PyObject*>();

    _stack  = new PyList<PyObject*>();

    _codes  = codes;
    _pc     = 0;
}

unsigned char FrameObject::get_op_arg() {
    return _codes->co_code->value()[_pc++];

}

unsigned char FrameObject::get_op_code() {
    return _codes->co_code->value()[_pc++];
}

bool FrameObject::has_more_codes() {
    return _pc < _codes->co_code->length();
}