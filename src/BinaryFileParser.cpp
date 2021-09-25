#include <iostream>
#include <assert.h>
#include "BinaryFileParser.h"
#include "PyInteger.h"
#include "Universe.h"

#define TYPE_NULL               '0'
#define TYPE_NONE               'N'
#define TYPE_FALSE              'F'
#define TYPE_TRUE               'T'
#define TYPE_STOPITER           'S'
#define TYPE_ELLIPSIS           '.'
#define TYPE_INT                'i'
/* TYPE_INT64 is not generated anymore.
   Supported for backward compatibility only. */
#define TYPE_INT64              'I'
#define TYPE_FLOAT              'f'
#define TYPE_BINARY_FLOAT       'g'
#define TYPE_COMPLEX            'x'
#define TYPE_BINARY_COMPLEX     'y'
#define TYPE_LONG               'l'
#define TYPE_STRING             's'
#define TYPE_INTERNED           't'
#define TYPE_REF                'r'
#define TYPE_TUPLE              '('
#define TYPE_LIST               '['
#define TYPE_DICT               '{'
#define TYPE_CODE               'c'
#define TYPE_UNICODE            'u'
#define TYPE_UNKNOWN            '?'
#define TYPE_SET                '<'
#define TYPE_FROZENSET          '>'
#define FLAG_REF                '\x80' /* with a type, add obj to index */

#define TYPE_ASCII              'a'
#define TYPE_ASCII_INTERNED     'A'
#define TYPE_SMALL_TUPLE        ')'
#define TYPE_SHORT_ASCII        'z'
#define TYPE_SHORT_ASCII_INTERNED 'Z'

#define WFERR_OK 0
#define WFERR_UNMARSHALLABLE 1
#define WFERR_NESTEDTOODEEP 2
#define WFERR_NOMEMORY 3

#define R_REF(O) do {\
    if (flag) \
        get_ref(O);\
} while(0)

CodeObject* BinaryFileParser::parse() {
    int magic_number = file_stream->read_int();
    printf("The magic number is: %x\n", magic_number);
    int bit_field = file_stream->read_int();
    printf("The bit field is: %x\n", bit_field);
    if (bit_field != 0) {
        printf("Hash based pyc is not supported\n");
        exit(-1);
    }
    int timestamp = file_stream->read_int();
    printf("The timestamp is: %x\n", timestamp);
    int file_size = file_stream->read_int();
    printf("The file size is: %x\n", file_size);

    char object_type = file_stream->read();
    if (object_type == ('c' | FLAG_REF)) {
        CodeObject* result = get_code_object();
        printf("Parse OK!\n");
        return result;
    }

    return NULL;
}

CodeObject* BinaryFileParser::get_code_object() {
    int argcount  = file_stream->read_int();
    std::cout << argcount << std::endl;    
    int posonlyargcount = file_stream->read_int();
    int kwonlyargcount  = file_stream->read_int();
    int nlocals   = file_stream->read_int();
    int stacksize = file_stream->read_int();
    int flags     = file_stream->read_int();
    std::cout << flags << std::endl; 

    PyString* byte_codes = get_byte_codes();
    PyList<PyObject*>* consts   = get_consts();
    PyList<PyObject*>* names    = get_names();
    PyList<PyObject*>* varnames = get_varnames();
    PyList<PyObject*>* freevars = get_freevars();
    PyList<PyObject*>* cellvars = get_cellvars();
    PyString* filename = get_filename();
    PyString* modulename = get_name();
    int begin_line_no = file_stream->read_int();
    PyString* lnotab = get_lnotab();

    return new CodeObject(
        argcount,
        posonlyargcount,
        kwonlyargcount,
        nlocals,
        stacksize,
        flags,
        byte_codes,
        consts,
        names,
        varnames,
        freevars,
        cellvars,
        filename,
        modulename,
        begin_line_no,
        lnotab);
}

PyString* BinaryFileParser::get_byte_codes() {
    assert(file_stream->read() == TYPE_STRING);
    int n = file_stream->read_int();
    return get_string(n);
}

PyObject* BinaryFileParser::get_object() {

    PyString* str;
    PyObject* retval;
   
    char code = file_stream->read();
    char flag     = code & FLAG_REF;
    char obj_type = code & ~FLAG_REF;
    int n;
    switch (obj_type) {

    case TYPE_CODE:
        std::cout << "got a code object" << std::endl;
        retval = get_code_object();
        get_ref(retval);
        break;

    case TYPE_INT:
        retval = new PyInteger(file_stream->read_int());
        R_REF(retval);
        break;

    case TYPE_NONE:
        retval = Universe::Py_None;
        break;

    case TYPE_INTERNED:
        assert(0);
        n = file_stream->read_int();
        str = get_string(n);
        _object_table.add(str);
        retval = str;
        break;

    case TYPE_STRING:
        n = file_stream->read_int();
        retval = get_string(n);
        R_REF(retval);
        break;

    case TYPE_SHORT_ASCII:
    case TYPE_SHORT_ASCII_INTERNED:
        n = file_stream->read();
        str = get_string(n);
        retval = str;
        R_REF(retval);
        break;

    case TYPE_REF:
        retval = _object_table.get(file_stream->read_int());
        break;

    case TYPE_TUPLE:
        n = file_stream->read_int();
        retval = get_tuple(n);
        R_REF(retval);
        break;

    case TYPE_SMALL_TUPLE:
        n = file_stream->read();
        retval = get_tuple(n);
        R_REF(retval);
        break;

    default:
        printf("Not inplemented: %x\n", code);
        exit(-1);

    }

    return retval;
}

PyList<PyObject*>* BinaryFileParser::get_tuple(int n) {
    PyList<PyObject*>* list = new PyList<PyObject*>();
    for (int i = 0; i < n; i++) {
        list->add(get_object());
    }
    return list;
}

PyString* BinaryFileParser::get_string(int n) {
    int length = n;
    string s;
    for (int i = 0; i < length; i++) {
        s.push_back(file_stream->read());
    }
    return new PyString(s);
}

PyList<PyObject*>* BinaryFileParser::get_consts() {
    return (PyList<PyObject*>*)get_object();
}

PyList<PyObject*>* BinaryFileParser::get_names() {
    return (PyList<PyObject*>*)get_object();
}

PyList<PyObject*>* BinaryFileParser::get_varnames() {
    return (PyList<PyObject*>*)get_object();
}

PyList<PyObject*>* BinaryFileParser::get_freevars() {
    return (PyList<PyObject*>*)get_object();
}

PyList<PyObject*>* BinaryFileParser::get_cellvars() {
    return (PyList<PyObject*>*)get_object();
}

PyString* BinaryFileParser::get_filename() {
    return get_name();
}

PyString* BinaryFileParser::get_name() {
    return (PyString*)get_object();
}

PyString* BinaryFileParser::get_lnotab() {
    char type = file_stream->read();
    type = type & ~FLAG_REF;

    if (type != TYPE_STRING && type != TYPE_INTERNED) {
        file_stream->unread();
        return NULL;
    }
    
    int n = file_stream->read_int();
    return get_string(n);
}

void BinaryFileParser::get_ref(PyObject* o) {
    _object_table.add(o);
}