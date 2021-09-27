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

void Interpreter::run(CodeObject* codes) {
    _frame = new FrameObject(codes);
    eval_frame();
    destroy_frame();
}

void Interpreter::destroy_frame() {
    FrameObject* temp = _frame;
    _frame = _frame->sender();
    delete temp;
}

void Interpreter::leave_frame() {
    destroy_frame();
    PUSH(_ret_value);
}

void Interpreter::eval_frame() {

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
            build_frame(POP());
            cout << "Call function \n";
            break;

        case POP_TOP:
            POP();
            cout << "pop top \n";
            break;

        case RETURN_VALUE:
            _ret_value = POP();
            if (_frame->is_first_frame()) {
                return;
            }
            leave_frame();
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
            v = POP(); // name
            w = POP(); // code_obj
            fo = new FunctionObject(w);
            PUSH(fo);
            break;

        case STORE_FAST:
            v = POP();
            _frame->_fast_locals->set(op_arg, v);
            break;

        case LOAD_FAST:
            PUSH(_frame->_fast_locals->get(op_arg));
            break;

        default:
            cerr << "Not implemented\n";
            exit(-1);
        }
    }
};

void Interpreter::build_frame(PyObject* callable) {
    FrameObject* frame = new FrameObject((FunctionObject*)callable);
    frame->set_sender(_frame);
    _frame = frame;
}