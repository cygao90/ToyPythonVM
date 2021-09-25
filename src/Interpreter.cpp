#include "Interpreter.h"
#include "opcode.h"
#include "PyInteger.h"
#include "PyObject.h"
#include "FunctionObject.h"
#include "Universe.h"
#include <iostream>

using std::cout;
using std::cerr;

#define PUSH(x)  _frame->stack()->add((x))
#define POP()    _frame->stack()->pop()

Interpreter::Interpreter() {

}

void Interpreter::run(CodeObject* _codes) {

    _frame = new FrameObject(_codes);

    while (_frame->has_more_codes()) {
        unsigned char op_code = _frame->get_op_code();
        unsigned char op_arg  = _frame->get_op_arg();

        PyInteger* lhs, *rhs;
        PyObject* v, *w, *u, *attr; // tmp vars
        FunctionObject* fo;

        switch (op_code) {
        case LOAD_CONST:
            PUSH(_frame->consts()->get(op_arg));
            cout << "LOAD_CONST ";
            _frame->consts()->get(op_arg)->print(); 
            break;

        case LOAD_NAME:
            v = _frame->names()->get(op_arg);
            w = _frame->locals()->get(v);
            if (w == Universe::Py_None) {
                cerr << "no locals when loading name\n";
            }
            PUSH(w);
            cout << "LOAD_NAME ";
            v->print();
            break;

        case STORE_NAME:
            v = _frame->names()->get(op_arg);
            _frame->locals()->insert(v, POP());
            cout << "STORE_NAME ";
            v->print();
            break;

        case CALL_FUNCTION:
            cout << "Call function \n";
            break;

        case POP_TOP:
            cout << "pop top \n";
            break;

        case RETURN_VALUE:
            cout << "return value \n";
            break;

        case COMPARE_OP:
            cout << "compare op ";
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
            if (v == Universe::Py_False) {
                _frame->set_pc(op_arg);
            }
            break;

        case JUMP_FORWARD:
            cout << "jump forward\n";
            _frame->set_pc(_frame->get_pc() + op_arg);
            break;

        case JUMP_ABSOLUTE:
            _frame->set_pc(op_arg);
            cout << "jump absolute\n\n";
            break;

        case BINARY_ADD:
            v = POP();
            w = POP();
            PUSH(v->add(w));
            break;

        case MAKE_FUNCTION:
            v = POP();
            fo = new FunctionObject(v);
            PUSH(fo);
            break;

        default:
            cerr << "Not implemented\n";
            exit(-1);
        }
    }
};