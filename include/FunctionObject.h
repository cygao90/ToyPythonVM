#ifndef FUNCTION_OBJECT_H
#define FUNCTION_OBJECT_H

#include "PyObject.h"
#include "Klass.h"
#include "CodeObject.h"
#include "Map.h"

class FunctionKlass : public Klass {
private:
    FunctionKlass();
    static FunctionKlass* _instance;

public:
    static FunctionKlass* get_instance();
};

class NativeFunctionKlass : public Klass {
private:
    NativeFunctionKlass();
    static NativeFunctionKlass* _instance;

public:
    static NativeFunctionKlass* get_instance();
};

typedef PyObject* (*NativeFuncPointer)(PyList* args);

class FunctionObject : public PyObject {
friend class FunctionKlass;
friend class FrameObject;

private:
    CodeObject* _func_code;
    PyString*   _func_name;

    unsigned int _flags;

    NativeFuncPointer _native_func;

    PyList* _defaults;

    Map<PyObject*, PyObject*>* _globals;

public:
    FunctionObject(PyObject* code_object);
    FunctionObject(Klass* klass);
    FunctionObject(NativeFuncPointer nfp);

    PyObject* call(PyList* args);

    PyList* defaults() { return _defaults; }
    void set_defaults(PyList* defaults);

    Map<PyObject*, PyObject*>* globals() { return _globals; }
    void set_globals(Map<PyObject*, PyObject*>* x) { _globals = x; }

    PyString* func_name() { return _func_name; }
    int flags()           { return _flags; }
};

class MethodKlass : public Klass {
private:
    MethodKlass();
    static MethodKlass* _instance;

public:
    static MethodKlass* get_instance();
};

class MethodObject : public PyObject {
friend MethodKlass;

private:
    PyObject* _owner;
    FunctionObject* _func;

public:
    MethodObject(FunctionObject* func);
    MethodObject(FunctionObject* func, PyObject* owner);

    static bool is_function(PyObject* x);

    void set_owner(PyObject* owner) { _owner = owner; }
    PyObject* owner()               { return _owner; }
    FunctionObject* func()          { return _func; }

};

PyObject* len(PyList* args);
PyObject* print(PyList* args);
PyObject* string_upper(PyList* args);

#endif