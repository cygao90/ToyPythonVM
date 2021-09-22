#ifndef MAP_H
#define MAP_H

#include <unordered_map>
#include "Universe.h"

template<typename K, typename V>
class Map {
private:
    std::unordered_map<K, V> _map;
public:
    int  size() { return _map.size(); }
    void insert(K k, V v);
    V&   get(K k);
    bool has_key(K k);
    void remove(K k);
};

template<typename K, typename V>
void Map<K, V>::insert(K k, V v) {
    if (has_key(k)) {
        _map.at(k) = v;
    } else {
        _map.insert(std::make_pair(k, v));
    }
}

template<typename K, typename V>
V& Map<K, V>::get(K k) {
    if (has_key(k)) {
        return _map.at(k);
    }
    return Universe::Py_None;
}

template<typename K, typename V>
bool Map<K, V>::has_key(K k) {
    return _map.find(k) != _map.end();
}

template<typename K, typename V>
void Map<K, V>::remove(K k) {
    _map.erase(k);
}

#endif