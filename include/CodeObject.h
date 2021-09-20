#ifndef CODE_OBJECT_H
#define CODE_OBJECT_H

#include "PyObject.h"
#include "PyList.h"
#include "PyString.h"

class CodeObject : public PyObject {
public:
    int co_argcount;
    int co_posonlyargcount;
    int co_kwonlyargcount;
    int co_nlocals;
    int co_stacksize;
    int co_flags;

    PyString* co_code;
    PyList<PyObject*>* co_consts;
    PyList<PyObject*>* co_names;
    PyList<PyObject*>* co_varnames;
    PyList<PyObject*>* co_freevars;
    PyList<PyObject*>* co_cellvars;

    PyString* co_filename;
    PyString* co_name;

    int co_firstlineno;
    PyString* co_lnotab;

    CodeObject(
        int co_argcount,
        int co_posonlyargcount,
        int co_kwonlyargcount,
        int co_nlocals,
        int co_stacksize,
        int co_flags,
        PyString* co_code,
        PyList<PyObject*>* co_consts,
        PyList<PyObject*>* co_names,
        PyList<PyObject*>* co_varnames,
        PyList<PyObject*>* co_freevars,
        PyList<PyObject*>* co_cellvars,
        PyString* co_filename,
        PyString* co_name,
        int co_firstlineno,
        PyString* co_lnotab):
            co_argcount(co_argcount),
            co_posonlyargcount(co_posonlyargcount),
            co_kwonlyargcount(co_kwonlyargcount),
            co_nlocals(co_nlocals),
            co_stacksize(co_stacksize),
            co_flags(co_flags),
            co_code(co_code),
            co_consts(co_consts),
            co_names(co_names),
            co_varnames(co_varnames),
            co_freevars(co_freevars),
            co_filename(co_filename),
            co_name(co_name),
            co_firstlineno(co_firstlineno),
            co_lnotab(co_lnotab) {

        }

};

#endif