#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "png.h"

int u8tod(uint8_t* buff, size_t size) {
    int result = 0;
    for (size_t i = 0; i < size; i++) {
        result += pow(256, size - i - 1) * buff[i];
    }

    return result;
}

void read_png_bytes(FILE* f, uint8_t* buff, size_t size) {
    size_t read = fread(buff, 1, size, f);
    if (read != size) {
        if (ferror(f)) {
            fprintf(stderr, "ERROR: Could not read PNG header: %s\n", strerror(errno));
        } else if (feof(f)) {
            fprintf(stderr, "ERROR: Reached EOF before expected\n");
        }
        exit(1);
    }
}

void read_png_chunk(FILE* f, PNGChunk* buff) {
    read_png_bytes(f, buff->length, sizeof(buff->length));
    read_png_bytes(f, buff->type, sizeof(buff->type));

    // setup dynamic memory for data    
    buff->_len = u8tod(buff->length, sizeof(buff->length));
    buff->data = malloc(sizeof(uint8_t) * buff->_len);
    read_png_bytes(f, buff->data, buff->_len);
    read_png_bytes(f, buff->crc, sizeof(buff->crc));
}