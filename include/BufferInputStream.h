#ifndef BUFFER_INPUT_STREAM_H
#define BUFFER_INPUT_STREAM_H

#include <stdio.h>

#define BUFFER_LEN 256

class BufferInputStream {
private:
    FILE* fp;
    char buffer[BUFFER_LEN];
    unsigned int index;

public:
    BufferInputStream(char const* filename) {
        fp = fopen(filename, "rb");
        assert(fp != NULL);
        fread(buffer, BUFFER_LEN * sizeof(char), 1, fp);
        index = 0;
    }
    
    ~BufferInputStream() {
        close();
    }

    char read() {
        if (index < BUFFER_LEN) {
            return buffer[index++];
        } else {
            index = 0;
            fread(buffer, BUFFER_LEN * sizeof(char), 1, fp);
            return buffer[index++];
        }
    }

    int read_int() {
        int b1 = read() & 0xFF;
        int b2 = read() & 0xFF;
        int b3 = read() & 0xFF;
        int b4 = read() & 0xFF;
        return b1 | b2 << 8 | b3 << 16 | b4 << 24;
    }

    void unread() {
        index--;
    }

    void close() {
        if (fp == NULL) {
            fclose(fp);
            fp = NULL;
        }
    }

};

#endif