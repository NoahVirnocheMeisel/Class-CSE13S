#include "io.h"

#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

//I was told in tutoring section that I should change the variable name to buffer_i_hardly_know_er to mess with Ben. Please do not hurt me I am sorry if I hurt you :).
//buffer structure(I hardly know-er....)
struct buffer { //Buffer? I hardly know-er!!
    int fd; //file descriptor from open() or create()
    int offset; //offset into buffer a[]

    int num_remaining; //number of bytes reamining in buffer (reading)
    uint8_t a[BUFFER_SIZE]; //Buffer? I hardly know-er!!
};

//opens up a buffer to read a file into.
Buffer *read_open(const char *filename) { //Buffer? I hardly know-er!!
    uint8_t open_return = open(filename, O_RDONLY);
    if (open_return >= 0) {
        Buffer *file_buffer_i_hardly_know_er
            = calloc(1, sizeof(Buffer)); //Buffer? I hardly know-er!!
        file_buffer_i_hardly_know_er->fd = open_return;
        file_buffer_i_hardly_know_er->offset = 0;
        file_buffer_i_hardly_know_er->num_remaining = 0;
        for (uint32_t i = 0; i < BUFFER_SIZE; i++) { //Buffer? I hardly know-er!!
            file_buffer_i_hardly_know_er->a[i] = 0;
        }
        return file_buffer_i_hardly_know_er;
    }
    return NULL;
}
//closes the read_buffer
void read_close(Buffer **pointer_buffer_i_hardly_know_er) { //Buffer? I hardly know-er!!
    if (pointer_buffer_i_hardly_know_er != NULL && *pointer_buffer_i_hardly_know_er != NULL) {
        close((*pointer_buffer_i_hardly_know_er)->fd);
        free(*pointer_buffer_i_hardly_know_er);
    }
    if (pointer_buffer_i_hardly_know_er != NULL) {
        *pointer_buffer_i_hardly_know_er = NULL;
    }
}
//opens up a buffer to write_files from
Buffer *write_open(const char *filename) { //Buffer? I hardly know-er!!
    uint32_t open_return = creat(filename, 0664);
    if (open_return >= 0) {
        Buffer *file_buffer_i_hardly_know_er
            = calloc(1, sizeof(Buffer)); //Buffer? I hardly know-er!!
        file_buffer_i_hardly_know_er->fd = open_return;
        file_buffer_i_hardly_know_er->offset = 0;
        file_buffer_i_hardly_know_er->num_remaining = 0;
        for (uint32_t i = 0; i < BUFFER_SIZE; i++) { //Buffer? I hardly know-er!!
            file_buffer_i_hardly_know_er->a[i] = 0;
        }
        return file_buffer_i_hardly_know_er;

    } else {
        return NULL;
    }
}
//closes the write_buffer
void write_close(Buffer **pointer_buffer_i_hardly_know_er) { //Buffer? I hardly know-er!!
    uint8_t *start = (*pointer_buffer_i_hardly_know_er)->a;
    int num_bytes = (*pointer_buffer_i_hardly_know_er)->offset;

    do {
        ssize_t rc = write((*pointer_buffer_i_hardly_know_er)->fd, start, num_bytes);
        if (rc < 0) {
            printf("Failed to close file. Exiting\n");
            exit(-1);
        }
        start += rc;
        num_bytes -= rc;

    } while (num_bytes > 0);

    (*pointer_buffer_i_hardly_know_er)->offset = 0;
    close((*pointer_buffer_i_hardly_know_er)->fd);
    free(*pointer_buffer_i_hardly_know_er);
    *pointer_buffer_i_hardly_know_er = NULL;
}
//reads one byte into the buffer file
bool read_uint8(Buffer *buffer_i_hardly_know_er, uint8_t *x) { //Buffer? I hardly know-er!!
    if (buffer_i_hardly_know_er->num_remaining == 0) {

        ssize_t rc = read(buffer_i_hardly_know_er->fd, buffer_i_hardly_know_er->a,
            sizeof(buffer_i_hardly_know_er->a));
        if (rc < 0) {
            fprintf(stderr, "Invalid Read: Try again with a valid file\n");
            read_close(&buffer_i_hardly_know_er);
            exit(-1);
        }
        if (rc == 0) {
            return false;
        }
        buffer_i_hardly_know_er->num_remaining = rc;
        buffer_i_hardly_know_er->offset = 0;
    }
    *x = buffer_i_hardly_know_er->a[buffer_i_hardly_know_er->offset];
    buffer_i_hardly_know_er->offset++;
    buffer_i_hardly_know_er->num_remaining--;
    return true;
}
//reads two bytes into the buffer file
bool read_uint16(Buffer *buffer_i_hardly_know_er, uint16_t *x) { //Buffer? I hardly know-er!!
    uint8_t first, second;
    uint16_t temp_short;
    if (read_uint8(buffer_i_hardly_know_er, &first) == false) {
        return false;
    }
    if (read_uint8(buffer_i_hardly_know_er, &second) == false) {
        return false;
    }
    temp_short = second;
    temp_short = temp_short << 8;
    temp_short = temp_short | first;
    *x = temp_short;
    return true;
}
//reads four bytes into the buffer file
bool read_uint32(Buffer *buffer_i_hardly_know_er, uint32_t *x) { //Buffer? I hardly know-er!!
    uint16_t first, second;
    uint32_t temp_word;
    if (read_uint16(buffer_i_hardly_know_er, &first) == false
        || read_uint16(buffer_i_hardly_know_er, &second) == false) {
        return false;
    }
    temp_word = second;
    temp_word = temp_word << 16;
    temp_word = temp_word | first;
    *x = temp_word;
    return true;
}
//writes one byte into a buffer
void write_uint8(Buffer *buffer_i_hardly_know_er, uint8_t x) {
    if (buffer_i_hardly_know_er->offset >= BUFFER_SIZE) {
        uint8_t *start = buffer_i_hardly_know_er->a;
        int num_bytes = buffer_i_hardly_know_er->offset;

        do {
            ssize_t rc = write(buffer_i_hardly_know_er->fd, start, num_bytes);
            if (rc < 0) {
                fprintf(stderr, "Invalid Write: Try again with a valid filei\n");
                write_close(&buffer_i_hardly_know_er);
                exit(-1);
            }
            start += rc;
            num_bytes -= rc;

        } while (num_bytes > 0);
        buffer_i_hardly_know_er->offset = 0;
    }
    buffer_i_hardly_know_er->a[buffer_i_hardly_know_er->offset] = x;
    buffer_i_hardly_know_er->offset++;
}
//writes two bytes into a buffer
void write_uint16(Buffer *buffer_i_hardly_know_er, uint16_t x) {
    write_uint8(buffer_i_hardly_know_er, x);
    write_uint8(buffer_i_hardly_know_er, x >> 8);
}
//writes four bytes into a buffer
void write_uint32(Buffer *buffer_i_hardly_know_er, uint32_t x) {
    write_uint16(buffer_i_hardly_know_er, x);
    write_uint16(buffer_i_hardly_know_er, x >> 16);
}
