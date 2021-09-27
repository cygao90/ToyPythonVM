#include "FrameObject.h"

FrameObject::FrameObject(CodeObject* codes) {
    _consts = codes->co_consts;
    _names  = codes->co_names;

    _locals = new Map<PyObject*, PyObject*>();

    _stack  = new PyList<PyObject*>();

    _fast_locals = new PyList<PyObject*>();

    _codes  = codes;
    _pc     = 0;
    _sender = NULL;
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

FrameObject::FrameObject(FunctionObject* func, PyList<PyObject*>* args) {
    _codes = func->_func_code;
    _consts = _codes->co_consts;
    _names = _codes->co_names;
    _locals = new Map<PyObject* ,PyObject*>();
    _stack = new PyList<PyObject*>();
    _fast_locals = new PyList<PyObject*>();
    if (args) {
        for (int i = 0; i < args->size(); i++) {
            _fast_locals->set(i, args->get(i));
        }
    }
    _pc = 0;
    _sender = NULL;
}

FrameObject::~FrameObject() {}