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
        r_ref(O);\
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

    // char object_type = file_stream->read();
    // if (object_type == ('c' | FLAG_REF)) {
    //     CodeObject* result = get_code_object();
    //     printf("Parse OK!\n");
    //     return result;
    // }
    CodeObject* result = (CodeObject*)r_object();
    printf("Parse OK!\n");
    return result;
}

CodeObject* BinaryFileParser::r_code_object() {
    int argcount        = file_stream->read_int();
    int posonlyargcount = file_stream->read_int();
    int kwonlyargcount  = file_stream->read_int();
    int nlocals         = file_stream->read_int();
    int stacksize       = file_stream->read_int();
    int flags           = file_stream->read_int();

    PyString* byte_codes        = r_byte_codes();
    PyList<PyObject*>* consts   = r_consts();
    PyList<PyObject*>* names    = r_names();
    PyList<PyObject*>* varnames = r_varnames();
    PyList<PyObject*>* freevars = r_freevars();
    PyList<PyObject*>* cellvars = r_cellvars();
    PyString* filename          = r_filename();
    PyString* modulename        = r_name();
    int begin_line_no           = file_stream->read_int();
    PyString* lnotab            = r_lnotab();

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

PyObject* BinaryFileParser::r_object() {

    PyString* str;
    PyObject* retval;
   
    int code = file_stream->read();
    int flag     = code & FLAG_REF;
    int obj_type = code & ~FLAG_REF;
    int n;
    switch (obj_type) {

    case TYPE_CODE: {
        int idx = r_ref_reverse(flag);
        std::cout << "got a code object" << std::endl;
        retval = r_code_object();
        r_ref_insert(retval, idx, flag);
        break;
    }
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
        str = r_string(n);
        _object_table.add(str);
        retval = str;
        break;

    case TYPE_STRING:
        n = file_stream->read_int();
        retval = r_string(n);
        R_REF(retval);
        break;

    case TYPE_SHORT_ASCII:
    case TYPE_SHORT_ASCII_INTERNED:
        n = file_stream->read();
        str = r_string(n);
        retval = str;
        R_REF(retval);
        break;

    case TYPE_REF:
        retval = _object_table.get(file_stream->read_int());
        break;

    case TYPE_TUPLE:
        n = file_stream->read_int();
        retval = r_tuple(n);
        R_REF(retval);
        break;

    case TYPE_SMALL_TUPLE:
        n = file_stream->read();
        retval = r_tuple(n);
        R_REF(retval);
        break;

    default:
        printf("Not inplemented: %x\n", code);
        exit(-1);

    }

    return retval;
}

PyList<PyObject*>* BinaryFileParser::r_tuple(int n) {
    PyList<PyObject*>* list = new PyList<PyObject*>();
    for (int i = 0; i < n; i++) {
        list->add(r_object());
    }
    return list;
}

PyString* BinaryFileParser::r_string(int n) {
    int length = n;
    string s;
    for (int i = 0; i < length; i++) {
        s.push_back(file_stream->read());
    }
    return new PyString(s);
}

PyString* BinaryFileParser::r_byte_codes() {
    return (PyString*)r_object();
}

PyList<PyObject*>* BinaryFileParser::r_consts() {
    return (PyList<PyObject*>*)r_object();
}

PyList<PyObject*>* BinaryFileParser::r_names() {
    return (PyList<PyObject*>*)r_object();
}

PyList<PyObject*>* BinaryFileParser::r_varnames() {
    return (PyList<PyObject*>*)r_object();
}

PyList<PyObject*>* BinaryFileParser::r_freevars() {
    return (PyList<PyObject*>*)r_object();
}

PyList<PyObject*>* BinaryFileParser::r_cellvars() {
    return (PyList<PyObject*>*)r_object();
}

PyString* BinaryFileParser::r_filename() {
    return r_name();
}

PyString* BinaryFileParser::r_name() {
    return (PyString*)r_object();
}

PyString* BinaryFileParser::r_lnotab() {
    return (PyString*)r_object();
}

PyObject* BinaryFileParser::r_ref(PyObject* o) {
    _object_table.add(o);
    return o;
}

int BinaryFileParser::r_ref_reverse(int flag) {
    if (flag) {
        int idx = _object_table.size();
        _object_table.add(Universe::Py_None);
        return idx;
    } else {
        return 0;
    }
}

PyObject* BinaryFileParser::r_ref_insert(PyObject* o, int idx, int flag) {
    if (o != NULL && flag) {
        _object_table.set(idx, o);
    }
    return o;
}