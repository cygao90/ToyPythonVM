#include "Interpreter.h"
#include "opcode.h"
#include "PyInteger.h"
#include "PyObject.h"
#include <iostream>

using std::cout;

void Interpreter::run(CodeObject* codes) {
    int pc = 0;
    int code_length = codes->co_code->length();

    _stack = new PyList<PyObject*>();
    _consts = codes->co_consts;

    while (pc < code_length) {
        u_char op_code = codes->co_code->value()[pc++];
        bool has_argument = HAS_ARG(op_code);

        u_char op_arg = -1;
        if (has_argument) {
            op_arg = codes->co_code->value()[pc++];
        } else {
            pc++;
        }

        PyInteger* lhs, *rhs;
        PyObject* v, *w, *u, *attr;        

        switch (op_code) {
        case LOAD_CONST: {
            _stack->add(_consts->get(op_arg));
            cout << "LOAD_CONST " << _consts->get(op_arg) << "\n"; 
            break;
        }

        case LOAD_NAME: {
            PyObject* name = codes->co_names->get(op_arg);
            cout << "LOAD_NAME " << ((PyString*)name)->value() << "\n";
            break;
        }

        case CALL_FUNCTION:
            cout << "Call function\n";
            break;

        case POP_TOP:
            cout << "pop top\n";
            break;

        case RETURN_VALUE:
            cout << "return value\n";
            break;
        
        default:
            cout << "Not implemented\n";
            exit(-1);
        }
    }
};