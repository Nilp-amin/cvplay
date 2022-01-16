#include "png.h"

int u8tod(uint8_t* buff, size_t size) {
    int result = 0;
    for (size_t i = 0; i < size; i++) {
        result += pow(256, size - i - 1) * buff[i];
    }

    return result;
}

bool matching_chunk_type(uint8_t* type, size_t size, PNGChunkType guess) {
    assert(size == 4);
    if (u8tod(type, size) == (int)guess) {
        return true;
    }
    return false;
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

void expose_png_chunk(PNGChunk chunk) {
    printf("Length: ");
    for (size_t i = 0; i < sizeof(chunk.length); i++) {
        printf("%u ", chunk.length[i]);
    }

    printf("\n");
    printf("Type: ");
    for (size_t i = 0; i < sizeof(chunk.type); i++) {
        printf("%u ", chunk.type[i]);
    }
    char type[5];
    memcpy(type, chunk.type, sizeof(chunk.type));
    type[4] = '\0';
    printf("(%s)", type);

    printf("\n");
    printf("Data: ");
    for (size_t i = 0; i < chunk._len; i++) {
        printf("%u ", chunk.data[i]);
    }
    
    printf("\n");
    printf("CRC: ");
    for (size_t i = 0; i < sizeof(chunk.crc); i++) {
        printf("%u ", chunk.crc[i]);
    }
    printf("\n");
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