#ifndef BINARY_FILE_PARSER_H
#define BINARY_FILE_PARSER_H

#include "BufferInputStream.h"
#include "CodeObject.h"
#include "PyString.h"
#include "PyInteger.h"
#include "PyObject.h"

class BinaryFileParser {
private:
    BufferInputStream* file_stream;
    PyList<PyObject*> _object_table;

public:
    BinaryFileParser(BufferInputStream* file_stream): file_stream(file_stream) {}

    CodeObject*        parse();    
    CodeObject*        r_code_object();
    PyString*          r_byte_codes();
    PyList<PyObject*>* r_consts();
    PyList<PyObject*>* r_names();
    PyList<PyObject*>* r_varnames();
    PyList<PyObject*>* r_freevars();
    PyList<PyObject*>* r_cellvars();
    PyString*          r_filename();
    PyString*          r_name();
    PyString*          r_lnotab();

    PyList<PyObject*>* r_tuple(int n);
    PyString*          r_string(int n);
    PyObject*          r_object();
    PyObject*          r_ref(PyObject* o);
    int                r_ref_reverse(int flag);
    PyObject*          r_ref_insert(PyObject* o, int idx, int flag);
};

#endif