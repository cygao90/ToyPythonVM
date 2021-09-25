#include "FunctionObject.h"

FunctionKlass* FunctionKlass::_instance = NULL;

FunctionKlass* FunctionKlass::get_instance() {
    if (_instance == NULL) {
        _instance = new FunctionKlass();
    }
    return _instance;
}

FunctionKlass::FunctionKlass() {

}

FunctionObject::FunctionObject(PyObject* code_object) {
    CodeObject* co = (CodeObject*)code_object;

    _func_code = co;
    _func_name = co->co_name;
    _flags = co->co_flags;

    set_klass(FunctionKlass::get_instance());
}