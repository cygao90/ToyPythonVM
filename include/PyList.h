#ifndef LIST_H
#define LIST_H

#include "PyObject.h"
#include <vector>

using std::vector;

template<typename T>
class PyList : public PyObject {
private:
    vector<T> _array;
public:
    void add(T t);
    void insert(int index, T t);
    T    get(int index);
    void set(int index, T t);
    int  size();
    int  length();
    T    pop();
};

template<typename T>
void PyList<T>::add(T t) {
    _array.push_back(t);
}

template<typename T>
void PyList<T>::insert(int index, T t) {
    _array.insert(_array.begin() + index, t);
}

template<typename T>
T PyList<T>::get(int index) {
    return _array.at(index);
}

template<typename T>
void PyList<T>::set(int index, T t) {
    while (index >= size()) {
       add(NULL); 
    }
    _array.at(index) = t;
}

template<typename T>
int PyList<T>::size() {
    return _array.size();
}

template<typename T>
int PyList<T>::length() {
    return _array.capacity();
}

template<typename T>
T PyList<T>::pop() {
    T t = _array.back();
    _array.pop_back();
    return t;
}

#endif