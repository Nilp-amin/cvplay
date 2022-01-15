#ifndef __PNG_H__
#define __PNG_H__

typedef struct {
    uint8_t length[4];
    uint8_t type[4];
    uint8_t* data;
    uint8_t crc[4];
    int _len;
} PNGChunk;

void read_png_bytes(FILE* f, uint8_t* buff, size_t size);
void read_png_chunk(FILE* f, PNGChunk* buff);

int u8tod(uint8_t* buff, size_t size);

#endif