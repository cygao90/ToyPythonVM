#include "Interpreter.h"
#include "opcode.h"
#include "PyInteger.h"
#include "PyObject.h"
#include <iostream>

using std::cout;

#define PUSH(x)  _stack->add((x))
#define POP()    _stack->pop()

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
        PyObject* v, *w, *u, *attr; // tmp vars

        switch (op_code) {
        case LOAD_CONST: {
            PUSH(_consts->get(op_arg));
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

        case COMPARE_OP:
            cout << "compare op\n";
            w = POP(); // right
            v = POP(); // left
            
            switch (op_arg) {
            case cmp_op::PyCmp_LT:
                cout << "lt\n";
                PUSH(v->lt(w));
                break;

            case cmp_op::PyCmp_LE:
                cout << "le\n";
                PUSH(v->le(w));
                break;

            case cmp_op::PyCmp_EQ:
                cout << "eq\n";
                PUSH(v->eq(w));
                break;

            case cmp_op::PyCmp_NE:
                cout << "ne\n";
                PUSH(v->ne(w));
                break;

            case cmp_op::PyCmp_GT:
                cout << "gt\n";
                PUSH(v->gt(w));
                break;

            case cmp_op::PyCmp_GE:
                cout << "ge\n";
                PUSH(v->ge(w));
                break;
            }
            break;
        
        case POP_JUMP_IF_FALSE:
            cout << "jump if false" << op_arg << "\n";
            v = POP();
            if (((PyInteger*)v)->value() == 0) {
                pc += op_arg;
            }
            break;

        case JUMP_FORWARD:
            cout << "jump forward\n";
            pc += op_arg;
            break;

        default:
            cout << "Not implemented\n";
            exit(-1);
        }
    }
};