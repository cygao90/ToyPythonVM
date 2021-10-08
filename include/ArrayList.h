#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <vector>

using std::vector;

template<typename T>
class ArrayList {
private:
    vector<T> _array;
public:
    void add(T t);
    void insert(int index, T t);
    T&   get(int index);
    void set(int index, T t);
    int  size();
    T    pop();
    T&   top();
};

template<typename T>
void ArrayList<T>::add(T t) {
    _array.push_back(t);
}

template<typename T>
void ArrayList<T>::insert(int index, T t) {
    _array.insert(_array.begin() + index, t);
}

template<typename T>
T& ArrayList<T>::get(int index) {
    return _array.at(index);
}

template<typename T>
void ArrayList<T>::set(int index, T t) {
    while (index >= size()) {
       add(NULL); 
    }
    _array.at(index) = t;
}

template<typename T>
int ArrayList<T>::size() {
    return _array.size();
}

template<typename T>
T ArrayList<T>::pop() {
    T t = _array.back();
    _array.pop_back();
    return t;
}

template<typename T>
T& ArrayList<T>::top() {
    assert(size() > 0);
    return _array.back();
}

#endif