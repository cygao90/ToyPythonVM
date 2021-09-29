#ifndef PY_INTEGER_H
#define PY_INTEGER_H

#include "PyObject.h"
#include "Klass.h"

class IntegerKlass : public Klass {
private:
    IntegerKlass();
    static IntegerKlass* _instance;

public:
    static IntegerKlass* get_instance();
    void initialize();

    virtual PyObject* add(PyObject* x, PyObject* y);    
    virtual PyObject* sub(PyObject* x, PyObject* y);    
    virtual PyObject* mul(PyObject* x, PyObject* y);    
    virtual PyObject* div(PyObject* x, PyObject* y);    
    virtual PyObject* mod(PyObject* x, PyObject* y);    

    virtual PyObject* lt(PyObject* x, PyObject* y);     
    virtual PyObject* le(PyObject* x, PyObject* y);     
    virtual PyObject* eq(PyObject* x, PyObject* y);     
    virtual PyObject* ne(PyObject* x, PyObject* y);     
    virtual PyObject* gt(PyObject* x, PyObject* y);     
    virtual PyObject* ge(PyObject* x, PyObject* y);     

    virtual PyObject* print(PyObject* x);
};

class PyInteger : public PyObject {
private:
    int _value;

public:

    void print() { std::cout << _value << "\n"; }

    PyInteger(int value); 
    int value() { return _value; }
    
};

#endif