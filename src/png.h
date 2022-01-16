#ifndef __PNG_H__
#define __PNG_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

typedef enum {
    // enum values are given by u8tod()
    IHDR = 1229472850,
    PLTE = 1347179589,
    sBIT = 1933723988,
    pHYs = 1883789683,
    tEXt = 1950701684,
    IDAT = 1229209940,
    IEND = 1229278788
} PNGChunkType;

typedef struct {
    uint8_t length[4];
    uint8_t type[4];
    uint8_t* data;
    uint8_t crc[4];
    int _len;
    PNGChunkType _type;
} PNGChunk;

void read_png_bytes(FILE* f, uint8_t* buff, size_t size);
void read_png_chunk(FILE* f, PNGChunk* buff);
void expose_png_chunk(PNGChunk chunk);

int u8tod(uint8_t* buff, size_t size);
bool matching_chunk_type(uint8_t* type, size_t size, PNGChunkType guess);

#endif