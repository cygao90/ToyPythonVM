#include "FunctionObject.h"

FunctionKlass* FunctionKlass::_instance = NULL;
NativeFunctionKlass* NativeFunctionKlass::_instance = NULL;

FunctionKlass* FunctionKlass::get_instance() {
    if (_instance == NULL) {
        _instance = new FunctionKlass();
    }
    return _instance;
}

FunctionKlass::FunctionKlass() {
    set_name(new PyString("function"));
}

FunctionObject::FunctionObject(PyObject* code_object) {
    CodeObject* co = (CodeObject*)code_object;

    _func_code = co;
    _func_name = co->co_name;
    _flags = co->co_flags;

    set_klass(FunctionKlass::get_instance());
}

FunctionObject::FunctionObject(NativeFuncPointer nfp) {
    _func_code = NULL;
    _func_name = NULL;
    _flags     = 0;
    _native_func = nfp;

    set_klass(NativeFunctionKlass::get_instance());
}

PyObject* FunctionObject::call(PyList<PyObject*>* args) {
    return (*_native_func)(args);
}

NativeFunctionKlass* NativeFunctionKlass::get_instance() {
    if (_instance == NULL) {
        _instance = new NativeFunctionKlass();
    }
    return _instance;
}

NativeFunctionKlass::NativeFunctionKlass() {
    set_name(new PyString("native function"));
}

PyObject* len(PyList<PyObject*>* args) {
    return args->get(0)->len(args);
}

PyObject* print(PyList<PyObject*>* args) {
    for (int i = 0; i < args->length() - 1; i++) {
        args->get(i)->print(args);
        printf(" ");
    }
    args->get(args->length() - 1)->print(args);
    return NULL;
}

FunctionObject::FunctionObject(Klass* klass) : _func_code(NULL), _func_name(NULL), _flags(0) {
    set_klass(klass);
}