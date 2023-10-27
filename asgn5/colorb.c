#include <stdio.h>
#include <stdlib.h>
#define OPTIONS "i:o:h"
#include "bmp.h"
#include "io.h"

#include <assert.h>
#include <stdbool.h>
#include <unistd.h>
//main command-line interface. switch statment to check for specific command-line options.
int main(int argc, char **argv) {
    int opt = 0;
    bool i, o, h;
    i = false;
    o = false;
    h = false;
    char *in_file = NULL;
    char *out_file = NULL;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            i = true;
            in_file = optarg;
            break;
        case 'o':
            o = true;
            out_file = optarg;
            break;
        case 'h':
            h = true;
            printf("-i filename: Reads in the specified bmp file\n-o filename: Writes to the "
                   "specified file\n -h: Prints this message\n");
            break;
        }
    }
    if (i == false && o == false && h == false) {
        printf("-i filename: Reads in the specified bmp file\n-o filename: Writes to the specified "
               "file\n -h: Prints this message\n");
    }
    //checks if either file is null, then creates a buffer file to read the input file to, creates a bmp structure using that buffer, closes the buffer, reduces the bmp pallette, writes another buffer file to write to, writes the new bmp to that buffer before closing the buffer and storing it's contents in the outfile.
    if (in_file != NULL && out_file != NULL) {
        Buffer *read_buffer = read_open(in_file);
        BMP *input_image = bmp_create(read_buffer);
        read_close(&read_buffer);
        bmp_reduce_palette(input_image);
        Buffer *write_buffer = write_open(out_file);
        bmp_write(input_image, write_buffer);
        bmp_free(&input_image);
        write_close(&write_buffer);
    }
}
