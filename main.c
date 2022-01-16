#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "png.h"

#define RED_FLAG_PATH       "../utils/red_flag.png" // 512x512 png: https://www.cleanpng.com/png-ios-mit-license-screenshot-cocoapods-digital-marke-266994/download-png.html



int main(int argc, char** argv) {
    FILE* png = fopen(RED_FLAG_PATH, "rb");
    if (png == NULL) {
        fprintf(stderr, "ERROR: Could not open file because: %s\n", strerror(errno));
        exit(1);
    } else {
        printf("Opened PNG file at: %s\n", RED_FLAG_PATH);
    }
    
    // Read the PNG signature
    uint8_t read_bytes[8];
    read_png_bytes(png, read_bytes, sizeof(read_bytes));

    // Every PNG starts with 137 80 78 71 13 10 26 10
    for (size_t i = 0; i < sizeof(read_bytes); i++) {
            printf("%u ", read_bytes[i]);
    }
    printf("\n");

    // Look at the IHDR chunk
    PNGChunk ihdr; 
    read_png_chunk(png, &ihdr);
    expose_png_chunk(ihdr);

    PNGChunk sbit;
    read_png_chunk(png, &sbit);
    expose_png_chunk(sbit);

    printf("%d\n", matching_chunk_type(ihdr.type, sizeof(ihdr.type), IHDR));
    
    /*
    uint8_t IHDR[4] = {73, 72, 68, 82};
    uint8_t PLTE[4] = {80, 76, 84, 69};
    uint8_t sBIT[4] = {115, 66, 73, 84};
    uint8_t pHYs[4] = {112, 72, 89, 115};
    uint8_t tEXt[4] = {116, 69, 88, 116};
    uint8_t IDAT[4] = {73, 68, 65, 84};
    uint8_t IEND[4] = {73, 69, 78, 68};

    printf("IHDR: %i\n", u8tod(IHDR, 4));
    printf("PLTE: %i\n", u8tod(PLTE, 4));
    printf("sBIT: %i\n", u8tod(sBIT, 4));
    printf("pHYs: %i\n", u8tod(pHYs, 4));
    printf("tEXt: %i\n", u8tod(tEXt, 4));
    printf("IDAT: %i\n", u8tod(IDAT, 4));
    printf("IEND: %i\n", u8tod(IEND, 4));

    for (int i = 0; i < 6; i++) {
        PNGChunk chunk;
        read_png_chunk(png, &chunk);
        expose_png_chunk(chunk);
        free(chunk.data);
    }
    */

    free(ihdr.data);
    free(sbit.data);
    fclose(png);
    return 0;
}