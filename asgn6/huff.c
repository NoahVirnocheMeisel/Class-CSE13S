#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "i:o:h"

typedef struct Code Code;

struct Code {
    uint64_t code;
    uint8_t code_length;
};

uint64_t fill_histogram(Buffer *inbuf, double *histogram);

Node *create_tree(double *histogram, uint16_t *num_leaves);

void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length);

void huff_compress_file(BitWriter *outbuf, Buffer *inbuf, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table);

void huff_write_tree(BitWriter *outbuf, Node *code_tree);

int main(int argc, char **argv) {
    int opt = 0;
    bool i = false;
    bool o = false;
    bool h = false;
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
            printf("-i filename: sets input file to specified filename\n-o filename: sets output "
                   "file to specified filename\n-h: Prints this very helpful message\n");
            break;
        }
    }

    if ((i == false) && (o == false) && (h == false)) {
        printf("-i filename: sets input file to specified filename\n-o filename: sets output file "
               "to specified filename\n-h: Prints this very helpful message\n");
    } else if (in_file != NULL && out_file != NULL) {
        //open first readbuffer
        Buffer *inbuf = read_open(in_file);
        double histogram[256];
        //fill histogram
        uint32_t filesize = fill_histogram(inbuf, histogram);
        void code_tree_free(Node * *node);
        uint16_t num_leaves = 0;
        //create a tree from the histogram
        Node *huff_tree = create_tree(histogram, &num_leaves);
        Code code_table[256];
        uint64_t code = 0;
        uint8_t code_length = 0;
        //creates a BitWriter buffer
        BitWriter *outbuf = bit_write_open(out_file);
        read_close(&inbuf);
        inbuf = read_open(in_file);
        //closes the old input buffer and opens new one, checks if tree has values then fills code table and runs compression
        if (huff_tree != NULL) {
            fill_code_table(code_table, huff_tree, code, code_length);
            huff_compress_file(outbuf, inbuf, filesize, num_leaves, huff_tree, code_table);
        }
        //frees all memory still in use
        read_close(&inbuf);
        bit_write_close(&outbuf);
        code_tree_free(&huff_tree);
    } else {
        printf("-i filename: sets input file to specified filename\n-o filename: sets output file "
               "to specified filename\n-h: Prints this very helpful message\n");
    }
}

uint64_t fill_histogram(Buffer *inbuf, double *histogram) {
    uint32_t filesize = 0;
    for (uint16_t i = 0; i <= 255; i++) {
        histogram[i] = 0;
    }
    ++histogram[0x00];
    ++histogram[0xff];
    uint8_t byte = 0;
    while (read_uint8(inbuf, &byte) != 0) {
        ++(histogram[byte]);
        filesize++;
    }
    return filesize;
}

Node *create_tree(double *histogram, uint16_t *num_leaves) {
    PriorityQueue *q = pq_create();
    Node *n = NULL;
    Node *left = NULL;
    Node *right = NULL;
    for (uint16_t i = 0; i <= 255; i++) {
        if (histogram[i] > 0) {
            n = node_create(i, histogram[i]);
            enqueue(q, n);
            (*num_leaves)++;
        }
    }
    while (!(pq_size_is_1(q) || pq_is_empty(q))) {
        dequeue(q, &left);
        dequeue(q, &right);
        n = node_create(0, (left->weight) + (right->weight));
        n->left = left;
        n->right = right;
        enqueue(q, n);
    }
    dequeue(q, &n);
    pq_free(&q);
    //node_print_tree(n, '<', 2);
    return n;
}

void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length) {

    if (node != NULL && (node->left != NULL || node->right != NULL)) {
        fill_code_table(code_table, node->left, code, code_length + 1);
        code |= (1 << code_length);
        fill_code_table(code_table, node->right, code, code_length + 1);
    } else {
        if (node != NULL) {
            code_table[node->symbol].code = code;
            code_table[node->symbol].code_length = code_length;
        }
    }
}

void huff_compress_file(BitWriter *outbuf, Buffer *inbuf, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table) {
    //function declaration for helper
    void huff_write_tree(BitWriter * oubuf, Node * node);
    bit_write_uint8(outbuf, 'H');
    bit_write_uint8(outbuf, 'C');
    bit_write_uint32(outbuf, filesize);
    bit_write_uint16(outbuf, num_leaves);
    uint8_t byte, code_length;
    uint64_t code;
    huff_write_tree(outbuf, code_tree);
    while (read_uint8(inbuf, &byte) != 0) {
        code = code_table[byte].code;
        code_length = code_table[byte].code_length;
        for (uint16_t i = 0; i < code_length; i++) {
            bit_write_bit(outbuf, code & 1);
            code >>= 1;
        }
        //check if it decodes
        //check writes
    }
}

void huff_write_tree(BitWriter *outbuf, Node *node) {
    if (node != NULL && (node->left != NULL || node->right != NULL)) {
        huff_write_tree(outbuf, node->left);
        huff_write_tree(outbuf, node->right);
        bit_write_bit(outbuf, 0);
    } else {
        bit_write_bit(outbuf, 1);
        bit_write_uint8(outbuf, node->symbol);
    }
}

void code_tree_free(Node **node) {
    if (*node != NULL) {
        if ((*node)->left != NULL) {
            code_tree_free(&((*node)->left));
        }
        if ((*node)->right != NULL) {
            code_tree_free(&((*node)->right));
        }
        free(*node);
        *node = NULL;
    }
}
