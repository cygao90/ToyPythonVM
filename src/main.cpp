#include "BufferInputStream.h"
#include <iostream>

using namespace std;

int main() {
    BufferInputStream s("/home/wctpd/Desktop/ToyPythonVM/__pycache__/test.cpython-38.pyc");
    cout << "The magic number is:" << hex << s.read_magic() << endl;
}