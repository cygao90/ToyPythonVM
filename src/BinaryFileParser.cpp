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

    return get_string();
}

PyString* BinaryFileParser::get_string() {
    int length = file_stream->read_int();
    string str_value;

    for (int i = 0; i < length; i++) {
        str_value.push_back(file_stream->read());
    }

    PyString* s = new PyString(str_value);
    return s;
}

PyList<PyObject*>* BinaryFileParser::get_consts() {
    int type = file_stream->read();
    if (type == TYPE_TUPLE) {
        return get_tuple(false);
    } else if (type == TYPE_SMALL_TUPLE) {
        return get_tuple(true);
    }

    file_stream->unread();
    return NULL;
}

PyList<PyObject*>* BinaryFileParser::get_tuple(bool is_small) {
    int length;
    if (is_small) {
        length = file_stream->read();
    } else {
        length = file_stream->read_int();
    }

    PyString* str;
    PyList<PyObject*>* list = new PyList<PyObject*>();
    for (int i = 0; i < length; i++) {
        char code = file_stream->read();
        char obj_type = code & ~FLAG_REF;
        switch (obj_type) {

        case TYPE_CODE:
            std::cout << "got a code object" << std::endl;
            list->add(get_code_object());
            break;

        case TYPE_INT:
            list->add(new PyInteger(file_stream->read_int()));
            break;

        case TYPE_NONE:
            list->add(Universe::Py_None);
            break;

        case TYPE_INTERNED:
            str = get_string();
            list->add(str);
            _string_table.add(str);
            break;

        case TYPE_STRING:
            list->add(get_string(false));
            break;

        case TYPE_SHORT_ASCII_INTERNED:
            str = get_string(true);
            list->add(str);
            _string_table.add(str);
            break;

        case TYPE_REF:
            list->add(_string_table.get(file_stream->read_int()));
            break;

        default:
            printf("Not inplemented: %d\n", obj_type);
            exit(-1);

        }
    }

    return list;
}

PyString* BinaryFileParser::get_string(bool is_short) {
    int length;
    string s;
    if (is_short) {
        length = file_stream->read();
    } else {
        length = file_stream->read_int();
    }
    for (int i = 0; i < length; i++) {
        s.push_back(file_stream->read());
    }
    return new PyString(s);
}

PyList<PyObject*>* BinaryFileParser::get_names() {
    int type = file_stream->read();
    if (type == TYPE_TUPLE) {
        return get_tuple(false);
    } else if (type == TYPE_SMALL_TUPLE) {
        return get_tuple(true);
    }

    file_stream->unread();
    return NULL;
    
}

PyList<PyObject*>* BinaryFileParser::get_varnames() {
    int type = file_stream->read();
    if (type == TYPE_TUPLE) {
        return get_tuple(false);
    } else if (type == TYPE_SMALL_TUPLE) {
        return get_tuple(true);
    }

    file_stream->unread();
    return NULL;
}

PyList<PyObject*>* BinaryFileParser::get_freevars() {
    int type = file_stream->read();
    if (type == TYPE_TUPLE) {
        return get_tuple(false);
    } else if (type == TYPE_SMALL_TUPLE) {
        return get_tuple(true);
    }

    file_stream->unread();
    return NULL;
}

PyList<PyObject*>* BinaryFileParser::get_cellvars() {
    int type = file_stream->read();
    if (type == TYPE_TUPLE) {
        return get_tuple(false);
    } else if (type == TYPE_SMALL_TUPLE) {
        return get_tuple(true);
    }

    file_stream->unread();
    return NULL;
}

PyString* BinaryFileParser::get_filename() {
    return get_name();
}

PyString* BinaryFileParser::get_name() {
    char ch = file_stream->read();

    if (ch == TYPE_STRING) {
        return get_string(false);
    } else if (ch == TYPE_INTERNED) {
        PyString* str = get_string(false);
        _string_table.add(str);
        return str;
    } else if (ch == TYPE_REF) {
        return _string_table.get(file_stream->read_int());
    }

    return NULL;
}

PyString* BinaryFileParser::get_lnotab() {
    char ch = file_stream->read();

    if (ch != TYPE_STRING && ch != TYPE_INTERNED) {
        file_stream->unread();
        return NULL;
    }
    
    return get_string(true);
}