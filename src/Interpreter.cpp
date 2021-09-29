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
    _builtins = new Map<string, PyObject*>();
    _builtins->insert("len", new FunctionObject(len));
    _builtins->insert("print", new FunctionObject(print));
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
        PyList<PyObject*>* args = NULL;

        switch (op_code) {
        case LOAD_CONST:
            PUSH(_frame->consts()->get(op_arg));
            break;

        case LOAD_NAME:
            v = _frame->names()->get(op_arg);
            w = _frame->locals()->get(v);
            if (w != Universe::Py_None) {
                PUSH(w);
                break;
            }

            w = _builtins->get(((PyString*)v)->value());
            if (w != Universe::Py_None) {
                PUSH(w);
                break;
            }
            cerr << "no locals when loading name\n";
            PUSH(w);
            break;

        case STORE_NAME:
            v = _frame->names()->get(op_arg);
            _frame->locals()->insert(v, POP());
            break;

        case CALL_FUNCTION:
            if (op_arg > 0) {
                args = new PyList<PyObject*>();
                while (op_arg--) {
                    args->set(op_arg, POP());
                }
            }
            build_frame(POP(), args);
            if (args) {
                delete args;
                args = NULL;
            }
            break;

        case POP_TOP:
            POP();
            break;

        case RETURN_VALUE:
            _ret_value = POP();
            if (_frame->is_first_frame()) {
                return;
            }
            leave_frame();
            break;

        case COMPARE_OP:
            w = POP(); // right
            v = POP(); // left
            
            switch (op_arg) {
            case cmp_op::PyCmp_LT:
                PUSH(v->lt(w));
                break;

            case cmp_op::PyCmp_LE:
                PUSH(v->le(w));
                break;

            case cmp_op::PyCmp_EQ:
                PUSH(v->eq(w));
                break;

            case cmp_op::PyCmp_NE:
                PUSH(v->ne(w));
                break;

            case cmp_op::PyCmp_GT:
                PUSH(v->gt(w));
                break;

            case cmp_op::PyCmp_GE:
                PUSH(v->ge(w));
                break;
            }
            break;
        
        case POP_JUMP_IF_FALSE:
            v = POP();
            if (v == Universe::Py_False) {
                _frame->set_pc(op_arg);
            }
            break;

        case JUMP_FORWARD:
            _frame->set_pc(_frame->get_pc() + op_arg);
            break;

        case JUMP_ABSOLUTE:
            _frame->set_pc(op_arg);
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
            fo->set_globals(_frame->globals());
            
            if (op_arg & 0x01) {
                fo->set_defaults((PyList<PyObject*>*)POP());
            }

            PUSH(fo);
            break;

        case STORE_FAST:
            v = POP();
            _frame->_fast_locals->set(op_arg, v);
            break;

        case LOAD_FAST:
            PUSH(_frame->_fast_locals->get(op_arg));
            break;

        case STORE_GLOBAL:
            v = _frame->names()->get(op_arg);
            _frame->globals()->insert(v, POP());
            break;

        case LOAD_GLOBAL:
            v = _frame->names()->get(op_arg);
            w = _frame->globals()->get(v);
            
            if (w != Universe::Py_None) {
                PUSH(w);
                break;
            }

            w = _builtins->get(((PyString*)v)->value());
            if (w != Universe::Py_None) {
                PUSH(w);
                break;
            }

            assert(0 && "global variable not found.");
            break;

        default:
            cerr << "Not implemented\n";
            exit(-1);
        }
    }
};

void Interpreter::build_frame(PyObject* callable, PyList<PyObject*>* args) {
    if (callable->klass() == NativeFunctionKlass::get_instance()) {
        PUSH(((FunctionObject*)callable)->call(args));
    } else {
        FrameObject* frame = new FrameObject((FunctionObject*)callable, args);
        frame->set_sender(_frame);
        _frame = frame;
    }
}