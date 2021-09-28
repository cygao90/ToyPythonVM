#include "Interpreter.h"
#include "BufferInputStream.h"
#include "BinaryFileParser.h"
#include "Universe.h"
#include <iostream>


using namespace std;

int main(int argc, char** argv) {
    Universe::genesis();
    BufferInputStream* file_stream = new BufferInputStream(argv[1]);
    BinaryFileParser parser(file_stream);
    CodeObject* code = parser.parse();
    Interpreter interpreter;
    interpreter.run(code);
}