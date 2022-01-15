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

    // Look at the IHDR chunk
    PNGChunk ihdr; 
    read_png_chunk(png, &ihdr);

    printf("\n");
    printf("Length: ");
    for (size_t i = 0; i < sizeof(ihdr.length); i++) {
        printf("%u ", ihdr.length[i]);
    }

    printf("\n");
    printf("Type: ");
    for (size_t i = 0; i < sizeof(ihdr.type); i++) {
        printf("%u ", ihdr.type[i]);
    }

    printf("\n");
    printf("Data: ");
    for (size_t i = 0; i < ihdr._len; i++) {
        printf("%u ", ihdr.data[i]);
    }
    
    printf("\n");
    printf("CRC: ");
    for (size_t i = 0; i < sizeof(ihdr.crc); i++) {
        printf("%u ", ihdr.crc[i]);
    }


    free(ihdr.data);

    fclose(png);
    return 0;
}