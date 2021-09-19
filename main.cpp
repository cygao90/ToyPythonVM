#include "BufferInputStream.h"
#include "List.h"
#include <iostream>

using namespace std;

int main() {
    List<int> l;
    l.add(1);
    l.add(2);
    cout << l.get(0) << endl;
    cout << l.size() << endl;
    cout << l.length() << endl;
    l.set(0, 100);
    cout << l.get(0) << endl;
    l.insert(0, 200);
    cout << l.get(0) << endl;
}