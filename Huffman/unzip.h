#ifndef UNZIP_H_INCLUDED
#define UNZIP_H_INCLUDED
#include "zip.h"

int checking_file(char *name);

void comeback_original(FILE* zip_file, FILE* original, Huffman* tree, int size_trash);

void unzip_file();

#endif