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
    PyList<PyString*> _string_table;

public:
    BinaryFileParser(BufferInputStream* file_stream): file_stream(file_stream) {}
    PyString* get_string();

    CodeObject*      parse();    
    CodeObject*      get_code_object();
    PyString*        get_byte_codes();
    PyList<PyObject*>* get_consts();
    PyList<PyObject*>* get_names();
    PyList<PyObject*>* get_varnames();
    PyList<PyObject*>* get_freevars();
    PyList<PyObject*>* get_cellvars();
    PyString*        get_filename();
    PyString*        get_name();
    PyString*        get_lnotab();

    PyList<PyObject*>* get_tuple(bool is_small);
    PyString*          get_string(bool is_short);
};

#endif