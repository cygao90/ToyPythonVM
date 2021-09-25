#ifndef FUNCTION_OBJECT_H
#define FUNCTION_OBJECT_H

#include "PyObject.h"
#include "Klass.h"
#include "FrameObject.h"

class FunctionKlass : public Klass {
private:
    FunctionKlass();
    static FunctionKlass* _instance;

public:
    static FunctionKlass* get_instance();
};

class FunctionObject : public PyObject {
friend class FunctionKlass;
friend class FrameObject;

private:
    CodeObject* _func_code;
    PyString*   _func_name;

    unsigned int _flags;

public:
    FunctionObject(PyObject* code_object);
    FunctionObject(Klass* klass) : _func_code(NULL), _func_name(NULL), _flags(0) {
        set_klass(klass);
    }

    PyString* func_name() { return _func_name; }
    int flags()           { return _flags; }
};

#endif